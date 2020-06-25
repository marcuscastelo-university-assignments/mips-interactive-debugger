#include <stdio.h>
#include <string>
#include <iostream>

#include "Registers.h"
#include "ConsoleDebugger.h"
#include "Debugger.h"

#include "string_utils.h"

using namespace std;

ConsoleDebugger::ConsoleDebugger(void) {
}

ConsoleDebugger::~ConsoleDebugger() {
}

void ConsoleDebugger::start (void) {
    string command;
    vector<string> commandParts;
        
    while (true) {
        printf("(MipsDB) >>> ");
        command = getLine();
        
        if (command.empty())
            continue;

        /*STRING PARSING*/        
        command = replaceAllChars(command, ',', ' ');
        commandParts = split(command);

        int size = commandParts.size();

        if (size == 0)
            continue;

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
            // TODO: adicionar somente se o executor não retornar erros (instrução não existente, etc...)
            if (parseInstruction(command) == true and executeInstructionAndVerify(command) == true) {
                program.addInstruction(command);
            }
            else {
                printf("Invalid instruction or syntax\n");
            }
        }
        
    }

    return;
}

void ConsoleDebugger::exportCode(vector<string> commandParts) {
    string name = "code.asm";

    //prevent to create files outside of the dir in which the program was executed
    if (commandParts.size() >= 2) {
        name = preventAbsolutePath(commandParts[1]);
    }

    FILE *file = fopen(name.c_str(), "w");
    program.printInstructions("", file);
    fclose(file);
    
    return;
}
