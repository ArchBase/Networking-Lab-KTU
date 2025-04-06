#include "../communication.h"

int main() {
    char buffer[100];
    setup_client("tcp");
    connect_to_tcp_server();
    send_to_server("Hello from Client");
    receive_from_server(buffer, sizeof(buffer));
    printf("Server: %s\n", buffer);
    close_all();
}
