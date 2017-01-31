#include "rhmp.h"

int writeRHMP(RHMP* rhmp, char* buffer);
int readRHMP(RHMP* rhmp, char* buffer);
/*
 * talk to the server with the given messge.
 * return the number of bytes recieved.
 */

void printRHMP(RHMP* x);


void sendRHMPMessage(RHMP* sentRHMP, RHMP* responseRHMP) {
    char sentBuffer[BUFSIZE], recievedBuffer[BUFSIZE];

    printf("RHMP sent content:\n");
    printRHMP(sentRHMP);

    int offset = writeRHMP(sentRHMP, sentBuffer);

		RHP rhp, resp;
    rhp.type = RHMP_Message;
    rhp.dstPort_length = 105; 
    rhp.srcPort = 674;
    rhp.payload = sentBuffer;
    rhp.payloadLen = offset;

    resp.payload = recievedBuffer;
    
    printf("RHP sent content:\n");
    printRHP(&rhp);

    sendRHPMessage(&rhp, &resp);

    printf("RHP content:\n");
    printRHP(&resp);

    readRHMP(responseRHMP, resp.payload);
    
    printf("RHMP content:\n");
    printRHMP(responseRHMP);
}

int writeRHMP(RHMP* rhmp, char* buffer) {
    char type = rhmp->type;
    int commID = rhmp->commID;
    char length = rhmp->length;
    char* payload = rhmp->payload;
    
    int offset = 0;
    buffer[offset++] = ((type << 2) & 0x0fc) | (commID & 0x03);
    buffer[offset++] = (commID>>2) & 0xff;
    buffer[offset++] = length;
    int i;
    for (i = 0; i < length; i++)
        buffer[offset++] = payload[i];
    return offset;
}

int readRHMP(RHMP* rhMp, char* buffer) {
    char a = buffer[0], b = buffer[1];
    char type = (a >> 2) & 0x3f;
    int commID = ((a<<8) & 0x30) | (b & 0xff);
    int length = buffer[2];
    int i;
    for (i = 0; i < length-3; i++)
        rhMp->payload[i] = buffer[3+i];

    rhMp->type = type;
    rhMp->commID = commID;
    rhMp->length = length;
    return 0;
}


void printRHMP(RHMP *x) {
    printf("\ttype: %d\n\tcommitID: %d\n\tlength: %d \n\tpayload: %s\n", 
        x->type, x->commID, x->length, x->payload);
}


