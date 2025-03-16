#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr = {AF_INET, htons(8080), INADDR_ANY};
    socklen_t len = sizeof(serv_addr);
    char message[] = "MOON WHITE", ack[10];
    
    for (int i = 0; i < strlen(message); i++) {
        if (message[i] == ' ') continue; // Skip spaces for simplicity
        char packet[2] = {message[i], '\0'};

        while (1) {
            sendto(sockfd, packet, strlen(packet), 0, (struct sockaddr*)&serv_addr, len);
            printf("Sent: %s\n", packet);

            fd_set fds;
            struct timeval timeout = {5, 0};  // 5 seconds timeout

            FD_ZERO(&fds);
            FD_SET(sockfd, &fds);

            int activity = select(sockfd + 1, &fds, NULL, NULL, &timeout);
            if (activity > 0) {
                recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr*)&serv_addr, &len);
                printf("Received ACK for: %s\n", packet);
                break;  // Move to next character after ACK
            } else {
                printf("No ACK for '%s'. Resending...\n", packet);
            }
        }
    }
}
