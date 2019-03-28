CC=clang
DebugFlags=-std=c11 -Wall -g3 -D DEBUG -D TESTS
ReleseFlags=-Ofast -std=c11 -g0
Libraries=cunit libpng

## Here add names of modules (.h, .c) files that should be compiled (with .o extension)
# It is assumed that each one has .h and .c file
Objects=BoardHandler.o Loader.o ArgumentsParser.o GraphicsGenerator.o gifenc.o Rules.o Simulator.o
## Here add names of test modules
TestObjects=boardTest.o

NAME=main.exe

development: CompileFlags=$(DebugFlags)
development: $(Objects) $(TestObjects)
	$(CC) $(DebugFlags) `pkg-config --cflags --libs $(Libraries)` -o $(NAME) $(Objects) $(TestObjects) main.c

release: CompileFlags=$(ReleseFlags)
release: $(Objects)
	$(CC) $(ReleseFlags) `pkg-config --cflags --libs $(Libraries)` -o $(NAME) $(Objects) main.c

rebuild: clean release

clean:
	rm -rf main.exe.dSYM
	rm -f *.o

%.o : %.c %.h
	$(CC) $(CompileFlags)  -c $< -o $@

# % - dowolne znaki. Jak już zadanie zostanie uruchomione to nie zmienia wargości
# $< - pierwsze wymaganie
# $@ - cała nazwa celu