#include <stdio.h>
#include <string>
#include <iostream>

#include "Registers.h"
#include "ConsoleDebugger.h"
#include "Debugger.h"

#include "string_utils.h"

ConsoleDebugger::ConsoleDebugger(void) {
}

ConsoleDebugger::~ConsoleDebugger() {
}

void ConsoleDebugger::start (void) {
    std::string command, commandWithCommas;
    std::vector<std::string> commandParts;
        
    while (true) {
        printf("(MipsDB) >>> ");
        commandWithCommas = getLine();
        commandWithCommas = removeComments(commandWithCommas);
        command = commandWithCommas;
        
        if (command.empty())
            continue;

        /*STRING PARSING*/        
        command = removeAllChars(command, ',');
        commandParts = split(command);
        commandParts = trimVec(commandParts);

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

        else if (commandParts[0] == "r" or commandParts[0] == "run")
            exec(-4);

        else if (commandParts[0] == "c" or commandParts[0] == "continue")
            exec();

        else if (commandParts[0] == "n" or commandParts[0] == "next") {
            try {
                next();
            } catch (std::out_of_range &e) {
                printf("There is no next instruction to be executed\n");
            }
        }

        else {
            //verifyLabel() verifies if a possible label is valid, or if it is not a label at all, returning true
            //if it is a in fact label, and is not valid, returns false
            Registers previousRegisters = this->executor.getRegisters();

            if (validatePossibleLabel(command) == true and executeInstructionAndVerify(command) == true) {
                program.addInstruction(commandWithCommas);
                printModifiedRegisters(previousRegisters,this->executor.getRegisters());            
            } 
        }
        
    }

    return;
}

void ConsoleDebugger::printModifiedRegisters(const Registers& oldRegisters, const Registers& newRegisters){
    std::map<std::string, Register*> oldRegisterMap = oldRegisters.getRegisterMap();
    bool modified = false;
    printf("Modified Registers: Old Value -> New Value:\n");
    for(auto it = oldRegisterMap.begin(); it != oldRegisterMap.end(); it++){
        if(it->second->asInt() != newRegisters.getRegisterByName(it->first).asInt()){
            if(!modified) modified = true;             
            printf("\t%s: %d\t->\t%d\n",it->first.c_str(),it->second->asInt(),newRegisters.getRegisterByName(it->first).asInt());
        }
    }
    if(!modified) printf("\tNo Register has been modified.\n");

}

void ConsoleDebugger::exportCode(std::vector<std::string> commandParts) {
    std::string name = "code.asm";

    //prevent to create files outside of the dir in which the program was executed
    if (commandParts.size() >= 2) {
        name = preventAbsolutePath(commandParts[1]);
    }

    FILE *file = fopen(name.c_str(), "w");
    program.printInstructions("", file);
    fclose(file);
    
    return;
}
