#ifndef __INSTRUCTION__H__
#define __INSTRUCTION__H__

#include "Executor.h"
#include "Register.h"
#include <string>

class Executor;

enum InstructionType {
    INVALID, T_3R, T_2R, T_1R, T_2R_1I, T_1R_1I, T_1I, T_1R_2I, T_2R_1U, T_V 
};

class Instruction
{
    private:
        std::string repr;
        InstructionType type;

        std::vector<Register *> registers; 
        std::vector<int> integers;

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
        Executor *executor;
        bool isValid();
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(Register*, Register*, Register*));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(Register*, Register*));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(Register*));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(Register*, Register*, int));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(Register*, Register*, unsigned));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(Register*, int, int));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(Register*, int));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(int));
        Instruction(std::string repr, Executor *executor, void (Executor::*executor_func)(void));
        Instruction(nullptr_t null);

        void execute();
        Instruction *add(int integer);
        Instruction *add(Register *reg);
        Instruction *add(std::vector<int> newIntegers);
        Instruction *add(std::vector<Register*> newRegisters);
};

#endif  //!__INSTRUCTION__H__