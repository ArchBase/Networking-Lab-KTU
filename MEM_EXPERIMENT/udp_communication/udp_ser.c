#include "../communication.h"

int main() {
    char buffer[100];
    setup_server("udp");
    receive_from_client(buffer, sizeof(buffer));
    printf("Client: %s\n", buffer);
    send_to_client("Hello from Server");
    close_all();
}
