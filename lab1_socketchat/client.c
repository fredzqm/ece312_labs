/**
 * Lab09 Solution File - simple client for echo server
 * @author <your name here>
 * @author <your name here>
 */
#include "client.h"

#define DEFAULTPORT 5555   /* Default port for socket connection */
#define MAX_STRING_LEN 100 /* Maximum length of string to echo */
#define DEFAULT_SERVE_NAME "localhost"


int running = 1;
int sock;
char ip[MAX_STRING_LEN];

int main(int argc, char *argv[])
{
    /* Parse command line arguments */
    if (argc < 2) {
        usage();
    }

    int serv_port = DEFAULTPORT;         /* Server port */
    char* serv_name = DEFAULT_SERVE_NAME;                  /* Server host name */
    parseArgs(argc, argv, &serv_name, &serv_port);

    sock = connectSocket(serv_name, serv_port);
    printf("Connection established with %s\n", ip);

    char input_string[MAX_STRING_LEN];
    printf("Provide user name: ");
    fgets(input_string, MAX_STRING_LEN, stdin);
    input_string[strlen(input_string)-1] = 0;
    if (send(sock , input_string , strlen(input_string) , 0 ) < 0){
        die_with_error("send name not successful");
    }

    pthread_t pid;
    if (pthread_create(&pid, NULL, dataReciever, NULL)) {
        die_with_error("Thread not created");
    }

    while (running) { /* run until user enters "." to quit. */
        fgets(input_string, MAX_STRING_LEN, stdin);
        input_string[strlen(input_string)-1] = 0;
        send(sock , input_string , strlen(input_string) , 0 );
    }

    if (pthread_join(pid, NULL)) {
        printf("pthread_join() failed\n");
        exit(-1);
    }
    /* Close socket */
    fprintf(stdout, "closing");
    close(sock);
}

void *dataReciever(void* arg) {
    while(1){
        char received_string[MAX_STRING_LEN];
        int received_bytes = recv(sock , &received_string , MAX_STRING_LEN , 0);
        if (received_bytes <= 0)
            break;
        received_string[received_bytes] = 0;
        printf("%s\n", received_string);
    }
    running = 0;
    pthread_exit(NULL);
}

void parseArgs(int argc, char** argv, char** hostName, int* port) {
    int ch;
    while ((ch=getopt(argc, argv, "h:p:u")) != -1) {
    switch (ch) {
        case 'h':
            *hostName = optarg;
            printf("Using server %s\n", *hostName);
            break;
        case 'p':
            *port = atoi(optarg);
            printf("Using port %d\n", *port);
            break;
        case 'u':
        default:
            usage();
            break;
        }
    }
}

int connectSocket(char* serv_name, int serv_port) {
    /* Create a TCP socket */
    int sock;                                       /* Socket  */
    if((sock = socket(AF_INET , SOCK_STREAM , 0 ) ) < 0){
        die_with_error("socket error");
    }

    struct sockaddr_in serv_addr;                   /* Server address */
    /* Construct local address structure */
    memset(&serv_addr, 0, sizeof(serv_addr));       /* Zero out structure */
    serv_addr.sin_family = AF_INET;                 /* Internet address family */
    serv_addr.sin_addr.s_addr = resolve_name(serv_name); /* Server address */
    serv_addr.sin_port = htons(serv_port);          /* Local port */

    /* Connect to server socket */
    if (connect(sock , (struct sockaddr*) &serv_addr , sizeof(serv_addr) ) != 0){
        die_with_error("connect error");
    }
    return sock;
}

void die_with_error(char *error_message)
{
  perror(error_message);
  exit(1);
}


/* usage - print description of command arguments */
void usage()
{
  fprintf(stderr, "Usage: client [-u] [-v] -h <server> [-p <port>]\n");
  fprintf(stderr, "-u for usage\n");
  fprintf(stderr, "-v for verbose mode\n");
  fprintf(stderr, "-h for server name\n");
  fprintf(stderr, "-p for server port\n");
  exit(1);
}



int hostname_to_ip(char * hostname , char* ip)
{
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
         
    if ( (he = gethostbyname( hostname ) ) == NULL) 
    {
        herror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        ;
        return 0;
    }
    return 1;
}

/* resolve_name - convert a host name to an IP address */
unsigned long resolve_name (char name[])
{
  struct hostent *host;
  if ((host=gethostbyname(name)) == NULL) {
    fprintf(stderr, "gethostbyname() failed");
    exit(1);
  }

  struct in_addr ** addr_list = (struct in_addr **) host->h_addr_list;
  strcpy(ip , inet_ntoa(*addr_list[0]));
  return *((unsigned long *)host->h_addr_list[0]);
}
