#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    connect(sockfd, (struct sockaddr*)&serv, sizeof(serv));

    // Send message to server
    char msg[] = "Hello from Client!";
    send(sockfd, msg, sizeof(msg), 0);

    // Receive reply from server
    char buffer[100];
    recv(sockfd, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    close(sockfd);
}
