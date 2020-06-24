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

void Register::print(FILE *file_stream = stdout) {
    //TODO: colocar como bytearray e deixar bonito
    fprintf(file_stream, "|%s|%d / ", name, word.asInt());
    for(int i=0;i<4;i++) fprintf(file_stream,"%x ",word.asByteArray()[i]);
    fprintf(file_stream,"|\n");
}

Register::~Register() {

}