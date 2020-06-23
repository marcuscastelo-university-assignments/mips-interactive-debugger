#include <stdio.h>
#include <string>

#include "ConsoleDebugger.h"
#include "Debugger.h"

using namespace std;

ConsoleDebugger::ConsoleDebugger(void) {

}

ConsoleDebugger::~ConsoleDebugger() {

}

void ConsoleDebugger::start (void) {
    char *tmp;
    string command;
   // DebuggerCommand *debuggerCommand;

    while (true) {
        printf("(MipsDB) >>> ");
        scanf(" %m[^\n\r]", &tmp);
        command = string(tmp);

        if (command == "quit")
            break;
     //   else
    } 
}
