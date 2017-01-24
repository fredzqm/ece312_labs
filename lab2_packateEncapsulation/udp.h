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


int talkToServer(char* message, int messageLen, char* buffer);

void printAsHex(char* buffer, int returnLen);
