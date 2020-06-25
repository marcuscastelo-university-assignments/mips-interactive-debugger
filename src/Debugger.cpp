#include "Debugger.h"

#include <iostream>
#include <string.h>

using namespace std;

Debugger::Debugger() {}

Debugger::Debugger(const Debugger& other) {}

Debugger::~Debugger () {}

void Debugger::start (void) {}

void Debugger::exec(int pos) {
    Register &reg = executor.getRegister("$pc");
    
    if (pos == -1)
        pos = reg.asInt();
    else
        reg.setWord(pos);

    while (true) {
        string inst;

        try {
            inst = program.getInstruction(pos);
            
            if (verifyLabel(inst) == true and executeInstructionAndVerify(inst) == true) {
                program.addInstruction(inst);
            }
            else {
                printf("Invalid instruction or syntax\n");
            }

        } catch (std::out_of_range &e) {
            break;
        }

        pos = reg.asInt();
        if (program.isBreakpoint(pos) == true) {
            printf("Breakpoint in in address '0x%4x'\n", pos);
            break;
        }
    }

    return;
}

void Debugger::next() {
    
}

void Debugger::help(const vector<string>& commandParts) {
    if (commandParts.size() <= 1) {
        printf("Help options:\n");
        printf("- console\n");
        printf("- run\n");
        printf("- disassemble\n");
        printf("- breakpoint\n");
        printf("- info\n");
        printf("- help\n");
        printf("- export\n");
        printf("- quit\n");
        return;
    }

    if (commandParts[1] == "console") {
        printf("Enter in console mode that allow to enter and execute code. Use \"-c\" flag to enter console mode. Use \"exit\" to exit console mode.\n");
        if (commandParts.size() == 2) {
            printf("Console help options:\n");
            printf("- data\n");
            printf("- text\n");
        }

        else {
            if (commandParts[2] == "text") {
                printf("entrou2\n");
                vector<string> instructions_accepted{"add", "addi", "j", "sub", "mul", "mult", "div", "rem", "bgez", "bgtz", "blez", "bltz", "beqz", "beq", "bne", "blt", "ble", "bgt", "bge", "bgezal", "bltzal", "mflo", "mfhi", "jal", "jalr", "jr", "and", "andi", "or", "ori", "xor", "xori", "li"};
                printf("Enter instructions to be executed\n");
                printf("List of instructions supported by the program:\n");
                for (string i : instructions_accepted)
                    printf("- %s\n", i.c_str());
                printf("Labels are accepted as well\n");
            }
        }

        return;
    }

    if (commandParts[1] == "run") {
        printf("Run the code entered\n");
        printf("This command can also be used while in console mode\n");
        return;
    }

    if (commandParts[1] == "disassemble") {
        printf("Show all code entered. Label name as argument prints the code from that label to the next label\n");
        return;
    }

    if (commandParts[1] == "breakpoint") {
        printf("'b' - Insert breakpoint in given line\n"); 
        printf("'break' - Insert breakpoint in given line\n");
        printf("'break-remove' - Delete breakpoint in given line\n"); 
        return;
    }

    if (commandParts[1] == "info") {
        printf("PS: This command can also be used while in console mode\n");
        if (commandParts.size() == 2) {
            printf("Info help options:\n");
            printf("- registers\n");    
            printf("- labels\n");
            printf("- breakpoints\n");
            return;
        }
        
        if (commandParts[2] == "registers") {
            printf("Print a list of registers and their contents\n");
            printf("Register name as argument makes the program describe only that register\n");
            return;
        }

        if (commandParts[2] == "labels") {
            printf("Print list of labels and their position in code\n");
            printf("Register name as argument makes the program describe only that label\n");
            return;
        }

        if (commandParts[2] == "breakpoints") {
            printf("Print list of breakpoints and their position in code\n");
            return;
        }

        printf("Unknown command \'%s\'\n", commandParts[2].c_str());
        return;
    }

    else if (commandParts[1] == "import")
        printf("Import code in .asm file\n");

    else if (commandParts[1] == "export")
        printf("Export code entered in console mode as \"code.asm\"\n");

    else if (commandParts[1] == "help")
        printf("Print the list of commands\n");

    else if (commandParts[1] == "quit")
        printf("Exit debugger\n");
    else
        printf("Command \"%s\" does not exist. Use \"help\" to see commands\n", commandParts[0].c_str());
}

void Debugger::info(const vector<string>& commandParts) {
    if (commandParts.size() == 1) {
        printf("No argument to show help. See 'help info'\n");
        return;
    }

    if (commandParts[1] == "registers") { 
        this->executor.getRegisters().printRegisters();
    }

    else if (this->executor.hasRegister(commandParts[1])) {
        this->executor.getRegister(commandParts[1]).print();
    }

    else if (commandParts[1] == "labels") {
        program.printLabel();
    }

    else if (program.hasLabel(commandParts[1])) {
        program.printLabel(commandParts[1]);
    }

    else if (commandParts[1] == "breakpoints") {
        program.printBreakpoints();
    }
}

void Debugger::disassemble(const vector<string>& commandParts) {
    if (commandParts.size() == 1) {
        program.printInstructions();
        return;
    }

    size_t size = commandParts.size();
    for (size_t i = 1; i < size; i++) {
        if (program.hasLabel(commandParts[i]) == false)
            printf("Label '%s' undefined\n", commandParts[i].c_str());
        
        else
            program.printInstructions(commandParts[i]);
        
        printf("---------------\n");
    }
}

void Debugger::breakpoint(const vector<string>& commandParts) {
    if (commandParts.size() == 1) {
        printf("No argument with '%s'\n", commandParts[0].c_str());
        return;
    }

    try {

        if (commandParts[0] == "break-remove")
            program.removeBreakpoint(stoi(commandParts[1]));
        else
            program.addBreakpoint(stoi(commandParts[1]));

    } catch (std::invalid_argument &e) {
        printf("Invalid argument to add breakpoint at. Use an int\n");
    } catch (std::out_of_range &e) {
        printf("%s\n", e.what());
    }

    return;
}

bool Debugger::verifyLabel(const string& command) {
    if (command.empty())
        return false;

    if (isLabel(command)) {
        string str = command;
        str.pop_back();
        if (hasRegister(command) or program.hasLabel(command))
            return false;
    }

    return true;
}

bool Debugger::executeInstructionAndVerify(const string& command) {
    Instruction *executedInstruction = executor.executeInstructionStr(command);
    return executedInstruction->isValid();
}

bool Debugger::hasRegister(const string& name) {
    return executor.hasRegister(name);
}
