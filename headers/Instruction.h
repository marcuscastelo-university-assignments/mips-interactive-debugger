#ifndef __INSTRUCTION__H__
#define __INSTRUCTION__H__

#include "Executor.h"
#include "Register.h"
#include <string>
#include <vector>

class Executor;
enum ExecutionType {
    T_UNKNOWN, T_3R, T_2R, T_1R, T_2R_1I, T_2R_2I, T_1R_1I, T_1I, T_1R_2I, T_2R_1U, T_V 
};

enum AdvancePcType {
    A_PASS = 0, A_NORMAL = 4 
};


class Instruction
{
    private:
        std::string repr;
        ExecutionType executionType;
        AdvancePcType advancePc;
        bool overloaded;
        std::string errorMessage;

        int supposedRegisterCount, supposedIntegerCount;
        int overloadedRegisterCount, overloadedIntegerCount;
        int typeRegisterCount, typeIntegerCount;

        std::vector<Register *> registers; 
        std::vector<int> integers;

        union {
            void (Executor::*T_3R)(Register*, Register*, Register*);
            void (Executor::*T_2R)(Register*, Register*);
            void (Executor::*T_1R)(Register*);
            void (Executor::*T_2R_1I)(Register*, Register*, int);
            void (Executor::*T_2R_2I)(Register*, Register*, int, int);
            void (Executor::*T_2R_1U)(Register*, Register*, unsigned);
            void (Executor::*T_1R_2I)(Register*, int, int);
            void (Executor::*T_1R_1I)(Register*, int);
            void (Executor::*T_1I)(int);
            void (Executor::*T_V)(void);
            void (Executor::*T_UNKNOWN)(nullptr_t);
        } executor_func;

    public:
        bool validate();
        ExecutionType getExecutionType();
        AdvancePcType getAdvancePcType();

        Instruction(const std::string& repr, AdvancePcType advanceType = A_NORMAL);
        Instruction(const Instruction& other);

        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*, Register*));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*, int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*,Register*,int, int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, Register*, unsigned));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, int, int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(Register*, int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(int));
        Instruction *setExecutionFunction(void (Executor::*executor_func_param)(void));
        Instruction *setExecutionFunction(void(Executor::*executor_func_param)(nullptr_t));

        Instruction *overloadSupposedRegisterCount(int count);
        Instruction *overloadSupposedIntegerCount(int count);

        Instruction *setOverloadedRegisterCount(int count);
        Instruction *setOverloadedIntegerCount(int count);
        Instruction *setSupposedRegisterCount(int count);
        Instruction *setSupposedIntegerCount(int count);

        void adjustParameters();
        void feed(const std::vector<Register*>& newRegisters, const std::vector<int>& newIntegers);

        const std::string& toString();
        const std::string& getErrorMessage();
        int getRegistersCount();
        int getIntegersCount();
        bool areParametersCountOK();
        bool hasOverload();

        void execute(Executor *executor);
};

#endif  //!__INSTRUCTION__H__