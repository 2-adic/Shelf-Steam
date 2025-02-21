CC = gcc
CFLAGS = -Wall

shelf-steam: main.c shell.c shell_cmds.c utils.c config.c
	$(CC) $(CFLAGS) main.c shell.c shell_cmds.c utils.c config.c -o shelf-steam

clean:
	rm -f shelf-steam
