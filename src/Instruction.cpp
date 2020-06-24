#include "Instruction.h"

bool Instruction::isValid() {
    return type != INVALID;
}

Instruction::Instruction(std::string repr, std::function<void (Register*, Register*, Register*)> executor_func) {
    executor_funcT_3R = executor_func;
    this->type = T_3R;
}

Instruction::Instruction(std::string repr, std::function<void (Register*, Register*)> executor_func) {
    executor_funcT_2R = executor_func;
    this->type = T_2R;
}

Instruction::Instruction(std::string repr, std::function<void (Register*)> executor_func) {
    executor_funcT_1R = executor_func;
    this->type = T_1R;
}

Instruction::Instruction(std::string repr, std::function<void (Register*, Register*, int)> executor_func) {
    executor_funcT_2R_1I = executor_func;
    this->type = T_2R_1I;
}

Instruction::Instruction(std::string repr, std::function<void (Register*, Register*, unsigned)> executor_func) {
    executor_funcT_2R_1U = executor_func;
    this->type = T_2R_1U;
}

Instruction::Instruction(std::string repr, std::function<void (Register*, int, int)> executor_func) {
    executor_funcT_1R_2I = executor_func;
    this->type = T_1R_2I;
}

Instruction::Instruction(std::string repr, std::function<void (Register*, int)> executor_func) {
    executor_funcT_1R_1I = executor_func;
    this->type = T_1R_1I;
}

Instruction::Instruction(std::string repr, std::function<void (int)> executor_func) {
    executor_funcT_1I = executor_func;
    this->type = T_1I;
}

Instruction::Instruction(std::string repr, std::function<void (void)> executor_func) {
    executor_funcT_V = executor_func;
    this->type = T_V;
}
