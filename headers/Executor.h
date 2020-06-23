#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <map>
#include <string>

#include "Stack.h"
#include "Word.h"

class Executor{
    private:
        std::map<std::string,int> registerNameToId;
        std::vector<Word> registerValues;
        Stack stack;
    public:
        Executor();
        ~Executor();

        int nameToId(char *name);

        Word *_lw(int stackAddress);
        void _sw(int stackAdress, Word *word);
        char _lb(int stackAdress);
        void _sb(int stackAddress, char byte);
        void _beqz(int regId, int jumpAddress);
        void _bnez(int regId, int jumpAddress);
        void _bgez(int regId, int jumpAddress);
        void _bgtz(int regId, int jumpAddress);
        void _blez(int regId, int jumpAddress);
        void _bltz(int regId, int jumpAddress);
        void _bgezal(int regId, int jumpAddress);
        void _bltzal(int regId, int jumpAddress);
        void _bne(int reg1Id, int reg2Id, int jumpAddress);
        void _beq(int reg1Id, int reg2Id, int jumpAddress);
        void _blt(int reg1Id, int reg2Id, int jumpAddress);
        void _ble(int reg1Id, int reg2Id, int jumpAddress);
        void _bgt(int reg1Id, int reg2Id, int jumpAddress);
        void _bge(int reg1Id, int reg2Id, int jumpAddress);
        void _b(int jumpAddress);

        void _jump(int jumpAddress);
        void _add(int reg1Id, int reg2Id, int reg3Id);
        void _addi(int reg1Id, int reg2Id, int value);
        void _sub(int reg1Id, int reg2Id, int reg3Id);
        void _mult(int reg1Id,int reg2Id);
        void _mul(int reg1Id,int reg2Id,int reg3Id);
        
        void _mflo(int regId);
        void _mfhi(int regId);
        
        void _div(int reg1Id,int reg2Id);
        void _div(int reg1Id,int reg2Id,int reg3Id);
        void _rem(int reg1Id,int reg2Id,int reg3Id);


        void _and(int reg1Id, int reg2Id, int reg3Id);
        void _or(int reg1Id, int reg2Id, int reg3Id);
        void _xor(int reg1Id, int reg2Id, int reg3Id);
        void _andi(int reg1Id, int reg2Id, int value);
        void _ori(int reg1Id, int reg2Id, int value);
        void _xori(int reg1Id, int reg2Id, int value);
        void _slt(int reg1Id, int reg2Id, int reg3Id);
        void syscall();
};

#endif