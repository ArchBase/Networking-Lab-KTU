// ftp_client.c
#include "../communication.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    setup_client("tcp");
    connect_to_tcp_server();

    FILE *file = fopen("sample.txt", "rb");

    while (fgets(buffer, BUFFER_SIZE, file)) {
        send_to_server(buffer);
        memset(buffer, 0, BUFFER_SIZE);
    }

    // Optionally send an empty message to indicate end of file
    send_to_server("");

    fclose(file);
    close_all();
    return 0;
}
