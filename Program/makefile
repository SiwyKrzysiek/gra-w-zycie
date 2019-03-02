CC=clang
DebugFlags=-std=c11 -Wall -g3 -D DEBUG
ReleseFlags=-Ofast -std=c11 -g0

NAME=main.exe

development: board.o parser.o
	$(CC) $(DebugFlags) -o $(NAME) board.o parser.o main.c

relese: # o. files are not compiled with correct flags
	$(CC) $(ReleseFlags) -o $(NAME) main.c

clean:
	rm -rf main.exe.dSYM
	rm *.o

board.o: board.c board.h
	$(CC) $(DebugFlags) -c board.c

parser.o: parser.c parser.h
	$(CC) $(DebugFlags) -c parser.c