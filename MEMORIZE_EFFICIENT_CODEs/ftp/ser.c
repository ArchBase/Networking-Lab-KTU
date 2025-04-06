// ftp_server.c
#include "../communication.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];

    setup_server("tcp");
    get_tcp_client();

    FILE *file = fopen("received.txt", "wb");

    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        receive_from_client(buffer, BUFFER_SIZE);
        
        // Break when received buffer is empty (end of file)
        if (strlen(buffer) == 0)
            break;

        fwrite(buffer, 1, strlen(buffer), file);
    }

    fclose(file);
    close_all();
    return 0;
}
