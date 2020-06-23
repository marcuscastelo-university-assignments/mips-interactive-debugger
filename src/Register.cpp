#include "Register.h"

Register::Register(std::string, Word word){    
    this->word = word;
    this->name = name;
}

Register::Register(std::string) {    
    this->word = 0;
    this->name = name;
}

std::string Register::getName(void) {
    return this->name;
}

Word Register::getValue(){
    return this->word;
}

int Register::getValueAsInt(){
    return this->word.asInt();
}
void Register::copyValue(Register *reg){
    this->word = reg->getValue();
}

void Register::setValue(Word word){
    this->word = word;
}

Register::~Register(){
}