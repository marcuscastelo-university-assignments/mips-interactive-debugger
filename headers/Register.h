#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <string>
#include "Word.h"

//TODO: implementar registradores que não podem ser alterados
class Register
{
    private:
        std::string name;    
        Word word;
    public:
        Register(const std::string& name);
        Register(const std::string& name, const Word& word);
        Register(const Register& other);
        ~Register();
        const std::string& getName(void) const;
        void copy(const Register& reg);
        void setWord(const Word& word);
        Word& getWord() const;
        int asInt() const;
        void print(FILE *file_stream = stdout) const;
};

#endif