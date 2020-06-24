#include "Debugger.h"
#include <iostream>

using namespace std;

Debugger::Debugger() {
    program = new Program;
    executor = new Executor;
}

Debugger::~Debugger () {
    delete program;
    delete executor;
}

void Debugger::start (void) {

}

void Debugger::exec (void) {
    Register *reg = executor->getRegister("$pc");
    reg->setValue(0);

    while (true) {
        int pos = reg->getValueAsInt();
        string inst;

        try {
            inst = program->getInstruction(pos);
            printSingleInstruction(inst);
        } catch (std::out_of_range &e) {
            cout << e.what() << endl;
            break;
        }

        reg->setValue(pos+1);
    }
}

void Debugger::help (vector<string> commandParts) {
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

void Debugger::info(vector<string> commandParts) {
    if (commandParts.size() == 1) {
        printf("No argument to show help. See 'help info'\n");
        return ;
    }

    if (commandParts[1] == "registers") { 
        this->executor->getRegisters()->printRegisters();
    }

    // else if (commandParts[1] in registers_name_to_id.keys()) {
    //     print('-'*33)
    //     print_reg(commandParts[1])
    //     print('-'*33)

    else if (commandParts[1] == "labels") {
        program->printLabel();
    }

    else if (program->hasLabel(commandParts[1])) {
        program->printLabel(commandParts[1]);
    }
}

void Debugger::disassemble(vector<string> commandParts) {
    if (commandParts.size() == 1) {
        program->printInstructions();
        return;
    }
    
    size_t size = commandParts.size();
    for (size_t i = 1; i < size; i++) {
        if (program->hasLabel(commandParts[i]) == false)
            printf("Label '%s' undefined\n", commandParts[i].c_str());
        
        else
            program->printInstructions(commandParts[i]);
        
        printf("---------------\n");
    }
}

void Debugger::breakpoint(vector<string> commandParts) {
    if (commandParts.size() == 1) {
        printf("No argument with '%s'\n", commandParts[0].c_str());
        return;
    }

    if (commandParts[0] == "break-remove")
        program->removeBreakpoint(stoi(commandParts[1]));

    else
        program->addBreakpoint(stoi(commandParts[1]));
}

bool Debugger::parseInstruction(string command) {
    if (command.empty())
        return false;

    if (isLabel(command)) {
        string str = command;
        str.pop_back();
        if (hasRegister(command))
            return false;
    }

    return true;
}

bool Debugger::executeInstructionAndVerify(string command) {
    Instruction *executedInstruction = executor->executeInstruction(command);
    return executedInstruction->isValid();
}

bool Debugger::hasRegister(string name) {
    return executor->hasRegister(name);
}
