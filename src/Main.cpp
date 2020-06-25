#include "Debugger.h"
#include "ConsoleDebugger.h"
#include "FileDebugger.h"
#include "Register.h"

#include "string_utils.h"

#include <string>
#include <signal.h>
#include <stdio.h>

//TODO: remover todos os "foda" do programa
void sigint_handler (int par) {
    fflush(stdin);
    return;
}

//TODO: delete
static void printByteArray(ByteArray *foda) {
    for (int i = 0; i < foda->getSize(); i++)
    {
        printf("%02X ", foda->getByteAt(i));
    }
    printf("\n");
    
}

int main (int argc, char *argv[]) {
    Register r("r", 4);
    Register a = r;


    a.print();
    return 0;










    signal(SIGINT, sigint_handler);
    Debugger *debugger;
    
    if (argc == 1) {
        printf("To enter in console mode, use the flag \'-c\'\n");
        debugger = new FileDebugger();
    }

    else if (std::string(argv[1]) == "-c")
        debugger = new ConsoleDebugger();
    else if (std::string(argv[1]) == "-h" or std::string(argv[1]) == "--help") {
        vector<string> command_parts;
        for (int i = 1; i < argc; i++) command_parts.push_back(argv[i]);        
        Debugger().help(command_parts);
        return 0;
    }
    else {
        fprintf(stderr, "ERROR: unknown flag \"%s\"\n", argv[1]);
        return 0;
    }

    debugger->start();
    delete debugger;
}
