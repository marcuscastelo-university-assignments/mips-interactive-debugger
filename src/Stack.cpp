#include "Stack.h"
#include "ByteArray.h"

#include <stdlib.h>

Stack::Stack(): Stack(4096 * sizeof(unsigned char)) {}
Stack::Stack(): ByteArray(4096);
Stack::Stack(int stackSize) {
    this->stackBytes = std::vector<unsigned char>(stackSize);
}

Stack::~Stack() {
    
}

int Stack::getStackSize() {
    return stackBytes.size();
}

unsigned char Stack::loadByte(int address){
    return stackBytes[address];
}

ByteArray Stack::loadBytes(int address, int size){
    ByteArray bArr(size);
    for(int i=0;i<size;i++){
        bArr.setByteAt(i, loadByte(address + i));
    }
    return bArr;
}

void Stack::writeByte(int address, unsigned char byte){
    stackBytes[address] = byte;
}

void Stack::writeBytes(int address, unsigned char *bytes, int size) {
    for (int i = 0; i < size; i++)
        writeByte(address + i, bytes[i]);
}