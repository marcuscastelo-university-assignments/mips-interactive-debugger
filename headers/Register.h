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
        Register(std::string name, Word word = 0);
        ~Register();
        std::string getName(void);
        void copyValue(Register *reg);
        void setValue(Word word);
        Word getValue();
        int getValueAsInt();
        void print(FILE *file_stream = stdout);
};

#endif