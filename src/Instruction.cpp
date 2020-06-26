#include "Instruction.h"

#include <sstream>
#include <stdexcept>

bool Instruction::validate() {
    if (!errorMessage.empty()) return false;

    errorMessage = "";
    if (executionType == T_UNKNOWN){
        errorMessage += "Unknown instruction: " + toString() + ".";        
        return false;
    }

    if(!areParametersCountOK()){
        errorMessage += "Wrong number of Register(s) and/or Integer(s).";
        std::stringstream correctSupossedNumbers;
        correctSupossedNumbers << getRegistersCount() << " Register(s) and " << getIntegersCount() << " Integer(s) have been passed, but:\n\t" << supposedRegisterCount << " Register(s) and " << supposedIntegerCount << " Integers";
        if(hasOverload()) correctSupossedNumbers <<", or\n\t" << overloadedRegisterCount << " Register(s) and " << overloadedIntegerCount << " Integers.";
        else correctSupossedNumbers << ".";
        errorMessage += correctSupossedNumbers.str() + "\nShould have been passed.";

        return false;
    }
    
    //Checks if user is trying to modify read-only register
    if(registers.size() > 0 && registers[0]->isReadOnly()){
        errorMessage += "Invalid attribution of value to register " + registers[0]->getName() + ", which is read only.";
        return false; 
    }
    
    if(hasOverload()) adjustParameters();


    return true;
}

void Instruction::adjustParameters(){
    for(int i=getRegistersCount();i<typeRegisterCount;i++) registers.push_back(NULL);
    for(int i=getIntegersCount();i<typeIntegerCount;i++) integers.push_back(0xF0DA);
}

void Instruction::feed(const std::vector<Register*>& newRegisters, const std::vector<int>& newIntegers) {
    registers.clear();
    integers.clear();
    registers.insert(registers.end(), newRegisters.begin(), newRegisters.end());
    integers.insert(integers.end(), newIntegers.begin(), newIntegers.end());



}

ExecutionType Instruction::getExecutionType() {
    return executionType;
}

AdvancePcType Instruction::getAdvancePcType() {
    return advancePc;
}

Instruction::Instruction(const std::string& repr, AdvancePcType advancePc) :
repr(repr),
executionType(T_UNKNOWN),
advancePc(advancePc),
overloaded(false),
errorMessage(""),
supposedRegisterCount(0), 
supposedIntegerCount(0), 
overloadedRegisterCount(0),
overloadedIntegerCount(0), 
typeRegisterCount(0),
typeIntegerCount(0) {}

Instruction::Instruction(const Instruction& other) : 
repr(other.repr), 
executionType(other.executionType), 
advancePc(other.advancePc), 
overloaded(other.overloaded), 
errorMessage(""),
supposedRegisterCount(other.supposedRegisterCount), 
supposedIntegerCount(other.supposedIntegerCount), 
overloadedRegisterCount(other.overloadedRegisterCount),
overloadedIntegerCount(other.overloadedIntegerCount), 
typeRegisterCount(other.typeRegisterCount),
typeIntegerCount(other.typeIntegerCount) {}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*, Register*)) {

    typeRegisterCount = 3;
    typeIntegerCount = 0;
    
    overloadedRegisterCount = 3;
    overloadedIntegerCount = 0;
    
    supposedRegisterCount = 3;
    supposedIntegerCount = 0;
    
    this->executor_func.T_3R = executor_func_param;
    this->executionType = T_3R;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*)) {

    typeRegisterCount = 2;
    typeIntegerCount = 0;
    
    overloadedRegisterCount = 2;
    overloadedIntegerCount = 0;
    
    supposedRegisterCount = 2;
    supposedIntegerCount = 0;
    
    this->executor_func.T_2R = executor_func_param;
    this->executionType = T_2R;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*)) {

    typeRegisterCount = 1;
    typeIntegerCount = 0;
    
    overloadedRegisterCount = 1;
    overloadedIntegerCount = 0;
    
    supposedRegisterCount = 1;
    supposedIntegerCount = 0;
    
    this->executor_func.T_1R = executor_func_param;
    this->executionType = T_1R;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*, int)) {

    typeRegisterCount = 2;
    typeIntegerCount = 1;
    
    overloadedRegisterCount = 2;
    overloadedIntegerCount = 1;
    
    supposedRegisterCount = 2;
    supposedIntegerCount = 1;
    
    this->executor_func.T_2R_1I = executor_func_param;
    this->executionType = T_2R_1I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*,Register*,int, int)) {

    typeRegisterCount = 2;
    typeIntegerCount = 2;
    
    overloadedRegisterCount = 2;
    overloadedIntegerCount = 2;
    
    supposedRegisterCount = 2;
    supposedIntegerCount = 2;
    
    this->executor_func.T_2R_2I = executor_func_param;
    this->executionType = T_2R_2I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, Register*, unsigned)) {

    typeRegisterCount = 2;
    typeIntegerCount = 1;
    
    overloadedRegisterCount = 2;
    overloadedIntegerCount = 1;
    
    supposedRegisterCount = 2;
    supposedIntegerCount = 1;
    
    this->executor_func.T_2R_1U = executor_func_param;
    this->executionType = T_2R_1U;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, int, int)) {

    typeRegisterCount = 1;
    typeIntegerCount = 2;
    
    overloadedRegisterCount = 1;
    overloadedIntegerCount = 2;
    
    supposedRegisterCount = 1;
    supposedIntegerCount = 2;
    
    this->executor_func.T_1R_2I = executor_func_param;
    this->executionType = T_1R_2I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(Register*, int)) {

    typeRegisterCount = 1;
    typeIntegerCount = 1;
    
    overloadedRegisterCount = 1;
    overloadedIntegerCount = 1;
    
    supposedRegisterCount = 1;
    supposedIntegerCount = 1;
    
    this->executor_func.T_1R_1I = executor_func_param;
    this->executionType = T_1R_1I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(int)) {

    typeRegisterCount = 0;
    typeIntegerCount = 1;
    
    overloadedRegisterCount = 0;
    overloadedIntegerCount = 1;
    
    supposedRegisterCount = 0;
    supposedIntegerCount = 1;
    
    this->executor_func.T_1I = executor_func_param;
    this->executionType = T_1I;
    return this;
}

