#include "Register.h"

Register::Register(const std::string& name, RegisterType type) 
: name(name), word(0), type(type) {}

Register::Register(const std::string& name, const Word& word, RegisterType type)
: name(name), word(word), type(type) {}

Register::Register(const Register& other, RegisterType type) 
: name(other.name), word(other.word), type(type)  {}

const std::string& Register::getName(void) const {
    return name;
}

const ByteArray& Register::asByteArray() const {
    return word;
}

int Register::asInt() const {
    return word.asInt();
}

bool Register::isReadOnly() const {
    return type & READONLY;
}

bool Register::isTemporary() const {
    return type & TEMPORARY;
}


void Register::setValue(const Word& word){
    if (type & READONLY)  {
        fprintf(stderr, "WARNING: ignoring trial to modify read-only register");
        return;
    }

    this->word.setValue(word.asInt());
}

void Register::copy(const Register& reg){
    if (type & READONLY) {
        fprintf(stderr, "WARNING: ignoring trial to copy to read-only register");
        return;
    }
    this->word.setValue(reg.asInt());
}

void Register::print(FILE *file_stream) const {
    fprintf(file_stream, "|%s|%d / ", name.c_str(), word.asInt());
    for(int i=0;i<4;i++) fprintf(file_stream, "%02X ", word.asByteArray().getByteAt(i));
    fprintf(file_stream,"|\n");
}