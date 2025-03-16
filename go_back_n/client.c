#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <time.h>

#define WINDOW_SIZE 4  // Window size

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr = {AF_INET, htons(8080), INADDR_ANY};
    socklen_t len = sizeof(serv_addr);
    char message[] = "MOONWHITE";
    
    int base = 0, next_seq = 0, msg_len = strlen(message);
    
    while (base < msg_len) {
        while (next_seq < base + WINDOW_SIZE && next_seq < msg_len) {
            char packet[3] = {next_seq + '0', message[next_seq], '\0'};  // Sequence + Data
            sendto(sockfd, packet, strlen(packet), 0, (struct sockaddr*)&serv_addr, len);
            printf("Sent Packet [%d]: %c\n", next_seq, message[next_seq]);
            next_seq++;
        }

        fd_set fds;
        struct timeval timeout = {5, 0};  // 5 seconds timeout
        FD_ZERO(&fds);
        FD_SET(sockfd, &fds);

        int activity = select(sockfd + 1, &fds, NULL, NULL, &timeout);
        if (activity > 0) {
            char ack[10];
            recvfrom(sockfd, ack, sizeof(ack), 0, (struct sockaddr*)&serv_addr, &len);
            int ack_num = ack[0] - '0';
            printf("Received ACK [%d]\n", ack_num);
            
            if (ack_num >= base) base = ack_num + 1;  // Slide window
        } else {
            printf("Timeout! Resending from Packet [%d]...\n", base);
            next_seq = base;  // Go back and resend from base
        }
    }
}
