#ifndef REGISTERS_H
#define REGISTERS_H

#include <map>
#include <string>

#include "Register.h"

#define s(x) (std::string(x))

class Registers
{
    private:
        std::map<std::string, Register> registerNamesMap;

    public:
        Registers();
        ~Registers();
};
#endif