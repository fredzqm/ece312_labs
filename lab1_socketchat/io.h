#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define MAX_STRING_LEN 100 /* Maximum length of string to echo */

void readMessage(char* buffer);
void requestName(char* buffer);
void printRecievedMessage(char* message);

void sendMessage(int socket, char* message);
int recieveMessage(int sock, char* buffer);


void die_with_error(char *error_message);
