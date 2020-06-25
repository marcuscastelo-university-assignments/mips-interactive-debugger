#ifndef __INTERPRETER__H__
#define __INTERPRETER__H__

#include "Instruction.h"

class Executor;
class Instruction;
class Interpreter
{
    private:
        Executor *parentExecutor;
    public:
        Interpreter(Executor *parentExecutor);
        Instruction *interpretInstruction(const std::string& instructionStr) const;
        ~Interpreter();
};



#endif  //!__INTERPRETER__H__