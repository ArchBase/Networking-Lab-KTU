// receiver.c
#include "../communication.h"
#include <stdio.h>
#include <string.h>

int main() {
    char buffer[100];
    char ack[10];

    setup_server("tcp");
    get_tcp_client();

    while (1) {
        receive_from_client(buffer, sizeof(buffer));
        if (strlen(buffer) == 0) break;

        printf("Received window: \"%s\"\n", buffer);

        printf("Enter ACK to send (0 to %ld): ", strlen(buffer));
        fgets(ack, sizeof(ack), stdin);
        ack[strcspn(ack, "\n")] = 0;  // Remove newline

        send_to_client(ack);
    }

    close_all();
    return 0;
}
