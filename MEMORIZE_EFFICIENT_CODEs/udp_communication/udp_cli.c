#include "../communication.h"

int main() {
    char buffer[100];
    setup_client("udp");
    send_to_server("Hello from Client");
    receive_from_server(buffer, sizeof(buffer));
    printf("Server: %s\n", buffer);
    close_all();
}
