/************* UDP CLIENT CODE *******************/

#include "rhmp.h"

int main() {
// 1. send hello RHP message
    printf("----------------------------------- send hello RHP message\n");
    char* message = "hello";
    int len = strlen(message) + 1;
    RHP rhpTo, rhpFrom;
    rhpTo.type = CONTROL_Message;
    rhpTo.dstPort_length = len; 
    rhpTo.srcPort = 674;
    memcpy(rhpTo.payload, message, len);
    rhpTo.payloadLen = len;
    
    sendRHPMessage(&rhpTo, &rhpFrom);
    printRHP(stdout, &rhpFrom);

// 2. request message
    printf("----------------------------------- request message\n");
    RHMP rhmpsent, rhmprecieved;
    rhmpsent.type = MESSAGE_REQUEST;
    rhmpsent.commID = 312;
    rhmpsent.length = 0;

    rhmpsent.rhp.type = RHMP_Message;
    rhmpsent.rhp.dstPort_length = 105; 
    rhmpsent.rhp.srcPort = 674;

    sendRHMPMessage(&rhmpsent, &rhmprecieved);
    printRHP(stdout, &rhmprecieved.rhp);
    printRHMP(stdout, &rhmprecieved);


// 3. request id
    printf("----------------------------------- request id\n");
    rhmpsent.type = ID_REQUEST;
    rhmpsent.commID = 312;
    rhmpsent.length = 0;

    rhmpsent.rhp.type = RHMP_Message;
    rhmpsent.rhp.dstPort_length = 105; 
    rhmpsent.rhp.srcPort = 674;

    sendRHMPMessage(&rhmpsent, &rhmprecieved);
    printRHP(stdout, &rhmprecieved.rhp);
    printRHMP(stdout, &rhmprecieved);

}




    