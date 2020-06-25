#include "Register.h"

Register::Register(const std::string& name) 
: name(name), word(0) {}

Register::Register(const std::string& name, const Word& word)
: name(name), word(word) {}

Register::Register(const Register& other) 
: name(other.name), word(other.word) {}

const std::string& Register::getName(void) const {
    return this->name;
}

Word& Register::getWord() const{
    return (Word&) this->word;
}

int Register::asInt() const{
    return this->word.asInt();
}

void Register::copy(const Register& reg){
    this->word = reg.getWord();
}

void Register::setWord(const Word& word){
    this->word = word;
}

void Register::print(FILE *file_stream) const {
    //TODO: colocar como bytearray e deixar bonito
    fprintf(file_stream, "|%s|%d / ", name.c_str(), word.asInt());
    for(int i=0;i<4;i++) fprintf(file_stream, "%02X ", word.asByteArray().getByteAt(i));
    fprintf(file_stream,"|\n");
}

Register::~Register() {

}