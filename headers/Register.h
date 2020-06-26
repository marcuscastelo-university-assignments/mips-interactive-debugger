#ifndef REGISTER_H
#define REGISTER_H

#include <stdio.h>
#include <string>
#include "Word.h"

enum RegisterType {
    NORMAL = 0, READONLY = 1, TEMPORARY = 2
};

//TODO: implementar registradores que não podem ser alterados
class Register
{
    private:
        std::string name;    
        Word word;
        RegisterType type;
    public:
        Register(const std::string& name, RegisterType type = NORMAL);
        Register(const std::string& name, const Word& word, RegisterType type = NORMAL);
        Register(const Register& other, RegisterType type = NORMAL);

        const std::string& getName(void) const;
        const ByteArray& asByteArray() const;
        int asInt() const;
        bool isReadOnly() const;
        bool isTemporary() const;

        void setValue(const Word& word);
        void copy(const Register& reg);
        
        void print(FILE *file_stream = stdout) const;
};

#endif