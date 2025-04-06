#include "../communication.h"

void main(){
    
    char buffer[100];

    setup_client("udp");
    //connect_to_tcp_server();

    printf("Enter string to check palindrome: ");
    scanf("%s", buffer);

    send_to_server(buffer);

    receive_from_server(buffer, 100);

    printf("Server: %s", buffer);
}

