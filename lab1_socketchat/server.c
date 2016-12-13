/**
 * @author zhangq2
 */
 
#include "server.h"

thread_data* ls;
int len, cap;
int running = 1;

int main(int argc, char** argv)
{
    int serv_port = DEFAULTPORT;
    parseArgs(argc, argv, &serv_port);  /* Server port */
    int sock = initializeSocket(serv_port);

    len = 1; cap = 5;
    ls = (thread_data*) malloc(sizeof(thread_data) * cap);
    if (ls == NULL) {
        die_with_error("malloc fails");
    }
    /* This thread is responsible for handling inputs from the server */
    ls[0].index = 0;
    ls[0].cid = 0;

    /* Spawn thread */
    if (pthread_create(&ls[0].tid, NULL, server_func, (void *) ls)) {
        perror("Thread not created");
        exit(0);
    }

    while(running) { /* run forever */
        struct sockaddr addr;
        socklen_t addrlen;
        /* Create a client socket for an accepted connection */
        int cid = accept(sock , &addr , &addrlen );
        if (cid <= 0) {
            die_with_error("accept error");
        }

        if (len + 1 == cap) {
            cap = cap*2;
            ls = (thread_data*) realloc(ls, sizeof(thread_data) * cap);
            if (ls == NULL) {
                die_with_error("malloc fails");
            }
        }
        /* Initialize thread with id number and pointer to file descriptor */
        ls[len].index = len;
        ls[len].cid = cid;
        /* Spawn thread */
        if (pthread_create(&ls[len].tid, NULL, thread_func, (void *) &ls[len])) {
            perror("Thread not created");
            exit(0);
        }
        len++;
    }
    
    /* Check status of thread */
    while (len > 0) {
        len--;
        if (pthread_join(ls[len].tid, NULL)) {
            printf("pthread_join() failed\n");
            exit(-1);
        }
    }

    /* Close the welcome socket */
    fprintf(stdout, "closing server");
    free(ls);
    close(sock);
}

int recievedDataFrom(int from, char* message) {
    int i;
    char sent[MAX_STRING_LEN];
    sprintf(sent, "<%s> %s", ls[from].name, message);
    for (i = 1; i < len; i++) {
        if (from != i) {
            send(ls[i].cid , sent , strlen(sent) , 0 );
            // send(ls[i].cid , sent , strlen(sent) , 0 );
        }
    }
    if (from != 0) {
        printf("%s\n", sent);
    }
    return 0;
}

void *thread_func(void *data_struct)
{
    thread_data* data = (thread_data*) data_struct;
    int index = data->index;
    int cid = data->cid;

    int numBytes = recv(cid , data->name , MAX_STRING_LEN , 0);
    if (numBytes <= 0)
        die_with_error("Recieve name not sucessful");

    while(1){
        char received_string[MAX_STRING_LEN];
        int numBytes = recv(cid , &received_string , MAX_STRING_LEN , 0);
        if (numBytes <= 0)
            break;
        received_string[numBytes] = 0;
        if (recievedDataFrom(index, received_string))
            break;
    }
    close(cid);
    printf("disconnected!\n");
    
    pthread_exit(NULL);
}

void *server_func(void *data_struct)
{
    thread_data* data = (thread_data*) data_struct;
    int index = data->index;

    printf("Provide user name: ");
    fgets(data->name, MAX_STRING_LEN, stdin);
    data->name[strlen(data->name)-1] = 0;

    while(1){
        char input_string[MAX_STRING_LEN];
        size_t size;
        fgets(input_string, MAX_STRING_LEN, stdin);
        input_string[strlen(input_string)-1] = 0;
        if (recievedDataFrom(index, input_string))
            break;
    }
    printf("disconnected!\n");
    
    pthread_exit(NULL);
}

/*
    initialize serv_port based on arguments
*/
void parseArgs(int argc, char** argv, int* port) {
    int optch;                        /* option flag */
    if (argc < 1) {
        usage();
    }
    while ((optch = getopt(argc, argv, "p:u")) != -1) {
        switch (optch) {
        case 'p':
            *port = atoi(optarg);
            printf("Using port %d\n", *port);
            break;
        case 'u':
        default:
            usage();
        }
    }
}

/*
    Creates a socket. handle the error it any step fails
*/
int initializeSocket(int serv_port) {
    /* Create a TCP socket - the welcome socket */
    int sock;                         /* Socket  */
    if( (sock = socket(AF_INET , SOCK_STREAM , 0 )) < 0){
        die_with_error("socket error");
    }
  
    /* Construct local address structure */
    struct sockaddr_in serv_addr;     /* Local address */
    memset(&serv_addr, 0, sizeof(serv_addr));      /* Zero out structure */
    serv_addr.sin_family = AF_INET;                /* Internet address family */
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    serv_addr.sin_port = htons(serv_port);         /* Local port */

    /* Bind to the local address */
    if( bind(sock , (struct sockaddr*)&serv_addr , sizeof(serv_addr)) != 0){
        die_with_error("bind error");
    }
    /* Wait for incoming requests */  
    if( listen( sock , MAX_STRING_LEN ) != 0 ){
        die_with_error("listen error");
    }
    return sock;
}

void usage() {
    fprintf(stderr, "Usage: server [-u] [-p <port>]\n");
    fprintf(stderr, "-u for usage\n");
    fprintf(stderr, "-p for server port\n");
    exit(1);
}

void die_with_error(char *errorMessage) {
    perror(errorMessage);
    exit(1);
}