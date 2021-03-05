CC=gcc

all: server client gui

client:
	$(CC) toy_client.c -o toy_client -pthread

server:
	$(CC) toy_server.c -o toy_server

gui:
	$(CC) curses_env.c -o curses_env -lncurses

clean:
	rm toy_server toy_client curses_env