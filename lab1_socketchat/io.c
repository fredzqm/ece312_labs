
#include "io.h"

void requestName(char* buffer) {
    printf("Provide user name: ");
    fgets(buffer, MAX_STRING_LEN, stdin);
    buffer[strlen(buffer)-1] = 0;
}

void printPrompt() {
    printf("<%s> : ", name);
    fflush(stdout);
}

void readMessage(char* buffer) {
    printPrompt();
    fgets(buffer, MAX_STRING_LEN, stdin);
    buffer[strlen(buffer)-1] = 0;
}

void printRecievedMessage(char* message) {
    printf("\r                                           \r");
    printf("%s\n", message, name);
    printPrompt();
}

void sendMessage(int socket, char* message) {
    if (send(socket , message , strlen(message) , 0) < 0)
        die_with_error("send failed");
}

int recieveMessage(int sock, char* buffer) {    
    int numByte = recv(sock , buffer , MAX_STRING_LEN , 0);
    if (numByte <= 0)
        return -1;
    buffer[numByte] = 0;
    return 0;
}

void die_with_error(char *error_message) {
  perror(error_message);
  exit(1);
}