#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr = {AF_INET, htons(8080), INADDR_ANY}, cli_addr;
    socklen_t len = sizeof(cli_addr);
    char buffer[10];

    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    while (1) {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cli_addr, &len);
        printf("Received: %s\n", buffer);

        printf("Send ACK for '%s'? (y/n): ", buffer);
        char choice;
        scanf(" %c", &choice);

        if (choice == 'y') {
            sendto(sockfd, "ACK", 3, 0, (struct sockaddr*)&cli_addr, len);
            printf("ACK sent.\n");
        } else {
            printf("ACK not sent.\n");
        }
    }
}
