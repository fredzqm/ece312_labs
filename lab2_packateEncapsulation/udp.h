#include <stdio.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

#define SERVER_ADDRESS "137.112.38.47"
#define MESSAGE "hello there"
#define PORT 1874
#define BUFSIZE 1024


/**
you can send message to server. 
message is the information you watn to send, 
messagelen is the length of the message
buffer is space in memory to receive the message.

return the bytes number of the message received.
*/
int talkToServer(char* message, int messageLen, char* buffer);


void printAsHex(FILE* f, char* buffer, int length);