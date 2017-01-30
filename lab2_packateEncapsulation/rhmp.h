#include "rhp.h"

#define REQUEST_ID 2
#define MESSAGE_REQUEST 8
#define RESPOND_ID 4
#define REQUEST_MESSAGE 16



/**
you can send message to server. 
message is the information you watn to send, 
messagelen is the length of the message
buffer is space in memory to receive the message.

return the bytes number of the message received.
*/
// int talkToServer(char* message, int messageLen, char* buffer);


// void printAsHex(char* buffer, int returnLen);

typedef struct
{
	char type;
	int commID;
	char length;
	char* payload;
} RHMP;

/*
 * talk to the server with the given messge.
 * return the number of bytes recieved.
 */
void sendRHMPMessage(RHMP* sent, RHMP* response);

void printRHMP(RHMP* x);
