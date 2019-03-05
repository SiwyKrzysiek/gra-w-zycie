CC=clang
DebugFlags=-std=c11 -Wall -g3 -D DEBUG
ReleseFlags=-Ofast -std=c11 -g0

Objects=board.o parser.o

NAME=main.exe

development: CompileFlags=$(DebugFlags)
development: $(Objects)
	$(CC) $(DebugFlags) -o $(NAME) $(Objects) main.c

relese: CompileFlags=$(ReleseFlags)
relese: board.o parser.o
	$(CC) $(ReleseFlags) -o $(NAME) $(Objects) main.c

rebuild: clean relese

clean:
	rm -rf main.exe.dSYM
	rm -f *.o

%.o : %.c %.h
	$(CC) $(CompileFlags) -c $< -o $@

# % - dowolne znaki. Jak już zadanie zostanie uruchomione to nie zmienia wargości
# $< - pierwsze wymaganie
# $@ - cała nazwa celu