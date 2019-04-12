CC=clang
DebugFlags=-std=c11 -Wall -g3
ReleseFlags=-Ofast -std=c11 -g0
Libraries=libpng

## Here add names of modules (.h, .c) files that should be compiled (with .o extension)
# It is assumed that each one has .h and .c file
Objects=BoardHandler.o Loader.o ArgumentsParser.o GraphicsGenerator.o gifenc.o Rules.o Simulator.o Saver.o
## Here add names of test modules
TestObjects=boardTest.o LoaderTest.o RulesTest.o SimulatorTest.o

NAME=game-of-life

release: CompileFlags=$(ReleseFlags)
release: $(Objects)
	$(CC) $(CompileFlags) `pkg-config --cflags --libs $(Libraries)` -o $(NAME) $(Objects) main.c

rebuild: clean release

development: CompileFlags=$(DebugFlags) -D DEBUG
development: $(Objects)
	$(CC) $(CompileFlags) `pkg-config --cflags --libs $(Libraries)` -o $(NAME) $(Objects) main.c

tests: CompileFlags=$(DebugFlags) -D TESTS
tests: TestLibraries=$(Libraries) cunit
tests: $(Objects) $(TestObjects)
	$(CC) $(CompileFlags) `pkg-config --cflags --libs $(TestLibraries)` -o $(NAME) $(Objects) $(TestObjects) main.c

clean:
	rm -rf game-of-life.dSYM
	rm -f *.o

GraphicsGenerator.o: GraphicsGenerator.c GraphicsGenerator.h
	$(CC) $(CompileFlags)  `pkg-config --cflags libpng` -c $< -o $@


%Test.o : %Test.c %Test.h
	$(CC) $(CompileFlags)  `pkg-config --cflags cunit` -c $< -o $@

%.o : %.c %.h
	$(CC) $(CompileFlags)  `pkg-config --cflags $(Libraries)` -c $< -o $@

# % - dowolne znaki. Jak już zadanie zostanie uruchomione to nie zmienia wargości
# $< - pierwsze wymaganie
# $@ - cała nazwa celu
