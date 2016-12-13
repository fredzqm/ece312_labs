# Makefile for echo client and echo server

CC = gcc
CFLAGS = -g -std=gnu99 -O -Wall -pthread -Wfatal-errors

all: client server

client: client.c client.h
	$(CC) $(CFLAGS) client.c client.h > client

server: server.c server.h
	$(CC) $(CFLAGS) server.c server.h > server

clean:
	rm -f *.o client server
	
