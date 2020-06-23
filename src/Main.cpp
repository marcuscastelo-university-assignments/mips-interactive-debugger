#include "Debugger.h"
#include "ConsoleDebugger.h"
#include "FileDebugger.h"

#include <string>

int main (int argc, char *argv[]) {
    Debugger *debugger;
    
    if (argc == 1)
        debugger = new FileDebugger();

    else if (std::string(argv[1]) == "-c")
        debugger = new ConsoleDebugger();

    debugger->start();
    delete debugger;
}
