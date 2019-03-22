CC=clang
DebugFlags=-std=c11 -Wall -g3 -D DEBUG
ReleseFlags=-Ofast -std=c11 -g0
Libraries=cunit

Objects=board.o parser.o boardTest.o

NAME=main.exe

development: CompileFlags=$(DebugFlags)
development: $(Objects)
	$(CC) $(DebugFlags) `pkg-config --cflags --libs $(Libraries)` -o $(NAME) $(Objects) main.c

release: CompileFlags=$(ReleseFlags)
release: board.o parser.o
	$(CC) $(ReleseFlags) `pkg-config --cflags --libs $(Libraries)` -o $(NAME) $(Objects) main.c

rebuild: clean release

clean:
	rm -rf main.exe.dSYM
	rm -f *.o

# boardTest.o : boardTest.c boardTest.h
# 	$(CC) $(CompileFlags) `pkg-config --cflags --libs cunit` -c $< -o $@

%.o : %.c %.h
	$(CC) $(CompileFlags)  -c $< -o $@

# % - dowolne znaki. Jak już zadanie zostanie uruchomione to nie zmienia wargości
# $< - pierwsze wymaganie
# $@ - cała nazwa celu