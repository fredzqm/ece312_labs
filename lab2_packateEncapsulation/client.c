/************* UDP CLIENT CODE *******************/

#include "rhp.h"

int main() {
    char* message = "h";

    RHP rhp, resp;

    rhp.type = 1;
    rhp.dstPort_length = strlen(message);
    rhp.srcPort = 682;
    rhp.payload = message;
    rhp.payloadLen = strlen(message);
    
    sendRHPMessage(&rhp, &resp);

    free(resp.payload);
}

