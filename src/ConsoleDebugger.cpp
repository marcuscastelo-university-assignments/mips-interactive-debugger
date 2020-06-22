#include "ConsoleDebugger.h"
#include "Debugger.h"

using namespace std;

void Console::run (void) {
    char *tmp;
    string command;
    DebuggerCommand *debuggerCommand;

    while (true) {
        printf("(MIPSDB) >>> ");
        scanf(" %m[^\n\r]", &tmp);
        command = string(tmp);

        if (command == "quit")
            break;
        else
    } 
}
