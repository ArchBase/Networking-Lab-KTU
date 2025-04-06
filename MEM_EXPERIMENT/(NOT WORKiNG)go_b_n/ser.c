// sender.c
#include "../communication.h"
#include <stdio.h>
#include <string.h>

int main() {
    char data[] = "MOON WHITE";
    int len = strlen(data);
    int base = 0, window = 4;
    char buffer[100], ack[10];

    setup_client("tcp");
    connect_to_tcp_server();

    while (base < len) {
        // Send window of 4 chars
        strcpy(buffer, "");
        for (int i = base; i < base + window && i < len; i++) {
            char temp[2] = { data[i], '\0' };
            strcat(buffer, temp);
        }

        send_to_server(buffer);
        printf("Sent window: \"%s\"\n", buffer);

        receive_from_server(ack, sizeof(ack));
        int ack_no = atoi(ack);  // convert ACK string to int
        printf("Received ACK: %d\n", ack_no);

        if (ack_no == window) {
            base += window;
        } else {
            base += ack_no;  // Go back and resend from that point
        }
    }

    close_all();
    return 0;
}
