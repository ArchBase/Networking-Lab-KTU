#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define WINDOW_SIZE 4  // Define window size

int main() {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serv_addr = {AF_INET, htons(8080), INADDR_ANY}, cli_addr;
    socklen_t len = sizeof(cli_addr);
    char buffer[10];

    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    int expected_seq = 0;  // Expected sequence number

    while (1) {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cli_addr, &len);
        int seq_num = buffer[0] - '0';  // Extract sequence number
        char data = buffer[1];

        if (seq_num == expected_seq) {  // Process only if in order
            printf("Received Packet [%d]: %c\n", seq_num, data);
            expected_seq++;  // Move to the next expected sequence
        } else {
            printf("Out-of-order Packet [%d] ignored.\n", seq_num);
        }

        printf("Send ACK for [%d]? (y/n): ", seq_num);
        char choice;
        scanf(" %c", &choice);

        if (choice == 'y') {
            char ack[2] = {seq_num + '0', '\0'};
            sendto(sockfd, ack, strlen(ack), 0, (struct sockaddr*)&cli_addr, len);
            printf("ACK [%d] sent.\n", seq_num);
        } else {
            printf("ACK [%d] not sent.\n", seq_num);
        }
    }
}
