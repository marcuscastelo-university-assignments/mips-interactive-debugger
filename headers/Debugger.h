#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Program.h"

#include <vector>
#include <string>
using namespace std;

class Debugger {
    public:
        Debugger();
		virtual ~Debugger();
        virtual void start(void);

        void info(vector<string> commandParts);
        void help(vector<string> commandParts);
        void disassemble(vector<string> commandParts);
        void breakpoint(vector<string> commandParts);

    protected:
        Program *program;
};

#endif
