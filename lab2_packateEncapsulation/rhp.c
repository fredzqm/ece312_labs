
#include "rhp.h"

int writeRHP(RHP* rhp, char* buffer);
int readRHP(RHP* rhp, char* buffer, int length);
int computeCheckSum(char* data, int length);


void sendRHPMessage(RHP* sentRHP, RHP* responseRHP) {
    char sentBuffer[BUFSIZE], recieveBuffer[BUFSIZE];
    
    int offset = writeRHP(sentRHP, sentBuffer);

    int nBytes;
    while (1) {
        nBytes = talkToServer(sentBuffer, offset, recieveBuffer);
        int checksum = computeCheckSum(recieveBuffer, nBytes);
        if (checksum == 0xffff) {
            break;
        }
    }
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
    checksum = checksum ^ 0xffff;

    buffer[offset++] = 0xff & (checksum>>8);
    buffer[offset++] = 0xff & checksum;

    return offset;
}

int readRHP(RHP* rhp, char* buffer, int length) {
    int offset = 0, i;
    char type = buffer[offset++];
    int dstPort_length = buffer[offset++];
    dstPort_length = dstPort_length + (0xff00 & (buffer[offset++] << 8));
    int srcPort = buffer[offset++];
    srcPort = srcPort + (0xff00 & (buffer[offset++] << 8));
    for (i = 0; i < dstPort_length; i++)
        rhp->payload[i] = buffer[offset+i];

    rhp->type = type;
    rhp->dstPort_length = dstPort_length;
    rhp->srcPort = srcPort;
    rhp->payloadLen = length-offset-2;

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


void printRHP(FILE* f, RHP *x) {
    if (x->type == CONTROL_Message) {
        fprintf(f, "RHP:\n\ttype: CONTROL_Message\n\tdstPort: %d\n\tsrcPort: %d \n\tmessage: %s\n", 
            x->dstPort_length, x->srcPort, x->payload);
    } else if (x->type == RHMP_Message) {
        fprintf(f, "RHP:\n\ttype: RHMP_Message\n\tlength: %d\n\tsrcPort: %d\n\tpayload: ", 
            x->dstPort_length, x->srcPort);
        printAsHex(f, x->payload, x->payloadLen);
        fprintf(f, "\n");
    } else {
        fprintf(f, "Invalid RHP type %02x", x->type);
    }
}


