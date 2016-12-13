# Makefile for echo client and echo server

CC = gcc
CFLAGS = -g -std=gnu99 -O -Wall -pthread -Wfatal-errors

all: client server

client: client.c client.h
	$(CC) $(CFLAGS) -o client client.c client.h

server: server.c server.h
	$(CC) $(CFLAGS) -o server server.c server.h

clean:
	rm -f *.o client server
	
