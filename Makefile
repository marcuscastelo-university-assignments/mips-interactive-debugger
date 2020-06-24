INC = -I ./headers
SRC = ./src
COMP = g++
FLAGS = -Wall

CLASSES = ConsoleDebugger Debugger Executor FileDebugger Program Register Registers Stack Word Instruction Interpreter

all: $(CLASSES) string_utils
	$(COMP) $(SRC)/Main.cpp *.o -o mipsdb $(INC) $(FLAGS)
	rm -f *.o

run: rfile

rfile: all
	./mipsdb

rconsole:
	./mipsdb -c

$(CLASSES):
	$(COMP) -c $(SRC)/$@.cpp $(INC) $(FLAGS)

string_utils:
	$(COMP) -c $(SRC)/string_utils.cpp $(INC) $(FLAGS)

gdb:
	gdb mipsdb

