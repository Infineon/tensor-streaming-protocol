#include "announcement.h"
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
#include <ifaddrs.h>
#include <netdb.h>
#include <pthread.h>
#endif

#include <protocol.h>

#define ANNOUNCEMENT_PORT 19245
#define ANNOUNCEMENT_INTERVAL_SEC 3
#define ANNOUNCEMENT_MAGIC_KEY "TSPA2501"
#define BOARD_NAME_MAX 64

typedef struct {
    uint8_t magic[8];
    uint32_t protocol_version[4];
    uint32_t firmware_version[4];
    uint8_t board_serial[16];
    uint16_t port;    // The TCP port for the client to connect to
    uint32_t ip_address; // The IPv4 address the client should connect to
    char name[BOARD_NAME_MAX];
} announcement_t;

typedef struct {
    protocol_t* protocol;
    int tcp_port;
} announcement_thread_args_t;

// Function to get the local IP address
static uint32_t get_local_ip_address() {
#ifdef _WIN32
    char hostname[NI_MAXHOST];
    struct addrinfo hints, * res;
    struct sockaddr_in* addr;

    if (gethostname(hostname, NI_MAXHOST) == SOCKET_ERROR) {
        fprintf(stderr, "Error getting hostname: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Only IPv4
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        fprintf(stderr, "Error getting address info\n");
        exit(EXIT_FAILURE);
    }

    addr = (struct sockaddr_in*)res->ai_addr;
    uint32_t ip = addr->sin_addr.s_addr;

    freeaddrinfo(res);
    return ip;

#else
    struct ifaddrs* ifaddr, * ifa;
    int family;
    char host[NI_MAXHOST];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    // Loop through linked list of interfaces
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        // Check for IPv4 address
        if (family == AF_INET) {
            int s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
                host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }

            if (strcmp(ifa->ifa_name, "lo") != 0) {  // Ignore loopback interface
                freeifaddrs(ifaddr);
                return inet_addr(host);  // Return the first non-loopback IPv4 address found
            }
        }
    }

    freeifaddrs(ifaddr);
    return INADDR_NONE;  // Return if no suitable address found
#endif
}

#ifdef _WIN32
static DWORD WINAPI announcement_thread_func(LPVOID arg) {
#else
static void* announcement_thread_func(void* arg) {
#endif
    announcement_thread_args_t* args = (announcement_thread_args_t*)arg;
    protocol_t* protocol = args->protocol;
    int tcp_port = args->tcp_port;
    int sockfd;
    struct sockaddr_in broadcast_addr;
    announcement_t announcement;
    int broadcast = 1;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0) {
        perror("setsockopt");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = inet_addr("255.255.255.255");
    broadcast_addr.sin_port = htons(ANNOUNCEMENT_PORT);

    memcpy(announcement.magic, ANNOUNCEMENT_MAGIC_KEY, sizeof(announcement.magic));
    memcpy(announcement.protocol_version, &protocol->board.protocol_version, sizeof(announcement.protocol_version));
    memcpy(announcement.firmware_version, &protocol->board.firmware_version, sizeof(announcement.firmware_version));
    memcpy(announcement.board_serial, protocol->board.serial.uuid, sizeof(announcement.board_serial));
    announcement.port = tcp_port;
    announcement.ip_address = get_local_ip_address();
    strncpy(announcement.name, protocol->board.name, BOARD_NAME_MAX - 1);

    printf("Sending announcements broadcast messages on UDP %d every %d seconds\n", ANNOUNCEMENT_PORT, ANNOUNCEMENT_INTERVAL_SEC);

    while (1) {
        int sent = sendto(sockfd, &announcement, sizeof(announcement), 0, (struct sockaddr*)&broadcast_addr, sizeof(broadcast_addr));
        if (sent < 0) {
            perror("sendto");
        }       
#ifdef _WIN32
        Sleep(ANNOUNCEMENT_INTERVAL_SEC * 000); // Windows sleep in milliseconds
#else
        sleep(ANNOUNCEMENT_INTERVAL_SEC); // Unix sleep in seconds
#endif
    }

    close(sockfd);
    free(args);
    return 0;
}

int announcement_start(protocol_t * protocol, int tcp_port) {
    announcement_thread_args_t* args = (announcement_thread_args_t*)malloc(sizeof(announcement_thread_args_t));
    if (args == NULL) {
        fprintf(stderr, "Failed to allocate memory for announcement thread arguments\n");
        return -1;
    }

    args->protocol = protocol;
    args->tcp_port = tcp_port;

#ifdef _WIN32
    DWORD threadId;
    HANDLE announcementThread = CreateThread(NULL, 0, announcement_thread_func, args, 0, &threadId);
    if (announcementThread == NULL) {
        fprintf(stderr, "Failed to create announcement thread\n");
        free(args);
        return -1;
    }
#else
    pthread_t announcement_thread;
    if (pthread_create(&announcement_thread, NULL, announcement_thread_func, args) != 0) {
        fprintf(stderr, "Failed to create announcement thread\n");
        free(args);
        return -1;
    }
#endif
    return 0;
}
