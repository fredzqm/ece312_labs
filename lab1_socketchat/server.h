#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define DEFAULTPORT 5555   /* Default port for socket connection */
#define MAX_STRING_LEN 100 /* Maximum length of string to echo */

typedef struct {
    int index;
    pthread_t tid;
    int cid;
} thread_data;

void parseArgs(int argc, char** argv, int* port);
int initializeSocket(int serv_port);

void die_with_error(char *errorMessage);
void usage();

void *thread_func(void *arg);
