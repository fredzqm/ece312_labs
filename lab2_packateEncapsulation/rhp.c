
#include "rhp.h"

int writeRHP(RHP* rhp, char* buffer);
void readRHP(RHP* rhp, char* buffer, int length);
int computeCheckSum(char* data, int length);


void sendRHPMessage(RHP* sentRHP, RHP* responseRHP) {
    char sentBuffer[BUFSIZE], recieveBuffer[BUFSIZE];
    
    int offset = writeRHP(sentRHP, sentBuffer);

    printf("set bytes as hex:\n");
    printAsHex(sentBuffer, offset);

    printf("%s\n", "ok");

    int nBytes = talkToServer(sentBuffer, offset, recieveBuffer);
    
    recieveBuffer[nBytes] = 0;
    printf("recieve bytes as hex:\n");
    printAsHex(recieveBuffer, nBytes);

    readRHP(responseRHP, recieveBuffer, nBytes);
}

int writeRHP(RHP* rhp, char* buffer) {
    char type = rhp->type;
    int dstPort_length = rhp->dstPort_length;
    int srcPort = rhp->srcPort;
    char* payload = rhp->payload;
    int payloadLen = rhp->payloadLen;

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

    buffer[offset++] = 0xff & checksum;
    buffer[offset++] = 0xff & (checksum>>8);

    // return the size of header
    return offset;
}

void readRHP(RHP* rhp, char* buffer, int length) {
    int offset = 0, i;
    char type = buffer[offset++];
    int dstPort_length = buffer[offset++];
    dstPort_length = dstPort_length + (0xff00 & (buffer[offset++] << 8));
    int srcPort = buffer[offset++];
    srcPort = srcPort + (0xff00 & (buffer[offset++] << 8));
    char* payload = (char*) malloc(sizeof(char) * (dstPort_length+1));
    for (i = 0; i < dstPort_length; i++)
        payload[i] = buffer[offset+i];

    rhp->type = type;
    rhp->dstPort_length = dstPort_length;
    rhp->srcPort = srcPort;
    rhp->payload = payload;
    rhp->payloadLen = dstPort_length;
}


int computeCheckSum(char* data, int length) {
    long checkSum = 0;
    int i;
    for (i = 0; i < length; i+=2) {
        int a = (0xff00 & (data[i] * 256)) + (0xff & data[i+1]);
        checkSum += a;
    }
    checkSum = (0xffff & (checkSum >> 16)) + (0xffff & checkSum);
    checkSum = checkSum ^ 0xffff;
    return checkSum;
}


void printRHP(RHP* x) {
    printf("\ttype: %d\n\tdstPort_length: %d\n\tsrcPort: %d \n\tpayload: %s\n", 
        x->type, x->dstPort_length, x->srcPort, x->payload);
}
