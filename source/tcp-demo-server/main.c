#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t; /* Define socklen_t for Windows */
#define close(socket) closesocket(socket)
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#endif
#include <pb_decode.h>
#include <pb_encode.h>
#include <protocol.h>

#include "devices/camera/camera.h"
#include "devices/mic/mic.h"
#include "devices/model/model.h"

#define TCP_PORT 12345

// Buffer size for reading data from the socket
#define BUFFER_SIZE 4096

// Structure to hold application state including protocol context, output stream, socket descriptor, and buffer
typedef struct {
    protocol_t* protocol;        // Protocol context for handling protocol-specific operations
    pb_ostream_t* ostream;       // Output stream for writing data to the socket
    int sockfd;                  // Socket file descriptor for the client connection
    uint8_t buffer[BUFFER_SIZE]; // Buffer for reading data from the socket
    size_t buffer_len;           // Length of data currently in the buffer
    size_t buffer_pos;           // Current position in the buffer
} app_state_t;

// Custom read function for pb_istream_t to read data from the socket, with buffering
static bool socket_read(pb_istream_t* stream, pb_byte_t* buf, size_t count) {
    if (count == 0) {
        return true;
    }

    app_state_t* state = (app_state_t*)(stream->state);
    size_t total_received = 0;

    while (total_received < count) {
        // If buffer is empty, refill it by reading from the socket
        if (state->buffer_pos == state->buffer_len) {
            ssize_t received = recv(state->sockfd, (char*)state->buffer, BUFFER_SIZE, 0);
            if (received < 0) {
#ifdef _WIN32
                int last_error = WSAGetLastError();
                if (last_error == WSAEWOULDBLOCK) {
                    // Non-blocking mode, wait for more data and call device poll repeatedly meanwhile
                    protocol_call_device_poll(state->protocol, state->ostream);
                    continue;
                }
                else {
                    PB_SET_ERROR(stream, strerror(last_error));
                    return false;
                }
#else
                if (errno == EWOULDBLOCK || errno == EAGAIN) {
                    // Non-blocking mode, wait for more data and call device poll repeatedly meanwhile
                    protocol_call_device_poll(state->protocol, state->ostream);
                    continue;
                }
                else {
                    PB_SET_ERROR(stream, strerror(errno));
                    return false; // Close the connection
                }
#endif
            }
            else if (received == 0) {
                PB_SET_ERROR(stream, "socket_read: Socket closed");
                return false; // Close the connection
            }
            state->buffer_len = received;
            state->buffer_pos = 0;
        }

        // Copy data from the buffer to the destination buffer (buf)
        size_t available = state->buffer_len - state->buffer_pos; // Available data in buffer
        size_t to_copy = count - total_received < available ? count - total_received : available;
        memcpy(buf + total_received, state->buffer + state->buffer_pos, to_copy);
        state->buffer_pos += to_copy;
        total_received += to_copy;
    }

    // All requested data has been read. Keep going.
    return true;
}

// Custom write function for pb_ostream_t to write data to the socket
static bool socket_write(pb_ostream_t* stream, const pb_byte_t* buf, size_t count) {
    app_state_t* state = (app_state_t*)(stream->state);
    ssize_t sent = send(state->sockfd, (const char*)buf, (int)count, 0);

    if (sent < 0) {
#ifdef _WIN32
        PB_SET_ERROR(stream, strerror(WSAGetLastError()));
#else
        PB_SET_ERROR(stream, strerror(errno));
#endif
        return false;
    }

    // Return true if all data was sent, otherwise false will close the connection.
    return sent == (ssize_t)count;
}

