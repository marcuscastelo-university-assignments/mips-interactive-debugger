INC = -I ./headers
SRC = ./src
COMP = g++
FLAGS = -Wall

RULES = ConsoleDebugger Debugger FileDebugger

all: $(RULES)
	$(COMP) $(SRC)/Main.cpp *.o -o mipsdb $(INC) $(FLAGS)
	rm -f *.o

run: 
	./mipsdb

$(RULES):
	$(COMP) -c $(SRC)/$@.cpp $(INC) $(FLAGS)

