INC = -I ./headers
SRC = ./src
COMP = g++
FLAGS = -Wall

CLASSES = ConsoleDebugger Debugger Executor FileDebugger Program Register ByteArray Registers Word Instruction Interpreter

all: $(CLASSES) string_utils
	$(COMP) $(SRC)/Main.cpp *.o -o mipsdb $(INC) $(FLAGS)
	rm -f *.o

run: rconsole

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