// Function to handle each client connection
static void handle_client(protocol_t* protocol, int client_socket) {
    // Initialize the application state
    app_state_t state = {
        .protocol = protocol,
        .sockfd = client_socket,
        .buffer_len = 0,
        .buffer_pos = 0,
    };

    // Initialize the input and output streams with the custom read/write functions
    pb_istream_t istream = { &socket_read, &state, SIZE_MAX, 0 };
    pb_ostream_t ostream = { &socket_write, &state, SIZE_MAX, 0, NULL };
    state.ostream = &ostream;

    while (true) {
        // Process the protocol request
        int status = protocol_process_request(protocol, &istream, &ostream);

        if (status != PROTOCOL_STATUS_SUCCESS) {
            printf("Failed to process package. %s %s\n",
                protocol_get_error_msg(status),
                istream.errmsg != NULL ? istream.errmsg : "");
            break;
        }

        // Reset the write/read counter
        ostream.bytes_written = 0;
    }

    // Halt any active devices
    for (int i = 0; i < protocol->board.devices_count; i++) {
        protocol_DeviceStatus status = protocol->board.devices[i].status;
        if (status == protocol_DeviceStatus_DEVICE_STATUS_ACTIVE || status == protocol_DeviceStatus_DEVICE_STATUS_ACTIVE_WAIT) {
            device_manager_t* device_manager = &protocol->device_managers[i];
            device_manager->stop(protocol, i, &ostream, device_manager->arg);
        }
    }

    printf("Closing socket\n");
    close(client_socket);
}

// Helper function to setup and configure the server socket
static int setup_server_socket(int port) {
    int server_socket;
    struct sockaddr_in server_addr;

    // Create the server socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        return -1;
    }

    // Enable the SO_REUSEADDR option on the server socket
    int optval = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optval, sizeof(optval)) < 0) {
        perror("setsockopt");
        close(server_socket);
        return -1;
    }

#ifdef _WIN32
    u_long mode = 1;
    if (ioctlsocket(server_socket, FIONBIO, &mode) != 0) {
        perror("ioctlsocket");
        close(server_socket);
        return -1;
    }
#else
    int flags = fcntl(server_socket, F_GETFL, 0);
    if (fcntl(server_socket, F_SETFL, flags | O_NONBLOCK) < 0) {
        perror("fcntl");
        close(server_socket);
        return -1;
    }
#endif

    // Configure the server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    // Bind the server socket to the specified port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        return -1;
    }

    // Listen for incoming connections
    if (listen(server_socket, 5) < 0) {
        perror("listen");
        close(server_socket);
        return -1;
    }

    return server_socket;
}

// Function to start the TCP server
static void start_server(protocol_t* protocol, int port) {
    int server_socket = setup_server_socket(port);
    if (server_socket < 0) {
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);

    while (1) {
        // Accept a new client connection
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);

        if (client_socket < 0) {
#ifdef _WIN32
            int last_error = WSAGetLastError();
            if (last_error != WSAEWOULDBLOCK) {
                perror("accept");
            }
#else
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                perror("accept");
            }
#endif
            continue;
        }

        printf("Client connected\n");

        // Set the client socket to non-blocking mode
#ifdef _WIN32
        u_long mode = 1;
        if (ioctlsocket(client_socket, FIONBIO, &mode) != 0) {
            perror("ioctlsocket");
            close(client_socket);
            continue;
        }
#else
        int client_flags = fcntl(client_socket, F_GETFL, 0);
        if (fcntl(client_socket, F_SETFL, client_flags | O_NONBLOCK) < 0) {
            perror("fcntl");
            close(client_socket);
            continue;
        }
#endif

        // Handle the client connection
        handle_client(protocol, client_socket);
    }

    // Clean up the protocol instance
    protocol_delete(protocol);

    // Close the server socket
    close(server_socket);
 }

int main() {
#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return -1; // Exit if Winsock initialization fails
    }
#endif

    // Initialize the protocol version and serial number
    protocol_Version firmware_version = {
        .major = 1,
        .minor = 2,
        .build = 345,
        .revision = 0
    };

    // Serial number {290DE5CB-460B-41BF-B257-022F2FD7849F}
    static uint8_t serial[16] = { 0x29, 0x0d, 0xe5, 0xcb, 0x46, 0x0b, 0x41, 0xbf, 0xb2, 0x57, 0x02, 0x2f, 0x2f, 0xd7, 0x84, 0x9f };

    // Create the protocol instance
    protocol_t* protocol = protocol_create("Demo Board", serial, firmware_version);

    // Register devices with the protocol
    camera_register(protocol);
    mic_register(protocol);
    model_register(protocol);

    // Start the TCP server on the specified port
    start_server(protocol, TCP_PORT);

    // Clean up the protocol instance
    protocol_delete(protocol);

#ifdef _WIN32
    // Clean up Winsock
    WSACleanup();
#endif

    return 0;
}
