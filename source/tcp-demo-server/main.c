
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
#include <poll.h>
#include <errno.h>
#endif
#include <pb_decode.h>
#include <pb_encode.h>
#include <protocol.h>

#include "devices/camera/camera.h"
#include "devices/mic/mic.h"
#include "devices/model/model.h"

#define TCP_PORT 12345

// Custom read function for pb_istream_t
static bool socket_read(pb_istream_t* stream, pb_byte_t* buf, size_t count) 
{
    if (count == 0)
        return true;

    int sockfd = *(int*)(stream->state);
    size_t total_received = 0;

    while (total_received < count) {
        ssize_t received = recv(sockfd, (char*)buf + total_received, (int)(count - total_received), 0);

        if (received < 0) {
#ifdef _WIN32
            PB_SET_ERROR(stream, strerror(WSAGetLastError()));
#else
            PB_SET_ERROR(stream, strerror(errno));
#endif
            return false;
        }
        else if (received == 0) {
            PB_SET_ERROR(stream, "socket_read: Socket closed");
            return false;
        }

        total_received += received;
    }

    return true;
}

// Custom write function for pb_ostream_t
static bool socket_write(pb_ostream_t* stream, const pb_byte_t* buf, size_t count) 
{
    int sockfd = *(int*)(stream->state);
    ssize_t sent = send(sockfd, (const char*)buf, (int)count, 0);

    if (sent < 0) {
#ifdef _WIN32
        PB_SET_ERROR(stream, strerror(WSAGetLastError()));
#else
        PB_SET_ERROR(stream, strerror(errno));
#endif
        return false;
    }

    // TODO: write bigger chunks 
    // printf("socket_write %zu\n", sent);

    return sent == (ssize_t)count;
}

static void watchdog_reset()
{
    // printf("Watchdog reset!\n");
}

// Function to handle each client connection
static void handle_client(protocol_t* protocol, int client_socket)
{
    struct pollfd ufds[1];
    ufds[0].fd = client_socket;
    ufds[0].events = POLLIN;

    pb_istream_t istream = { &socket_read, &client_socket, SIZE_MAX, 0 };
    pb_ostream_t ostream = { &socket_write, &client_socket, SIZE_MAX, 0, NULL };
 
    while (true)
    {
        switch (poll(ufds, 1, 1)) {
        case -1:
            perror("poll");
            break;
        case 0: // timeout
            protocol_call_device_poll(protocol, &ostream);
            continue;
        default:
            break;
        }

        int status = protocol_process_request(protocol, &istream, &ostream);
        if (status != PROTOCOL_STATUS_SUCCESS) {
            printf("Failed to process package. %s %s\n", 
                protocol_get_error_msg(status),
                istream.errmsg != NULL ? istream.errmsg : istream.errmsg);
            break;
        }

        if(ostream.bytes_written != 0)
            printf("Sent %ld bytes\n", ostream.bytes_written);

        // Reset write/read counter
        ostream.bytes_written = 0;
    }

    // Halt any active devices
    for (int i = 0; i < protocol->board.devices_count; i++) {
        protocol_DeviceStatus status = protocol->board.devices[i].status;
        if (status == protocol_DeviceStatus_DEVICE_STATUS_ACTIVE || status == protocol_DeviceStatus_DEVICE_STATUS_ACTIVE_WAIT) {
            device_manager_t* device_manager = &protocol->device_managers[i];
            device_manager->stop(protocol, i, device_manager->arg);
        }
    }
    
    printf("Closing socket\n");
    close(client_socket);
}

// Function to start the TCP server
static void start_server(protocol_t* protocol, int port)
{
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("listen");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", port);
  
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        printf("Client connected\n");
        handle_client(protocol, client_socket);
    }

    protocol_delete(protocol);

    close(server_socket);
}

int main() 
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "WSAStartup failed.\n");
        return -1;
    }
#endif

    printf("Request                    : %ld\n", sizeof(protocol_Request));
    printf("BoardCapabilitiesRequest   : %ld\n", sizeof(protocol_BoardCapabilitiesRequest));
    printf("DeviceConfigurationRequest : %ld\n", sizeof(protocol_DeviceConfigurationRequest));
    printf("StartRequest               : %ld\n", sizeof(protocol_StartRequest));
    printf("StopRequest                : %ld\n", sizeof(protocol_StopRequest));
    printf("WatchdogResetRequest       : %ld\n", sizeof(protocol_WatchdogResetRequest));
    printf("Response                   : %ld\n", sizeof(protocol_Response));
    printf("BoardCapabilitiesResponse  : %ld\n", sizeof(protocol_BoardCapabilitiesResponse));
    printf("DeviceConfigurationResponse: %ld\n", sizeof(protocol_DeviceConfigurationResponse));
    printf("ErrorResponse              : %ld\n", sizeof(protocol_ErrorResponse));
    printf("DataChunk                  : %ld\n", sizeof(protocol_DataChunk));
    printf("Board                      : %ld\n", sizeof(protocol_Board));
    printf("Device                     : %ld\n", sizeof(protocol_Device));
    printf("Option                     : %ld\n", sizeof(protocol_Option));
    printf("Dimension                  : %ld\n", sizeof(protocol_Dimension));
    printf("StreamConfig               : %ld\n", sizeof(protocol_StreamConfig));
    
    protocol_Version firmware_version = {
        major: 1,
        minor : 2,
        build : 345,
        revision : 0
    };

    // {290DE5CB-460B-41BF-B257-022F2FD7849F}
    static uint8_t serial[16] = { 0x29, 0x0d, 0xe5, 0xcb, 0x46, 0x0b, 0x41, 0xbf, 0xb2, 0x57, 0x02, 0x2f, 0x2f, 0xd7, 0x84, 0x9f };

    protocol_t* protocol = protocol_create("Demo Board", serial, firmware_version);

    protocol_configure_watchdog(protocol, 1000, watchdog_reset);

    camera_register(protocol);
    mic_register(protocol);
    model_register(protocol);

    start_server(protocol, TCP_PORT);
    
    protocol_delete(protocol);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}