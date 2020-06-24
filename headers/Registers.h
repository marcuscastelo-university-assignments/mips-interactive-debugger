#ifndef REGISTERS_H
#define REGISTERS_H

#include <map>
#include <string>

#include "Register.h"

#define s(x) (std::string(x))



class Registers
{
    private:
        std::map<std::string, Register*> registerNamesMap;

    public:
        Register *getRegisterByName(std::string registerName);

        Registers();
        ~Registers();

        void printRegisters(FILE *file_stream = stdout);
        void printRegister(std::string name, FILE *file_stream = stdout);
        void printRegister(Register *reg, FILE *file_stream = stdout);

        int getValue(std::string name);
        void setValue(std::string name, int value);
        bool isRegister(std::string name);

        

        Register *ZERO;
        Register *AT;
        Register *V0;
        Register *V1;
        Register *A0;
        Register *A1;
        Register *A2;
        Register *A3;
        Register *T0;
        Register *T1;
        Register *T2;
        Register *T3;
        Register *T4;
        Register *T5;
        Register *T6;
        Register *T7;
        Register *S0;
        Register *S1;
        Register *S2;
        Register *S3;
        Register *S4;
        Register *S5;
        Register *S6;
        Register *S7;
        Register *T8;
        Register *T9;
        Register *K0;
        Register *K1;
        Register *GP;
        Register *SP;
        Register *FP;
        Register *F0;
        Register *F1;
        Register *F2;
        Register *F3;
        Register *F4;
        Register *F5;
        Register *F6;
        Register *F7;
        Register *F8;
        Register *F9;
        Register *F10;
        Register *F11;
        Register *F12;
        Register *F13;
        Register *F14;
        Register *F15;
        Register *F16;
        Register *F17;
        Register *F18;
        Register *F19;
        Register *F20;
        Register *F21;
        Register *F22;
        Register *F23;
        Register *F24;
        Register *F25;
        Register *F26;
        Register *F27;
        Register *F28;
        Register *F29;
        Register *F30;
        Register *F31;
        Register *HI;
        Register *LO;
        Register *RA;
        Register *PC;

};
#endif