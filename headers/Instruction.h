#ifndef __INSTRUCTION__H__
#define __INSTRUCTION__H__

#include "Executor.h"
#include "Register.h"
#include <string>
#include <vector>

class Executor;

enum InstructionType {
    INVALID, T_3R, T_2R, T_1R, T_2R_1I, T_1R_1I, T_1I, T_1R_2I, T_2R_1U, T_V 
};

class Instruction
{
    private:
        std::string repr;
        InstructionType type;
        Executor *executor;

        std::vector<Register *> registers; 
        std::vector<int> integers;


        //TODO: union
        void (Executor::*executor_funcT_3R)(Register*, Register*, Register*);
        void (Executor::*executor_funcT_2R)(Register*, Register*);
        void (Executor::*executor_funcT_1R)(Register*);
        void (Executor::*executor_funcT_2R_1I)(Register*, Register*, int);
        void (Executor::*executor_funcT_2R_1U)(Register*, Register*, unsigned);
        void (Executor::*executor_funcT_1R_2I)(Register*, int, int);
        void (Executor::*executor_funcT_1R_1I)(Register*, int);
        void (Executor::*executor_funcT_1I)(int);
        void (Executor::*executor_funcT_V)(void);

    public:
        bool isValid();
        Instruction(std::string repr, Executor *executor);
        Instruction(nullptr_t null);


        void setExecutionFunction(void (Executor::*executor_func)(Register*, Register*, Register*));
        void setExecutionFunction(void (Executor::*executor_func)(Register*, Register*));
        void setExecutionFunction(void (Executor::*executor_func)(Register*));
        void setExecutionFunction(void (Executor::*executor_func)(Register*, Register*, int));
        void setExecutionFunction(void (Executor::*executor_func)(Register*, Register*, unsigned));
        void setExecutionFunction(void (Executor::*executor_func)(Register*, int, int));
        void setExecutionFunction(void (Executor::*executor_func)(Register*, int));
        void setExecutionFunction(void (Executor::*executor_func)(int));
        void setExecutionFunction(void (Executor::*executor_func)(void));

        void execute();
        Instruction *feed(std::vector<Register*> newRegisters, std::vector<int> newIntegers);
};

#endif  //!__INSTRUCTION__H__