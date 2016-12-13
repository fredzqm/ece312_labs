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
#include <netinet/in.h>
#include <arpa/inet.h>

void parseArgs(int argc, char** argv, char** hostName, int* port);
int connectSocket(char* serv_name, int serv_port);



void usage();
void die_with_error(char *error_message);
unsigned long resolve_name (char name[]);

void *dataReciever(void* arg);