#include "Instruction.h"

#include <sstream>

bool Instruction::validate() {
    if (!errorMessage.empty()) return false;

    if (executionType == T_UNKNOWN){
        errorMessage += "T_Unknown instruction: " + toString() + ".\n";        
        return false;
    }

    if(!areParametersCountOK()){
        errorMessage += "Wrong number of Register(s) and/or Integer(s).\n";
        std::stringstream correctSupossedNumbers;
        correctSupossedNumbers << supposedRegisterCount << " Register(s) and " << supposedIntegerCount << " Integer(s) have been passed, but:\n\t" << supposedRegisterCount << " Register(s) and " << supposedIntegerCount << " Integers";
        if(hasOverload()) correctSupossedNumbers <<", or\n\t" << overloadedRegisterCount << " Register(s) and " << overloadedIntegerCount << " Integers.\n";
        else correctSupossedNumbers <<".\n";
        errorMessage += correctSupossedNumbers.str() + "Should have been passed.\n";

        return false;
    }
    
    //Checks if user is trying to modify read-only register
    if(registers[0]->isReadOnly()){
        errorMessage += "Invalid attribution of value to register " + registers[0]->getName() + ", which is read only.\n";
        return false; 
    }
    
    if(hasOverload()) adjustParameters();


    return true;
}

void Instruction::adjustParameters(){
    for(int i=getRegistersCount();i<typeRegisterCount;i++) feedRegisters(i,NULL);
    for(int i=getIntegersCount();i<typeIntegerCount;i++) feedIntegers(i,0xF0DA);
}


void Instruction::feedRegisters(int pos, Register* value){
    registers[pos] = value;
}

void Instruction::feedIntegers(int pos,int value){
    integers[pos] = value;
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

    for(int i = 0; i<3;i++) registers.push_back(NULL);
    for(int i=0;i<0;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<2;i++) registers.push_back(NULL);
    for(int i=0;i<0;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<1;i++) registers.push_back(NULL);
    for(int i=0;i<0;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<2;i++) registers.push_back(NULL);
    for(int i=0;i<1;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<2;i++) registers.push_back(NULL);
    for(int i=0;i<2;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<2;i++) registers.push_back(NULL);
    for(int i=0;i<1;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<1;i++) registers.push_back(NULL);
    for(int i=0;i<2;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<1;i++) registers.push_back(NULL);
    for(int i=0;i<1;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<0;i++) registers.push_back(NULL);
    for(int i=0;i<1;i++) integers.push_back(0xF0DA);

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

    for(int i = 0; i<0;i++) registers.push_back(NULL);
    for(int i=0;i<0;i++) integers.push_back(0xF0DA);

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


void Instruction::feed(std::vector<Register*> newRegisters, std::vector<int> newIntegers) {
    if (!newRegisters.empty()) registers.insert(registers.end(), newRegisters.begin(), newRegisters.end());
    if (!newIntegers.empty()) integers.insert(integers.end(), newIntegers.begin(), newIntegers.end());
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