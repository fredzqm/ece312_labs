#include "rhmp.h"

int writeRHMP(RHMP* rhmp, char* buffer);
int readRHMP(RHMP* rhmp, char* buffer);


void sendRHMPMessage(RHMP* sentRHMP, RHMP* responseRHMP) {
    char sentBuffer[BUFSIZE], recievedBuffer[BUFSIZE];

    printf("RHMP sent content:\n");
    printRHMP(sentRHMP, stdout);

    int offset = writeRHMP(sentRHMP, sentBuffer);

	RHP rhp, resp;
    rhp.type = RHMP_Message;
    rhp.dstPort_length = 105; 
    rhp.srcPort = 674;
    rhp.payload = sentBuffer;
    rhp.payloadLen = offset;

    resp.payload = recievedBuffer;
    
    printf("RHP sent content:\n");
    printRHP(&rhp, stdout);

    sendRHPMessage(&rhp, &resp);

    printf("RHP content:\n");
    printRHP(&resp, stdout);

    readRHMP(responseRHMP, resp.payload);
    
    printf("RHMP content:\n");
    printRHMP(responseRHMP, stdout);
}

int writeRHMP(RHMP* rhmp, char* buffer) {
    char type = rhmp->type;
    int commID = rhmp->commID;
    char length = rhmp->length;
    char* payload = rhmp->payload;
    
    int offset = 0;
    buffer[offset++] = (type & 0x3f) | ((commID << 6) & 0xc0);
    buffer[offset++] =  (commID>>2) & 0xff;
    buffer[offset++] = length;
    int i;
    for (i = 0; i < length; i++)
        buffer[offset++] = payload[i];
    return offset;
}

int readRHMP(RHMP* rhMp, char* buffer) {
    int a = buffer[0], b = buffer[1];
    char type = a & 0x3f;
    int commID = ((a>>6) & 0x03) | ((b<<2) & 0x3fc);
    int length = buffer[2];
    int i;
    for (i = 0; i < length-3; i++)
        rhMp->payload[i] = buffer[3+i];

    rhMp->type = type;
    rhMp->commID = commID;
    rhMp->length = length;
    return 0;
}


void printRHMP(RHMP *x, FILE* f) {
    char* type;
    if (x->type == ID_REQUEST) {
        type = "ID_REQUEST";
    } else if (x->type == ID_RESPONSE) {
        type = "ID_RESPONSE";
    } else if (x->type == MESSAGE_REQUEST) {
        type = "MESSAGE_REQUEST";
    } else if (x->type == MESSAGE_RESPONSE) {
        type = "MESSAGE_RESPONSE";
    } else {
        type = "Invalid";
    } 
    fprintf(f, "\ttype: %s\n\tcommitID: %d\n\tlength: %d \n\tpayload: %s\n", 
        type, x->commID, x->length, x->payload);
}


