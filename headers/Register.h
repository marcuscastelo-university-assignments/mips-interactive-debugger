#ifndef REGISTER_H
#define REGISTER_H

#include <string>
#include "Word.h"

class Register
{
    private:
        std::string name;    
        Word word;
    public:
        Register(std::string name);
        Register(std::string name, Word word);
        ~Register();
        std::string getName(void);
        void copyValue(Register *reg);
        void setValue(Word word);
        Word getValue();
        int getValueAsInt();
};

#endif