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

        int getStackSize();

        char *loadBytes(int address, int size);
        void writeBytes(int address, char *bytes, int size);
        char loadByte(int address);
        void writeByte(int address, char byte);
};

#endif
