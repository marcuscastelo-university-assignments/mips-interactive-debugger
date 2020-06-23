#include "Register.h"

Register::Register(std::string, Word word){    
    this->word = word;
    this->name = name;
}

Register::Register(std::string){    
    this->word = 0;
    this->name = name;
}

std::string Register::getName(void) {
    return name;
}

Word Register::getValue(){
    return word;
}

void Register::setValue(Word word){
    this->word.setValue(word.asInt());
}

Register::~Register(){
}