

#include "../communication.h"

void main(){
    char buffer[100];
    int i=0, j, flag=0;

    setup_server("udp");
    //get_tcp_client();

    receive_from_client(buffer, 10);

    printf("String recieved: %s", buffer);
    printf("\nLength: %d\n", (int)strlen(buffer));

    i=0;
    j = strlen(buffer)-1;

    while(i<(strlen(buffer)/2)){
        if(buffer[i] != buffer[j]){
            strcpy(buffer, "String is not palindrome.");
            flag = 1;
            break;
        }
        i++;
        j--;
    }
    if(flag == 0){
        strcpy(buffer, "String is palindrome");
    }
    send_to_client(buffer);
}