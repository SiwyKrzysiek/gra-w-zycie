CC=clang
DebugFlags=-std=c11 -Wall -g3 -D DEBUG
ReleseFlags=-Ofast -std=c11 -g0

NAME=main.exe

development: 
	$(CC) $(DebugFlags) -D DEBUG -o $(NAME) main.c

relese:
	$(CC) $(ReleseFlags) -o $(NAME) main.c

clean:
	rm -rf main.exe.dSYM