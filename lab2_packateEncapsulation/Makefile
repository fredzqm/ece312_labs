# Makefile for echo client and echo server

CC = gcc
CFLAGS = -g -std=gnu99 -O -Wall -Wfatal-errors
DEPS = io.h client.h server.h

all: client server

%.o: %.c ${DEPS}
	$(CC) -c -o $@ $< $(CFLAGS)

client: client.o
	$(CC) $(CFLAGS) client.o -o client 

server: server.o
	$(CC) $(CFLAGS) server.o -o server

clean:
	rm -rf *.o client server *.gch a.out*
	
