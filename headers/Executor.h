#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <map>
#include <string>

#include "Stack.h"

class Executor{
    private:
        std::map<std::string,int> registerNameToId;
        Stack stack;

    public:
        Executor();
        ~Executor();

        char *lw(int stackAddress);
        void sw(int stackAdress, char* word);
        char lb(int stackAdress);
        void sb(char byte);
        void syscall();

};

#endif