// communication.h
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int sockfd, clientfd;
int is_tcp;
struct sockaddr_in server_addr, client_addr;
socklen_t addr_len = sizeof(client_addr);

void setup_server(const char* protocol) {
    is_tcp = strcmp(protocol, "tcp") == 0;
    sockfd = socket(AF_INET, is_tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
    
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if (is_tcp) listen(sockfd, 5);
}

void setup_client(const char* protocol) {
    is_tcp = strcmp(protocol, "tcp") == 0;
    sockfd = socket(AF_INET, is_tcp ? SOCK_STREAM : SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
}

void get_tcp_client() {
    clientfd = accept(sockfd, NULL, NULL);
}

void connect_to_tcp_server() {
    connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
}

void send_to_server(const char* msg) {
    if (is_tcp)
        send(sockfd, msg, strlen(msg) + 1, 0);
    else
        sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
}

void send_to_client(const char* msg) {
    if (is_tcp)
        send(clientfd, msg, strlen(msg) + 1, 0);
    else
        sendto(sockfd, msg, strlen(msg) + 1, 0, (struct sockaddr*)&client_addr, addr_len);
}

void receive_from_server(char* buffer, int size) {
    is_tcp ? recv(sockfd, buffer, size, 0)
           : recvfrom(sockfd, buffer, size, 0, NULL, NULL);
}

void receive_from_client(char* buffer, int size) {
    is_tcp ? recv(clientfd, buffer, size, 0)
           : recvfrom(sockfd, buffer, size, 0, (struct sockaddr*)&client_addr, &addr_len);
}

void close_all() {
    if (is_tcp && clientfd) close(clientfd);
    close(sockfd);
}
