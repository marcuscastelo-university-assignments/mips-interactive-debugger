#include "Debugger.h"
#include "FileDebugger.h"
#include "string_utils.h"
#include <iostream>


FileDebugger::FileDebugger (void) {
    program= new Program();
}

FileDebugger::~FileDebugger () {
    delete program;
}

void FileDebugger::start (void) {
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

        else if (commandParts[0] == "file")
            importCode(commandParts);

        else if (commandParts[0] == "disassemble")
            disassemble(commandParts);

        else if (commandParts[0] == "b" or commandParts[0] == "break" or commandParts[0] == "break-remove"){
            breakpoint(commandParts);
        }

        else if (commandParts[0] == "r" or commandParts[0] == "run") {
            exec();
        }
    }
}

void FileDebugger::exec (void) {
    
}

void FileDebugger::importCode (vector<string> commandParts) {
    
}
