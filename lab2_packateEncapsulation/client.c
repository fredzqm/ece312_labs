/************* UDP CLIENT CODE *******************/

#include "client.h"
#include "udp.h"

int main() {
    char* message = "Hello";

    printAsHex(message, strlen(message));
    printf("%s\n", message);

    RHP rhp, resp;

    rhp.type = 1;
    rhp.dstPort_length = strlen(message);
    rhp.srcPort = 682;
    rhp.payload = message;
    rhp.payloadLen = strlen(message);
    
    sendRHPMessage(&rhp, &resp);

    resp.payload[resp.payloadLen] = 0;
    printf("RHP resp:\n\ttype: %d\n\tdstPort_length: %d\n\tsrcPort: %d \n\tpayload: %s\n", 
        resp.type, resp.dstPort_length, resp.srcPort, resp.payload);
}

void sendRHPMessage(RHP* sent, RHP* response) {
    char sentBuffer[BUFSIZE], recieveBuffer[BUFSIZE];
    
    int offset = writeRHP(sent, sentBuffer);

    printf("set bytes as hex:\n");
    printAsHex(sentBuffer, offset);

    int nBytes = talkToServer(sentBuffer, offset, recieveBuffer);
    
    recieveBuffer[nBytes] = 0;
    printf("recieve bytes as hex:\n");
    printAsHex(recieveBuffer, nBytes);

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
    for (i = payloadLen-1; i >= 0; i--)
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


