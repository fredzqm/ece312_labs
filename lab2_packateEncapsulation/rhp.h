#include "udp.h"
#define RHMP_Message 0
#define CONTROL_Message 1

typedef struct
{
	char type;
	int dstPort_length;
	int srcPort;
	char payload[BUFSIZE];
	int payloadLen;
} RHP;

/*
 * talk to the server with the given messge.
 * return the number of bytes recieved.
 */
int sendRHPMessage(RHP* sent, RHP* response);

void printRHP(RHP *x, FILE* f);
