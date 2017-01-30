#include "rhmp.h"

int writeRHMP(RHMP* rhmp, char* buffer);
int readRHMP(RHMP* rhmp, char* buffer, int length);
/*
 * talk to the server with the given messge.
 * return the number of bytes recieved.
 */

void printRHMP(RHMP* x);


void sendRHMPMessage(RHMP* sentRHMP, RHMP* responseRHMP) {
    char sentBuffer[BUFSIZE], recieveBuffer[BUFSIZE];
    
    int offset = writeRHMP(sentRHMP, sentBuffer);

    printRHMP(sentRHMP);

    printf("set bytes as hex:\n");
    printAsHex(sentBuffer, offset);


void sendRHPMessage(RHP* sent, RHP* response);
		

		RHP rhp, resp;
    rhp.type = RHMP_Message;
    rhp.dstPort_length = 105; 
    rhp.srcPort = 682;
    rhp.payload = message;
    rhp.payloadLen = strlen(message);
    
    sendRHPMessage(&rhp, &resp);
    
    
    printf("recieve bytes as hex:\n");
    printAsHex(recieveBuffer, nBytes);

    if (readRHMP(responseRHMP, recieveBuffer, nBytes) < 0)
        printf("Checksum failed\n");

    printRHMP(responseRHMP);
}

int writeRHMP(RHMP* rhMp, char* buffer) {
    char type = rhmp->type;
    int dstPort_length = rhMp->dstPort_length;
    int srcPort = rhMp->srcPort;
    char* payload = rhMp->payload;
    int payloadLen = rhMp->payloadLen;

    int offset = 0, i;
    buffer[offset++] = type;
    buffer[offset++] = 0xff & dstPort_length;
    buffer[offset++] = 0xff & (dstPort_length>>8);
    buffer[offset++] = 0xff & srcPort;
    buffer[offset++] = 0xff & (srcPort>>8);
    for (i = 0; i < payloadLen; i++)
        buffer[offset++] = payload[i];
    if (offset % 2 == 1)
        buffer[offset++] = 0;

    // compute the checksum
    int checksum = computeCheckSum(buffer, offset);
    checksum = checksum ^ 0xffff;

    buffer[offset++] = 0xff & (checksum>>8);
    buffer[offset++] = 0xff & checksum;

    return offset;
}

int readRHMP(RHMP* rhMp, char* buffer, int length) {
    int checksum = computeCheckSum(buffer, length);
    if (checksum != 0xffff) // check the checksum
        return -1;

    int offset = 0, i;
    char type = buffer[offset++];
    int dstPort_length = buffer[offset++];
    dstPort_length = dstPort_length + (0xff00 & (buffer[offset++] << 8));
    int srcPort = buffer[offset++];
    srcPort = srcPort + (0xff00 & (buffer[offset++] << 8));
    char* payload = (char*) malloc(sizeof(char) * (dstPort_length+1));
    for (i = 0; i < dstPort_length; i++)
        payload[i] = buffer[offset+i];

    rhMp->type = type;
    rhMp->dstPort_length = dstPort_length;
    rhMp->srcPort = srcPort;
    rhMp->payload = payload;
    rhMp->payloadLen = dstPort_length;

    return 0;
}


int computeCheckSum(char* data, int length) {
    unsigned int a = 0, b = 0;
    int i;
    for (i = 0; i < length; i+=2) {
        a += 0xff & ((int) data[i]);
        b += 0xff & ((int) data[i+1]);
    }
    long checkSum = a * 256 + b;
    checkSum = ((checkSum >> 16) & 0xffff) + (checkSum & 0xffff);
    return checkSum;
}


void printRHMP(RHMP *x) {
    printf("\ttype: %d\n\tdstPort_length: %d\n\tsrcPort: %d \n\tpayload: %s\n", 
        x->type, x->dstPort_length, x->srcPort, x->payload);
}


