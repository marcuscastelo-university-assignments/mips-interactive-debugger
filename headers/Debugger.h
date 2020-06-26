#ifndef __DEBUGGER__H__
#define __DEBUGGER__H__

#include "Executor.h"
#include "Program.h"
#include "Instruction.h"

#include <vector>
#include <string>

class Debugger {
    protected:
        Program program;
        Executor executor(&program);

    public:
        Debugger();
        Debugger(const Debugger& other);
		virtual ~Debugger();
        virtual void start(void);
        void exec(int pos=-1);
        void next();
        
        void info(const std::vector<std::string>& commandParts);
        void help(const std::vector<std::string>& commandParts = std::vector<std::string>(1));
        void disassemble(const std::vector<std::string>& commandParts);
        void breakpoint(const std::vector<std::string>& commandParts);
        
        bool validatePossibleLabel(const std::string& command);
        bool executeInstructionAndVerify(const std::string& command);

        bool hasRegister(const std::string& name);

};

#endif
