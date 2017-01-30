/************* UDP CLIENT CODE *******************/

#include "rhp.h"

int main() {
    char* message = "h";

    RHMP rhp, resp;
    rhp.type = 1;
    rhp.dstPort_length = strlen(message);
    rhp.srcPort = 682;
    rhp.payload = message;
    rhp.payloadLen = strlen(message);
    
    sendRHPMessage(&rhp, &resp);

    RHMP send, respones;
    rhmp.type = REQUEST_MESSAGE;
    rhmp.commID = 312;
    rhmp.length = 0;

    free(resp.payload);
}

