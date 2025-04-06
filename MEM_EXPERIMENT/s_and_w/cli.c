// stop_wait_client.c
#include "../communication.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 10

int main() {
    char ack[BUFFER_SIZE];
    char message[] = "MOON WHITE";

    setup_client("udp");

    for (int i = 0; i < strlen(message); i++) {
        if (message[i] == ' ') continue;

        char packet[2] = {message[i], '\0'};

        while (1) {
            send_to_server(packet);
            printf("Sent: %s\n", packet);

            receive_from_server(ack, sizeof(ack));
            if (strcmp(ack, "ACK") == 0) {
                printf("Received ACK for: %s\n", packet);
                break;
            } else {
                printf("Received NACK for: %s. Resending...\n", packet);
            }
        }
    }

    close_all();
    return 0;
}
