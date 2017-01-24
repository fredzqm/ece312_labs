/************* UDP CLIENT CODE *******************/

#include "rhp.h"

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
    
    printRHP(&rhp);

    sendRHPMessage(&rhp, &resp);

    resp.payload[resp.payloadLen] = 0;

    printRHP(&resp);

    free(resp.payload);
}

