#include "../communication.h"

void main(){
    
    char buffer[100];

    setup_client("tcp");
    connect_to_tcp_server();

    receive_from_server(buffer, 10);
    printf("Server: %s", buffer);

    printf("Enter string to check palindrome: ");
    scanf("%s", buffer);

    send_to_server(buffer);

    receive_from_server(buffer, 100);

    printf("Server: %s", buffer);
}