Instruction *Instruction::setExecutionFunction(void(Executor::*executor_func_param)(void)) {

    typeRegisterCount = 0;
    typeIntegerCount =  0;
    
    overloadedRegisterCount = 0;
    overloadedIntegerCount =  0;
    
    supposedRegisterCount = 0;
    supposedIntegerCount =  0;
    
    this->executor_func.T_V = executor_func_param;
    this->executionType = T_V;
    return this;
}

Instruction *Instruction::setExecutionFunction(void (Executor::*executor_func_param)(nullptr_t)) {

    typeRegisterCount = 0;
    typeIntegerCount =  0;
    
    overloadedRegisterCount = 0;
    overloadedIntegerCount =  0;
    
    supposedRegisterCount = 0;
    supposedIntegerCount =  0;
    
    this->executor_func.T_UNKNOWN = executor_func_param;
    this->executionType = T_UNKNOWN;
    return this;
}


Instruction *Instruction::setOverloadedRegisterCount(int count) {
    overloadedRegisterCount = count;
    overloaded = true;
    return this;
}

Instruction *Instruction::setOverloadedIntegerCount(int count) {
    overloadedIntegerCount = count;
    overloaded = true;
    return this;
}

Instruction *Instruction::setSupposedRegisterCount(int count) {
    supposedRegisterCount = count;
    return this;
}

Instruction *Instruction::setSupposedIntegerCount(int count) {
    supposedIntegerCount = count;
    return this;
}


void Instruction::execute(Executor *executor) {
    if (!validate()) {
        printf("validate errado\n");
        fflush(stdout);
        throw std::domain_error("Invalid Instruction:" + errorMessage);
    }
    else if (executionType == T_3R) (executor->*executor_func.T_3R)(registers[0], registers[1], registers[2]);
    else if (executionType == T_2R) (executor->*executor_func.T_2R)(registers[0], registers[1]);
    else if (executionType == T_1R) (executor->*executor_func.T_1R)(registers[0]);
    else if (executionType == T_2R_1I) (executor->*executor_func.T_2R_1I)(registers[0], registers[1], integers[0]);
    else if (executionType == T_2R_1U) (executor->*executor_func.T_2R_1U)(registers[0], registers[1], (unsigned) integers[0]);
    else if (executionType == T_2R_2I) (executor->*executor_func.T_2R_2I)(registers[0], registers[1], integers[0], integers[1]);
    else if (executionType == T_1R_2I) (executor->*executor_func.T_1R_2I)(registers[0], integers[0], integers[1]);
    else if (executionType == T_1R_1I) (executor->*executor_func.T_1R_1I)(registers[0], integers[0]);
    else if (executionType == T_1I) (executor->*executor_func.T_1I)(integers[0]);
    else if (executionType == T_V) (executor->*executor_func.T_V)();
}

const std::string& Instruction::getErrorMessage() {
    return errorMessage;
}

bool Instruction::hasOverload(){
    return overloaded;
}


int Instruction::getRegistersCount(){
    return registers.size();
}

int Instruction::getIntegersCount(){
    return integers.size();
}

bool Instruction::areParametersCountOK(){
    return ((getRegistersCount() == supposedRegisterCount && getIntegersCount() == supposedIntegerCount) || (getRegistersCount() == overloadedRegisterCount && getIntegersCount() == overloadedIntegerCount));
}


const std::string& Instruction::toString() {
    return repr;
}