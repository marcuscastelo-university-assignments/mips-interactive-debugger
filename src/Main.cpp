#include "Debugger.h"
#include "ConsoleDebugger.h"
#include "FileDebugger.h"

#include <string>
#include <signal.h>
#include <stdio.h>

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

    debugger->start();
    delete debugger;
}
