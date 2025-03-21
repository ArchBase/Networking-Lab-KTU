#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Allow port reuse
    int opt = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in serv = {AF_INET, htons(8080), INADDR_ANY};

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);

    int client = accept(sockfd, NULL, NULL);

    // Receive message from client
    char buffer[100];
    recv(client, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    // Send reply to client
    char msg[] = "Hello from Server!";
    send(client, msg, sizeof(msg), 0);

    close(client);
    close(sockfd);
}
