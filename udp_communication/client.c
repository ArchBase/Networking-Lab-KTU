#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    sendto(sock, "Hello from client", 17, 0, (struct sockaddr*)&server, sizeof(server));

    char buffer[1024];
    recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
    printf("Received: %s\n", buffer);

    return 0;
}
