#include <stdio.h>

#include "DebuggerFunction.h"
#include "Help.h"


Help::Help (void) {

}

Help::~Help () {

}

void Help::exec (vector<string> command_parts) {
    if (command_parts.size() == 1) {
        printf("Help options:\n");
        printf("- console\n");
        printf("- run\n");
        printf("- disassemble\n");
        printf("- breakpoint\n");
        printf("- info\n");
        printf("- help\n");
        printf("- export\n");
        printf("- quit\n");
    }

    else {
        if (command_parts[1] == "console") {
            printf("Enter in console mode that allow to enter and execute code. Use \"-c\" flag to enter console mode. Use \"exit\" to exit console mode.\n");

            if (command_parts.size() == 2) {
                printf("Console help options:\n");
                printf("- data\n");
                printf("- text\n");
            }

            else {
                if (command_parts[2] == "text") {
                    printf("entrou2\n");
                    vector<string> instructions_accepted{"add", "addi", "j", "sub", "mul", "mult", "div", "rem", "bgez", "bgtz", "blez", "bltz", "beqz", "beq", "bne", "blt", "ble", "bgt", "bge", "bgezal", "bltzal", "mflo", "mfhi", "jal", "jalr", "jr", "and", "andi", "or", "ori", "xor", "xori", "li"};
                    printf("Enter instructions to be executed\n");
                    printf("List of instructions supported by the program:\n");
                    for (string i : instructions_accepted)
                        printf("- %s\n", i.c_str());
                    printf("Labels are accepted as well\n");
                }
            }
        }

        else if (command_parts[1] == "run") {
            printf("Run the code entered\n");
            printf("This command can also be used while in console mode\n");
        }

        else if (command_parts[1] == "disassemble") {
            printf("Show all code entered. Label name as argument prints the code from that label to the next label\n");
        }

        else if (command_parts[1] == "breakpoint" or command_parts[1] == "b") {
            printf("Insert breakpoint in given line\n"); 
        }

        else if (command_parts[1] == "info") {
            if (command_parts.size() == 2) {
                printf("- registers\n");    
                printf("- labels\n");
            }
            
            else {
                if (command_parts[2] == "registers") {
                    printf("Print a list of registers and their contents\n");
                    printf("Register name as argument makes the program describe only that register\n");
                }

                else if (command_parts[2] == "labels") {
                    printf("Print list of labels and their position in code\n");
                    printf("Register name as argument makes the program describe only that label\n");
                }

                else {
                    printf("Undefined command \'{command_parts[2]}\'\n");
                    return;
                }

                printf("This command can also be used while in console mode\n");
            }
        }

        else if (command_parts[1] == "import")
            printf("Import code in .asm file\n");

        else if (command_parts[1] == "export")
            printf("Export code entered in console mode as \"code.asm\"\n");

        else if (command_parts[1] == "help")
            printf("Print the list of commands\n");

        else if (command_parts[1] == "quit")
            printf("Exit debugger\n");

        else
            printf("Command \"%s\" does not exist. Use \"help\" to see commands\n", command_parts[0].c_str());
    }
}