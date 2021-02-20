CC = g++ -std=c++17


CFLAGS = -g -Wall -c

all:  client server


server: server.cpp socket.o
	$(CC) -g -Wall server.cpp socket.o -o server

client: client.cpp socket.o
	$(CC) -g -Wall client.cpp socket.o -o client

clean:
	rm -rf *o main