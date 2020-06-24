#ifndef __INTERPRETER__H__
#define __INTERPRETER__H__

#include "Executor.h"
#include "Instruction.h"

class Interpreter
{
    private:
        Executor *parentExecutor;
    public:
        Interpreter(Executor *parentExecutor);
        Instruction interpretInstruction(std::string instruction);
        ~Interpreter();
};



#endif  //!__INTERPRETER__H__