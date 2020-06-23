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
        int pcMaxCounter;
    public:
        Executor();
        ~Executor();

        char *lw(int stackAddress);
        void sw(int stackAdress, char* word);
        char lb(int stackAdress);
        void sb(int stackAddress, char byte);
        void beqz(int regId, int jumpAddress);
        void bnez(int regId, int jumpAddress);
        void bgez(int regId, int jumpAddress);
        void bgtz(int regId, int jumpAddress);
        void blez(int regId, int jumpAddress);
        void bltz(int regId, int jumpAddress);
        void bgezal(int regId, int jumpAddress);
        void bltzal(int regId, int jumpAddress);
        void bne(int reg1Id, int reg2Id, int jumpAddress);
        void beq(int reg1Id, int reg2Id, int jumpAddress);
        void blt(int reg1Id, int reg2Id, int jumpAddress);
        void ble(int reg1Id, int reg2Id, int jumpAddress);
        void bgt(int reg1Id, int reg2Id, int jumpAddress);
        void bge(int reg1Id, int reg2Id, int jumpAddress);
        void jump(int jumpAddress);
        void syscall();

};

#endif