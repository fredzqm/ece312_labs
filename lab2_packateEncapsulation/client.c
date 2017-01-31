/************* UDP CLIENT CODE *******************/

#include "rhmp.h"

int main() {
    char recieveBuffer[BUFSIZE];

// 1. send hello RHP message
    // char* message = "hello";
    // RHP rhpTo, rhpFrom;
    // rhpTo.type = CONTROL_Message;
    // rhpTo.dstPort_length = strlen(message) + 1; 
    // rhpTo.srcPort = 674;
    // rhpTo.payload = message;
    // rhpTo.payloadLen = strlen(message) + 1;
    
    // rhpFrom.payload = recieveBuffer;
    // printRHP(&rhpTo);
    // sendRHPMessage(&rhpTo, &rhpFrom);
    // printRHP(&rhpFrom);

// 2. request message
    RHMP rhmpsent1, rhmprecieved1;
    rhmpsent1.type = MESSAGE_REQUEST;
    rhmpsent1.commID = 312;
    rhmpsent1.length = 0;

    rhmprecieved1.payload = recieveBuffer;

    sendRHMPMessage(&rhmpsent1, &rhmprecieved1);
}




    