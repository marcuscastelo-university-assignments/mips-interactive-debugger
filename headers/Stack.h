#ifndef STACK_H
#define STACK_H

#include <vector>

class Stack
{
    private:
        std::vector<char> stackBytes;
    public:
        Stack();
        Stack(int stackSize);

        ~Stack();
        char *loadBytes(int address, int size);
        void writeBytes(int address, char *bytes, int size);
        char loadByte(int address);
        char writeByte(int address, char byte);
};

#endif
