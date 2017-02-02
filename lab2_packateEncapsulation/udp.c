#include "udp.h"


int talkToServer(char* message, int messageLen, char* buffer) {
    int clientSocket, nBytes;
    struct sockaddr_in clientAddr, serverAddr;

    /*Create UDP socket*/
    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        perror("cannot create socket");
        exit(1);
    }

    /* Bind to an arbitrary return address.
     * Because this is the client side, we don't care about the address 
     * since no application will initiate communication here - it will 
     * just send responses 
     * INADDR_ANY is the IP address and 0 is the port (allow OS to select port) 
     * htonl converts a long integer (e.g. address) to a network representation 
     * htons converts a short integer (e.g. port) to a network representation */
    memset((char *) &clientAddr, 0, sizeof (clientAddr));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    clientAddr.sin_port = htons(0);
    if (bind(clientSocket, (struct sockaddr *) &clientAddr, sizeof (clientAddr)) < 0) {
        perror("bind failed");
        exit(2);
    }

    /* Configure settings in server address struct */
    memset((char*) &serverAddr, 0, sizeof (serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

    /* send a message to the server */
    if (sendto(clientSocket, message, messageLen, 0,
            (struct sockaddr *) &serverAddr, sizeof (serverAddr)) < 0) {
        perror("sendto failed");
        exit(3);
    }

    /* Receive message from server */
    nBytes = recvfrom(clientSocket, buffer, BUFSIZE, 0, NULL, NULL);
    if (nBytes < 0) {
        perror("sendto failed");
        exit(4);
    }
    close(clientSocket);
    return nBytes;
}



void printAsHex(FILE* f, char* buffer, int length) {
    for (int i = 0; i < length; i++) {
        if (i % 2 == 0)
            fprintf(f, " ");
        fprintf(f, "%02x", (int) (buffer[i] & 0xff));
    }
}