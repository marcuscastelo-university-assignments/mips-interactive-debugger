#include "ByteArray.h"
#include<stdio.h>
ByteArray::ByteArray(int size) {
    this->size = size;
    bytes = (unsigned char *) calloc(size, sizeof(unsigned char));
}

ByteArray::ByteArray(const ByteArray &byteArray) {
    this->size = size;
    bytes = (unsigned char *) calloc(size, sizeof(unsigned char));
    for (int i = 0; i < size; i++) bytes[i] = byteArray.getByteAt(i);
    printf("\n");
}

ByteArray::ByteArray(unsigned char *charArr, int size): ByteArray(size) {
    setBytes(charArr, size);
}

void ByteArray::setBytes(int fromPos, ByteArray subByteArray) {
    if (fromPos + subByteArray.getSize() > size) throw("invalid subByteArray size");
    for (int i = fromPos, j = 0; i < subByteArray.getSize(); i++, j++)
        bytes[i] = subByteArray.getByteAt(j);
}

//TODO: delete
static void printByteArray(const ByteArray *foda) {
    for (int i = 0; i < foda->getSize(); i++)
    {
        printf("%02X ", foda->getByteAt(i));
    }
    printf("\n");
    
}

void ByteArray::setBytes(const ByteArray& byteArray) {
    printf("ByteArray@setBytes:\n");
    printByteArray(&byteArray);

    if (byteArray.size != this->size) throw("invalid byteArr size");
    setBytes(0,byteArray);
}

void ByteArray::setBytes(unsigned char *charArr, int size) {
    if (size != this->size) throw("Mismatch in array size while setting bytes");
    for (int i = 0; i < size; i++) bytes[i] = charArr[i];
}

int ByteArray::getSize() const {
    return size;
}

const ByteArray ByteArray::getBytes(int from, int size) const {
    ByteArray toReturn(size);
    for(int i = from, j = 0; j < size; i++, j++)       
        toReturn.setByteAt(j, getByteAt(i));  

    printf("%d != %d\n", bytes[3], getByteAt(3));
    printf("%d != %d\n", bytes[3], toReturn.getByteAt(3));
    return toReturn;
}

const ByteArray ByteArray::getBytes() const {      
    return getBytes(0, size);
}


unsigned char ByteArray::getByteAt(int pos) const {
    return bytes[pos];
}

void ByteArray::setByteAt(int pos, unsigned char byte) {
    bytes[pos] = byte;
}

ByteArray::~ByteArray() {
    free(bytes);
}