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

        /*STRING PARSING*/
        command = string(tmp);
        command = trim(command);
        command = replaceAllChars(command, ',', ' ');
        commandParts = split(command);

        int size = commandParts.size();

        if (size == 0)
            continue;
        
        for (int i = 0; i < size; i++)
            commandParts[i] = trim(commandParts[i]);
        /****************/


        if (commandParts[0] == "quit")
            break;
        
        else if (commandParts[0] == "info") //TODO: info registers
            info(commandParts);

        else if (commandParts[0] == "help")
            help(commandParts);

        else if (commandParts[0] == "export")
            exportCode(commandParts);

        else if (commandParts[0] == "disassemble")
            disassemble(commandParts);

        else if (commandParts[0] == "b" or commandParts[0] == "break" or commandParts[0] == "break-remove"){
            breakpoint(commandParts);
        }

        else if (commandParts[0] == "r" or commandParts[0] == "run") {
            exec();
        }

        else {
            program->addInstruction(command);
        }

        // else {
        //     printf("Command not implemented yet\n");
        //     continue;
        // }
        
    }

    return;
}

void ConsoleDebugger::exec(void) {

}

void ConsoleDebugger::exportCode(vector<string> commandParts) {
    string name = "code.asm";

    //prevent to create files outside of the dir in which the program was executed
    if (commandParts.size() >= 2) {
        name = commandParts[1];
        auto pos = name.rfind("/");
        if (pos != string::npos) {
            name.erase(0, pos+1);
        }
    }
    
    FILE *file = fopen(name.c_str(), "w");
    program->printInstructions("", file);
    fclose(file);
    
    return;
}
