#include <stdio.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

typedef struct
{
	char type;
	int dstPort_length;
	int srcPort;
	char* payload;
	int payloadLen;
} RHP;

/*
 * talk to the server with the given messge.
 * return the number of bytes recieved.
 */
void sendRHPMessage(RHP* sent, RHP* response);

int writeRHP(RHP* rhp, char* buffer);
void readRHP(RHP* rhp, char* buffer, int length);

int computeCheckSum(char* data, int length);

