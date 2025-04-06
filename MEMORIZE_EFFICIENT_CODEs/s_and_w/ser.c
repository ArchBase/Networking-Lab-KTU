// stop_wait_server.c
#include "../communication.h"
#include <stdio.h>

#define BUFFER_SIZE 10

int main() {
    char buffer[BUFFER_SIZE];

    setup_server("udp");

    while (1) {
        receive_from_client(buffer, sizeof(buffer));
        printf("Received: %s\n", buffer);

        printf("Send ACK for '%s'? (y/n): ", buffer);
        char choice;
        scanf(" %c", &choice);

        if (choice == 'y') {
            send_to_client("ACK");
            printf("ACK sent.\n");
        } else {
            send_to_client("NACK");
            printf("NACK sent.\n");
        }
    }
    printf("Recieived: %s\n", buffer);

    close_all();
    return 0;
}
