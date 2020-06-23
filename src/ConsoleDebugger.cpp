#include <stdio.h>
#include <string>

#include "ConsoleDebugger.h"
#include "Debugger.h"
#include "DebuggerFunction.h"

#include "string_utils.h"

using namespace std;

ConsoleDebugger::ConsoleDebugger(void) {

}

ConsoleDebugger::~ConsoleDebugger() {

}

void ConsoleDebugger::start (void) {
    char *tmp;
    string command;
    vector<string> command_parts;
    // DebuggerFunction *debuggerFunction;

    while (true) {
        printf("(MipsDB) >>> ");
        scanf(" %m[^\n\r]", &tmp);
        command = string(tmp);
        command_parts = split(command);
        if (command_parts.size() == 0)
            continue;

        if (command_parts[0] == "quit")
            break;
        
            

    } 
}
