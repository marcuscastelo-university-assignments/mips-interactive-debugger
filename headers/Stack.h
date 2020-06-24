#ifndef STACK_H
#define STACK_H

#include <vector>

class Stack
{
    private:
        std::vector<unsigned char> stackBytes;
    public:
        Stack();
        Stack(int stackSize);
        ~Stack();

        int getStackSize();

        ByteArray loadBytes(int address, int size);
        void writeBytes(int address, ByteArray byteArray);
        unsigned char loadByte(int address);
        void writeByte(int address, unsigned char byte);
};

#endif
