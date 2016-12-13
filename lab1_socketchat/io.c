
#include "io.h"

void requestName(char* buffer) {
    printf("Provide user name: ");
    fgets(buffer, MAX_STRING_LEN, stdin);
    buffer[strlen(buffer)-1] = 0;
}

void readMessage(char* buffer) {
    fgets(buffer, MAX_STRING_LEN, stdin);
    buffer[strlen(buffer)-1] = 0;
}

void printRecievedMessage(char* message) {
    printf("%s\n", message);
}
