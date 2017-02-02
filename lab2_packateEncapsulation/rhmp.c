#include "rhmp.h"

int writeRHMP(RHMP* rhmp, char* buffer);
void readRHMP(RHMP* rhmp, char* buffer);


void sendRHMPMessage(RHMP* sentRHMP, RHMP* responseRHMP) {

    sentRHMP->rhp.payloadLen = writeRHMP(sentRHMP, sentRHMP->rhp.payload);

    sendRHPMessage(&sentRHMP->rhp, &responseRHMP->rhp);

    readRHMP(responseRHMP, responseRHMP->rhp.payload);
}

int writeRHMP(RHMP* rhmp, char* buffer) {
    int offset = 0;
    buffer[offset++] = (rhmp->type & 0x3f) | ((rhmp->commID << 6) & 0xc0);
    buffer[offset++] =  (rhmp->commID>>2) & 0xff;
    buffer[offset++] = rhmp->length;
    int i;
    for (i = 0; i < rhmp->length; i++)
        buffer[offset++] = rhmp->payload[i];
    return offset;
}

void readRHMP(RHMP* rhMp, char* buffer) {
    int a = buffer[0], b = buffer[1];
    rhMp->type = a & 0x3f;
    rhMp->commID = ((a>>6) & 0x03) | ((b<<2) & 0x3fc);
    rhMp->length = buffer[2];
    int i;
    for (i = 0; i < rhMp->length; i++)
        rhMp->payload[i] = buffer[3+i];
}


void printRHMP(FILE* f, RHMP *x) {
    if (x->type == ID_REQUEST) {
        fprintf(f, "RHMP:\n\ttype: ID_REQUEST\n\tcommitID: %d\n\tlength: %d \n", 
            x->commID, x->length);
    } else if (x->type == ID_RESPONSE) {
        int id = x->payload[3];
        id = (id << 8) | (((int)x->payload[2]) & 0xff);
        id = (id << 8) | (((int)x->payload[1]) & 0xff);
        id = (id << 8) | (((int)x->payload[0]) & 0xff);
        fprintf(f, "RHMP:\n\ttype: ID_RESPONSE\n\tcommitID: %d\n\tlength: %d \n\tID: %d\n", 
            x->commID, x->length, id);
    } else if (x->type == MESSAGE_REQUEST) {
        fprintf(f, "RHMP:\n\ttype: MESSAGE_REQUEST\n\tcommitID: %d\n\tlength: %d \n", 
            x->commID, x->length);
    } else if (x->type == MESSAGE_RESPONSE) {
        fprintf(f, "RHMP:\n\ttype: MESSAGE_RESPONSE\n\tcommitID: %d\n\tlength: %d \n\tMessage: %s\n", 
            x->commID, x->length, x->payload);
    } else {
        fprintf(f, "Invalid RHMP type %02x", x->type);
    } 
}


