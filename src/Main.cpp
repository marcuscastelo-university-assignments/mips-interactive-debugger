#include "Debugger.h"
#include "ConsoleDebugger.h"
#include "FileDebugger.h"

#include "string_utils.h"

#include <string>
#include <signal.h>
#include <stdio.h>

//TODO: remover todos os "foda" do programa
void sigint_handler (int par) {
    fflush(stdin);
    return;
}

int main (int argc, char *argv[]) {
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
