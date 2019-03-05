CC=clang
DebugFlags=-std=c11 -Wall -g3 -D DEBUG
ReleseFlags=-Ofast -std=c11 -g0

NAME=main.exe

development: CompileFlags=$(DebugFlags)
development: board.o parser.o
	$(CC) $(DebugFlags) -o $(NAME) board.o parser.o main.c

relese: CompileFlags=$(ReleseFlags)
relese: board.o parser.o
	$(CC) $(ReleseFlags) -o $(NAME) board.o parser.o main.c

rebuild: clean relese

clean:
	rm -rf main.exe.dSYM
	rm -f *.o

board.o: board.c board.h
	$(CC) $(CompileFlags) -c board.c

parser.o: parser.c parser.h
	$(CC) $(CompileFlags) -c parser.c