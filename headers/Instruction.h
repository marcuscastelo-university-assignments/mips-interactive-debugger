#ifndef __INSTRUCTION__H__
#define __INSTRUCTION__H__

#include "Executor.h"
#include "Register.h"
#include <string>
#include <vector>

class Executor;
enum ExecutionType {
    UNKNOWN, T_3R, T_2R, T_1R, T_2R_1I, T_1R_1I, T_1I, T_1R_2I, T_2R_1U, T_V 
};

enum AdvancePcType {
    NORMAL = 4, LINK = 8 
};


class Instruction
{
    private:
        std::string repr;
        ExecutionType executionType;
        AdvancePcType advancePc;
        std::string errorMessage;

        std::vector<Register *> registers; 
        std::vector<int> integers;

        int supposedRegisterCount, supposedIntegerCount, overloadedRegisterCount, overloadedIntegerCount;

        union {
            void (Executor::*T_3R)(Register*, Register*, Register*);
            void (Executor::*T_2R)(Register*, Register*);
            void (Executor::*T_1R)(Register*);
            void (Executor::*T_2R_1I)(Register*, Register*, int);
            void (Executor::*T_2R_1U)(Register*, Register*, unsigned);
            void (Executor::*T_1R_2I)(Register*, int, int);
            void (Executor::*T_1R_1I)(Register*, int);
            void (Executor::*T_1I)(int);
            void (Executor::*T_V)(void);
        } executor_func;

    public:
        bool validate();
        ExecutionType getExecutionType();

        Instruction(const std::string& repr, AdvancePcType advanceType = NORMAL);
        Instruction(const Instruction& other);
        ~Instruction();

        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*, Register*));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*, int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*, unsigned));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, int, int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(void));

        Instruction *overloadSupposedRegisterCount(int count);
        Instruction *overloadSupposedIntegerCount(int count);

        const std::string& toString();
        const std::string& getErrorMessage();
        int getRegistersCount();
        int getIntegersCount();
        bool isRegisterCountOK();
        bool isIntegerCountOK();

        void execute(Executor *executor);
        void feed(std::vector<Register*> newRegisters, std::vector<int> newIntegers);
};

#endif  //!__INSTRUCTION__H__