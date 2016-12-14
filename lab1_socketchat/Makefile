# Makefile for echo client and echo server

CC = gcc
CFLAGS = -g -std=gnu99 -O -Wall -pthread -Wfatal-errors
DEPS = io.h client.h server.h

all: client server

%.o: %.c ${DEPS}
	$(CC) -c -o $@ $< $(CFLAGS)

client: client.o io.o
	$(CC) $(CFLAGS) client.o io.o -o client 

server: server.o io.o
	$(CC) $(CFLAGS) server.o io.o -o server

clean:
	rm -rf *.o client server *.gch a.out*
	
