#include "udp.h"


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

void printRHP(RHP* x);