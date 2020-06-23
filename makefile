INC = -I ./headers
SRC = ./src
COMP = g++
FLAGS = -Wall

CLASSES = ConsoleDebugger Debugger FileDebugger

all: $(CLASSES) string_utils
	$(COMP) $(SRC)/Main.cpp *.o -o mipsdb $(INC) $(FLAGS)
	rm -f *.o

rconsole: 
	./mipsdb -c

rfile:
	./mipsdb

$(CLASSES):
	$(COMP) -c $(SRC)/$@.cpp $(INC) $(FLAGS)

string_utils:
	$(COMP) -c $(SRC)/string_utils.cpp $(INC) $(FLAGS)

