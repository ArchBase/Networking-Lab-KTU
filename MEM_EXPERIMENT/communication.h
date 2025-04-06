// communication.h

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int sockfd, clientfd;
int is_tcp = 0;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_len = sizeof(client_addr);

// Setup server
void setup_server(const char* protocol) {
    if (strcmp(protocol, "tcp") == 0) {
        is_tcp = 1;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        int opt = 1;
        setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    } else {
        is_tcp = 0;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (is_tcp) {
        listen(sockfd, 5);
    }
}

// Accept TCP client
void get_tcp_client() {
    if (is_tcp)
        clientfd = accept(sockfd, NULL, NULL);
}

// Setup client
void setup_client(const char* protocol) {
    if (strcmp(protocol, "tcp") == 0) {
        is_tcp = 1;
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    } else {
        is_tcp = 0;
        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
}

// Connect TCP client
void connect_to_tcp_server() {
    if (is_tcp)
        connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
}

// Send to server
void send_to_server(const char* msg) {
    if (is_tcp) {
        send(sockfd, msg, strlen(msg) + 1, 0);
    } else {
        sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    }
}

// Send to client
void send_to_client(const char* msg) {
    if (is_tcp) {
        send(clientfd, msg, strlen(msg) + 1, 0);
    } else {
        sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&client_addr, addr_len);
    }
}

// Receive from server
void receive_from_server(char* buffer, int size) {
    if (is_tcp) {
        recv(sockfd, buffer, size, 0);
    } else {
        recvfrom(sockfd, buffer, size, 0, NULL, NULL);
    }
}

// Receive from client
void receive_from_client(char* buffer, int size) {
    if (is_tcp) {
        recv(clientfd, buffer, size, 0);
    } else {
        recvfrom(sockfd, buffer, size, 0, (struct sockaddr*)&client_addr, &addr_len);
    }
}

// Cleanup
void close_all() {
    if (is_tcp && clientfd) close(clientfd);
    close(sockfd);
}

#endif
