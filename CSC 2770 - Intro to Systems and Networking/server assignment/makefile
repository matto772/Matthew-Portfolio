CC=g++
CFLAGS=-g -Wall -pedantic
LDFLAGS=-L. -lastyle-2.06d

all: server

server.o: server.cpp
	$(CC) -c $(CFLAGS) -o server.o server.cpp

server: server.o
	$(CC) $(CFLAGS) server.o $(LDFLAGS) -o server

run: server
	LD_LIBRARY_PATH=$(PWD) ./server

clean:
	rm -f server server.o