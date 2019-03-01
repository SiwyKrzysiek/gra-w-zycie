CC=gcc
CFLAGS=-std=c11 -Wall -g3

NAME=main.exe

development: 
	$(CC) $(CFLAGS) -D DEBUG -o $(NAME) main.c

relese:
	$(CC) -Ofast -std=c11 -g0 -o $(NAME) main.c

clean:
	echo "Not implemented"