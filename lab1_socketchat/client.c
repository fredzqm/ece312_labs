/**
 * Lab09 Solution File - simple client for echo server
 * @author <your name here>
 * @author <your name here>
 */
#include "client.h"

#define DEFAULTPORT 5555   /* Default port for socket connection */
#define MAX_STRING_LEN 100 /* Maximum length of string to echo */
#define DEFAULT_SERVE_NAME "localhost"

int main(int argc, char *argv[])
{
    /* Parse command line arguments */
    if (argc < 2) {
        usage();
    }

    int serv_port = DEFAULTPORT;         /* Server port */
    char* serv_name = DEFAULT_SERVE_NAME;                  /* Server host name */
    parseArgs(argc, argv, &serv_name, &serv_port);

    int sock = connectSocket(serv_name, serv_port);

    while (1) { /* run until user enters "." to quit. */
        char input_string[MAX_STRING_LEN];
        char received_string[MAX_STRING_LEN];
        int received_bytes = 0;
        /* Prompt user for string to echo and read in the string.
         *  String may have spaces.
         */
        printf("\n\nEnter the string(\".\" to quit):");
        fgets(input_string, MAX_STRING_LEN, stdin);
        input_string[strlen(input_string)-1] = '\0';
        if (input_string[0] == '.') {
            break;
        }

        /* Send string to server */
        if( send(sock , input_string , strlen(input_string) , 0 ) < 0){
            break;
        }
        /* Block until message received from the server */
        received_bytes = recv(sock , received_string , MAX_STRING_LEN , 0);
        if(received_bytes < 0){
            break;
        }
        received_string[received_bytes] = 0;
        /* Print the received string. */
        fprintf(stdout, "sending string: %s", received_string);      
    }
    /* Close socket */
    fprintf(stdout, "closing");
    close(sock);
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
        // get the host info
        herror("gethostbyname");
        return 1;
    }
 
    addr_list = (struct in_addr **) he->h_addr_list;
     
    for(i = 0; addr_list[i] != NULL; i++) 
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
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
  return *((unsigned long *)host->h_addr_list[0]);
}
