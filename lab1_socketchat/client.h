#include <arpa/inet.h>
#include <pthread.h>
#include <dirent.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "io.h"

void parseArgs(int argc, char** argv, char** hostName, int* port);
int connectSocket(char* serv_name, int serv_port, char* ip);

void usage();

void *dataReciever(void* arg);