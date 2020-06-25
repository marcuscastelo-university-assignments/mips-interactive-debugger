#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "Executor.h"
#include "Program.h"
#include "Instruction.h"

#include <vector>
#include <string>
using namespace std;

class Debugger {
    protected:
        Program program;
        Executor executor;

    public:
        Debugger();
        Debugger(const Debugger& other);
		virtual ~Debugger();
        virtual void start(void);
        void exec(void);
        
        void info(const vector<string>& commandParts);
        void help(const vector<string>& commandParts = vector<string>(1));
        void disassemble(const vector<string>& commandParts);
        void breakpoint(const vector<string>& commandParts);
        bool parseInstruction(const string& command);
        bool executeInstructionAndVerify(const string& command);

        bool hasRegister(const string& name);

};

#endif
