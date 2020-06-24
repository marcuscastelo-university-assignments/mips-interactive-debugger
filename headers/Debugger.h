#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Executor.h"
#include "Program.h"

#include <vector>
#include <string>
using namespace std;

class Debugger {
    protected:
        Program *program;
        Executor *executor;

    public:
        Debugger();
		virtual ~Debugger();
        virtual void start(void);
        virtual void exec(void);


        void info(vector<string> commandParts);
        void help(vector<string> commandParts);
        void disassemble(vector<string> commandParts);
        void breakpoint(vector<string> commandParts);

};

#endif
