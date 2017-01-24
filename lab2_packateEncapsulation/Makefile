# Makefile for echo client and echo server

CC = gcc
CFLAGS = -g -std=gnu99 -O -Wall -Wfatal-errors

all: client

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)

client: client.o udp.o
	$(CC) $(CFLAGS) client.o udp.o -o client 

clean:
	rm -rf *.o client server *.gch a.out* server.dSYM
	
