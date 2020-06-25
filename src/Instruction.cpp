#include "Instruction.h"

bool Instruction::isValid() {
    return type != UNKNOWN && (getIntegersCount() == getIntegersSupposedCount()) && (getRegistersCount() == getRegistersSupposedCount());
}

bool Instruction::isUnknown() {
    return type == UNKNOWN;
}

InstructionType Instruction::getType() {
    return type;
}

Instruction::Instruction() {
    this->type = UNKNOWN;
}

Instruction::Instruction(std::string repr, Executor *executor): Instruction() {
    this->repr = repr;
    this->executor = executor;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(Register*, Register*, Register*)) {
    executor_funcT_3R = executor_func;
    this->type = T_3R;
}


void Instruction::setExecutionFunction(void(Executor::*executor_func)(Register*, Register*)) {
    executor_funcT_2R = executor_func;
    this->type = T_2R;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(Register*)) {
    executor_funcT_1R = executor_func;
    this->type = T_1R;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(Register*, Register*, int)) {
    executor_funcT_2R_1I = executor_func;
    this->type = T_2R_1I;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(Register*, Register*, unsigned)) {
    executor_funcT_2R_1U = executor_func;
    this->type = T_2R_1U;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(Register*, int, int)) {
    executor_funcT_1R_2I = executor_func;
    this->type = T_1R_2I;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(Register*, int)) {
    executor_funcT_1R_1I = executor_func;
    this->type = T_1R_1I;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(int)) {
    executor_funcT_1I = executor_func;
    this->type = T_1I;
}

void Instruction::setExecutionFunction(void(Executor::*executor_func)(void)) {
    executor_funcT_V = executor_func;
    this->type = T_V;
}



Instruction *Instruction::feed(std::vector<Register*> newRegisters, std::vector<int> newIntegers) {
    registers.insert(registers.end(), newRegisters.begin(), newRegisters.end());
    integers.insert(integers.end(), newIntegers.begin(), newIntegers.end());
    return this;
}

void Instruction::execute() {
    if (type == UNKNOWN) fprintf(stderr, "WARNING: trying to execute UNKNOWN function.\n");
    else if (!isValid()) throw("Cannot execute invalid instruction");
    else if (type == T_3R) (executor->*executor_funcT_3R)(registers[0], registers[1], registers[2]);
    else if (type == T_2R) (executor->*executor_funcT_2R)(registers[0], registers[1]);
    else if (type == T_1R) (executor->*executor_funcT_1R)(registers[0]);
    else if (type == T_2R_1I) (executor->*executor_funcT_2R_1I)(registers[0], registers[1], integers[0]);
    else if (type == T_2R_1U) (executor->*executor_funcT_2R_1U)(registers[0], registers[1], (unsigned) integers[0]);
    else if (type == T_1R_2I) (executor->*executor_funcT_1R_2I)(registers[0], integers[0], integers[1]);
    else if (type == T_1R_1I) (executor->*executor_funcT_1R_1I)(registers[0], integers[0]);
    else if (type == T_1I) (executor->*executor_funcT_1I)(integers[0]);
    else if (type == T_V) (executor->*executor_funcT_V)();
}

int Instruction::getRegistersCount(){
    return registers.size();
}

int Instruction::getRegistersSupposedCount(){
    if (isUnknown()) return -1;
    else if(type == T_3R) return 3;
    else if(type == T_2R || type == T_2R_1I || type == T_2R_1U) return 2;
    else if(type == T_V) return 0;
    else return 1;
}

int Instruction::getIntegersCount(){
    return integers.size();
}


int Instruction::getIntegersSupposedCount(){
    if (isUnknown()) return -1;
    else if (type == T_3R || type == T_2R || type == T_1R || type == T_V) return 0;
    else if (type == T_1I || type == T_1R_1I || type == T_2R_1I || type == T_2R_1U) return 1;
    else if (type == T_1R_2I) return 2;
    else throw("Invalid instruction state");
}

std::string Instruction::toString() {
    return repr;
}