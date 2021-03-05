CC=gcc

all: server client

client:
	$(CC) toy_client.c -o toy_client -pthread

server:
	$(CC) toy_server.c -o toy_server

clean:
	rm toy_server toy_client