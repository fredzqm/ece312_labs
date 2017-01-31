/************* UDP CLIENT CODE *******************/

#include "rhmp.h"

int main() {
// 1. send hello RHP message
    char* message = "hello";
    int len = strlen(message) + 1;
    RHP rhpTo, rhpFrom;
    rhpTo.type = CONTROL_Message;
    rhpTo.dstPort_length = len; 
    rhpTo.srcPort = 674;
    memcpy(rhpTo.payload, message, len);
    rhpTo.payloadLen = len;
    
    printRHP(&rhpTo, stdout);
    sendRHPMessage(&rhpTo, &rhpFrom);
    printRHP(&rhpFrom, stdout);

// 2. request message
    RHMP rhmpsent1, rhmprecieved1;
    rhmpsent1.type = MESSAGE_REQUEST;
    rhmpsent1.commID = 312;
    rhmpsent1.length = 0;
    rhmpsent1.rhp.type = RHMP_Message;
    rhmpsent1.rhp.dstPort_length = 105; 
    rhmpsent1.rhp.srcPort = 674;

    sendRHMPMessage(&rhmpsent1, &rhmprecieved1);
}




    