#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

#include "ConsoleDebugger.h"
#include "Debugger.h"

#include "string_utils.h"

using namespace std;

ConsoleDebugger::ConsoleDebugger(void) {
    program = new Program();
}

ConsoleDebugger::~ConsoleDebugger() {
    delete program;
}

void ConsoleDebugger::start (void) {
    char *tmp;
    string command;
    vector<string> commandParts;

    while (true) {
        printf("(MipsDB) >>> ");
        scanf("%m[^\n\r]", &tmp);
        if (tmp == NULL) {
            printf("\r");
            getchar();
            continue;
        }

        command = string(tmp);
        command = trim(command);
        commandParts = split(command);

        if (commandParts.size() == 0)
            continue;

        if (commandParts[0] == "quit")
            break;
        
        else if (commandParts[0] == "info")
            info(commandParts);

        else if (commandParts[0] == "help")
            help(commandParts);

        // else if (commandParts[0] == "export")
        //     debuggerFunction = new Export();

        else if (commandParts[0] == "disassemble")
            disassemble(commandParts);

        else if (commandParts[0] == "b"){
            program->removeBreakpoint(1000);
        }

        else {
            program->addInstruction(command);
        }

        // else {
        //     printf("Command not implemented yet\n");
        //     continue;
        // }
        
    }
}
