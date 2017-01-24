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
    
    sendRHPMessage(&rhp, &resp);

    resp.payload[resp.payloadLen] = 0;
    printf("RHP resp:\n\ttype: %d\n\tdstPort_length: %d\n\tsrcPort: %d \n\tpayload: %s\n", 
        resp.type, resp.dstPort_length, resp.srcPort, resp.payload);
}

