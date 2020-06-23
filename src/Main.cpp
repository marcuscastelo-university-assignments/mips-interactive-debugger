#include "Debugger.h"
#include "ConsoleDebugger.h"
#include "FileDebugger.h"

#include <string>
#include <signal.h>

void sigint_handler (int par) {
    fflush(stdin);
    return;
}

int main (int argc, char *argv[]) {
    signal(SIGINT, sigint_handler);
    Debugger *debugger;
    
    if (argc == 1)
        debugger = new FileDebugger();

    else if (std::string(argv[1]) == "-c")
        debugger = new ConsoleDebugger();

    debugger->start();
    delete debugger;
}
