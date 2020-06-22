#include "Stack.h"

#include <stdlib.h>

Stack::Stack(): Stack(4096) {}
Stack::Stack(int stackSize) {
    this->stackBytes = std::vector<char>(stackSize);
}


char Stack::loadByte(int address){
    return stackBytes[address];
}

char *Stack::loadBytes(int address, int size){
    char *toReturn = (char *)malloc(size*sizeof(char));
    for(int i=0;i<size;i++){
        toReturn[i] = loadByte(address + i);
    }
    return toReturn;
}

char Stack::writeByte(int address, char byte){
    stackBytes[address] = byte;
}

void Stack::writeBytes(int address, char *bytes, int size) {
    for (int i = 0; i < size; i++)
        writeByte(address + i, bytes[i]);
}