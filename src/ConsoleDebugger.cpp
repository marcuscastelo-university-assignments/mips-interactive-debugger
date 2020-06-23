#include <stdio.h>
#include <string>

#include "ConsoleDebugger.h"
#include "Debugger.h"
#include "DebuggerFunction.h"
#include "Help.h"
#include "Info.h"

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

    DebuggerFunction *debuggerFunction;

    while (true) {
        printf("(MipsDB) >>> ");
        scanf("%m[^\n\r]", &tmp);
        if (tmp == NULL) {
            printf("\r");
            getchar();
            continue;
        }

        command = string(tmp);
        command_parts = split(command);
        
        if (command_parts.size() == 0)
            continue;

        if (command_parts[0] == "quit")
            break;
        
        else if (command_parts[0] == "info")
            debuggerFunction = new Info();

        else if (command_parts[0] == "help")
            debuggerFunction = new Help();

        else {
            printf("Command not implemented yet\n");
            continue;
        }

        debuggerFunction->exec();
        delete debuggerFunction;
    } 
}
