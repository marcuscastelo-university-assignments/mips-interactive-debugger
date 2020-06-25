#include "Instruction.h"

#include <sstream>

bool Instruction::validate() {
    if (!errorMessage.empty()) return false;

    bool hasSomeError = false;

    if (executionType == UNKNOWN){
        errorMessage += "Unknown instruction: " + toString() + ".\n";        
        return false;
    }
    if (!isIntegerCountOK()){
        std::stringstream correctNumberOfInts;
        if (supposedIntegerCount == overloadedIntegerCount) correctNumberOfInts << supposedIntegerCount;
        else correctNumberOfInts << supposedIntegerCount << "/" << overloadedIntegerCount;
        
        errorMessage += "Incorrect number of Integers:\n\tCorrect Number: " + correctNumberOfInts.str() + ", Given Number: " + std::to_string(getIntegersCount()) + "\n";
        hasSomeError = true;
    }
    if (!isRegisterCountOK()) {
        std::stringstream correctNumberOfRegs;
        if (supposedIntegerCount == overloadedIntegerCount) correctNumberOfRegs << supposedRegisterCount;
        else correctNumberOfRegs << supposedRegisterCount << "/" << overloadedRegisterCount;

        errorMessage += "Incorrect number of Registers:\n\tCorrect Number: " + correctNumberOfRegs.str() + ", Given Number: " + std::to_string(getRegistersCount()) + "\n";
        hasSomeError = true;
    }
    if (hasSomeError) return false;
    
    //Checks if user is trying to modify read-only register
    if(registers[0]->isReadOnly()){
        errorMessage += "Invalid attribution of value to register " + registers[0]->getName() + ", which is read only.\n";
        return false; 
    }
    
    return true;
}

ExecutionType Instruction::getExecutionType() {
    return executionType;
}

Instruction::Instruction(const std::string& repr, AdvancePcType advancePc)
: repr(repr), executionType(UNKNOWN), errorMessage(""), advancePc(advancePc){ }

Instruction::Instruction(const Instruction& other)
: repr(other.repr), executionType(other.executionType), errorMessage(""), advancePc(other.advancePc), overloadSupposedRegisterCount(other.supposedRegisterCount), supposedIntegerCount(other.supposedIntegerCount) {}

Instruction::~Instruction() {}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*, Register*)) {
    supposedRegisterCount = 3;
    supposedIntegerCount = 0;
    this->executor_func.T_3R = executor_func_param;
    this->executionType = T_3R;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*)) {
    supposedRegisterCount = 2;
    supposedIntegerCount = 0;
    this->executor_func.T_2R = executor_func_param;
    this->executionType = T_2R;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*)) {
    supposedRegisterCount = 1;
    supposedIntegerCount = 0;
    this->executor_func.T_1R = executor_func_param;
    this->executionType = T_1R;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*, int)) {
    supposedRegisterCount = 2;
    supposedIntegerCount = 1;
    this->executor_func.T_2R_1I = executor_func_param;
    this->executionType = T_2R_1I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*, unsigned)) {
    supposedRegisterCount = 2;
    supposedIntegerCount = 1;
    this->executor_func.T_2R_1U = executor_func_param;
    this->executionType = T_2R_1U;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, int, int)) {
    supposedRegisterCount = 1;
    supposedIntegerCount = 2;
    this->executor_func.T_1R_2I = executor_func_param;
    this->executionType = T_1R_2I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, int)) {
    supposedRegisterCount = 1;
    supposedIntegerCount = 1;
    this->executor_func.T_1R_1I = executor_func_param;
    this->executionType = T_1R_1I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(int)) {
    supposedRegisterCount = 0;
    supposedIntegerCount = 1;
    this->executor_func.T_1I = executor_func_param;
    this->executionType = T_1I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(void)) {
    supposedRegisterCount = 0;
    supposedIntegerCount =  0;
    this->executor_func.T_V = executor_func_param;
    this->executionType = T_V;
    return this;
}

Instruction *Instruction::overloadSupposedRegisterCount(int count) {
    overloadedRegisterCount = count;
    return this;
}

Instruction *Instruction::overloadSupposedIntegerCount(int count) {
    overloadedIntegerCount = count;
    return this;
}


void Instruction::feed(std::vector<Register*> newRegisters, std::vector<int> newIntegers) {
    registers.insert(registers.end(), newRegisters.begin(), newRegisters.end());
    integers.insert(integers.end(), newIntegers.begin(), newIntegers.end());
}

void Instruction::execute(Executor *executor) {
    if (!validate()) throw("Invalid Instruction:\n" + errorMessage);
    else if (executionType == T_3R) (executor->*executor_func.T_3R)(registers[0], registers[1], registers[2]);
    else if (executionType == T_2R) (executor->*executor_func.T_2R)(registers[0], registers[1]);
    else if (executionType == T_1R) (executor->*executor_func.T_1R)(registers[0]);
    else if (executionType == T_2R_1I) (executor->*executor_func.T_2R_1I)(registers[0], registers[1], integers[0]);
    else if (executionType == T_2R_1U) (executor->*executor_func.T_2R_1U)(registers[0], registers[1], (unsigned) integers[0]);
    else if (executionType == T_1R_2I) (executor->*executor_func.T_1R_2I)(registers[0], integers[0], integers[1]);
    else if (executionType == T_1R_1I) (executor->*executor_func.T_1R_1I)(registers[0], integers[0]);
    else if (executionType == T_1I) (executor->*executor_func.T_1I)(integers[0]);
    else if (executionType == T_V) (executor->*executor_func.T_V)();
}

const std::string& Instruction::getErrorMessage() {
    return errorMessage;
}

int Instruction::getRegistersCount(){
    return registers.size();
}

int Instruction::getIntegersCount(){
    return integers.size();
}

bool Instruction::isRegisterCountOK(){
    return ((getRegistersCount() == supposedRegisterCount) || (getRegistersCount() == overloadedRegisterCount)); 
}

bool Instruction::isIntegerCountOK(){
    return ((getIntegersCount() == supposedIntegerCount) || (getIntegersCount() == overloadedIntegerCount)); 
}

const std::string& Instruction::toString() {
    return repr;
}