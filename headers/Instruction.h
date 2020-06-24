#ifndef __INSTRUCTION__H__
#define __INSTRUCTION__H__

#include <string>
#include <functional>

#include "Register.h"

enum InstructionType {
    INVALID, T_3R, T_2R, T_1R, T_2R_1I, T_1R_1I, T_1I, T_1R_2I, T_2R_1U, T_V 
};

class Instruction
{
    private:
        std::string repr;
        InstructionType type;

        std::function<void (Register*, Register*, Register*)> executor_funcT_3R;
        std::function<void (Register*, Register*)> executor_funcT_2R;
        std::function<void (Register*)> executor_funcT_1R;
        std::function<void (Register*, Register*, int)> executor_funcT_2R_1I;
        std::function<void (Register*, Register*, unsigned)> executor_funcT_2R_1U;
        std::function<void (Register*, int, int)> executor_funcT_1R_2I;
        std::function<void (Register*, int)> executor_funcT_1R_1I;
        std::function<void (int)> executor_funcT_1I;
        std::function<void (void)> executor_funcT_V;

    public:
        bool isValid();
        Instruction(std::string repr, std::function<void (Register*, Register*, Register*)> executor_func);
        Instruction(std::string repr, std::function<void (Register*, Register*)> executor_func);
        Instruction(std::string repr, std::function<void (Register*)> executor_func);
        Instruction(std::string repr, std::function<void (Register*, Register*, int)> executor_func);
        Instruction(std::string repr, std::function<void (Register*, Register*, unsigned)> executor_func);
        Instruction(std::string repr, std::function<void (Register*, int, int)> executor_func);
        Instruction(std::string repr, std::function<void (Register*, int)> executor_func);
        Instruction(std::string repr, std::function<void (int)> executor_func);
        Instruction(std::string repr, std::function<void (void)> executor_func);
};

#endif  //!__INSTRUCTION__H__