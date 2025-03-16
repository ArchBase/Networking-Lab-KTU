#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server = {AF_INET, htons(8080), INADDR_ANY}, client;
    bind(sock, (struct sockaddr*)&server, sizeof(server));

    char buffer[1024];
    socklen_t len = sizeof(client);
    recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client, &len);
    printf("Received: %s\n", buffer);

    sendto(sock, "Hello from server", 17, 0, (struct sockaddr*)&client, len);
    return 0;
}
