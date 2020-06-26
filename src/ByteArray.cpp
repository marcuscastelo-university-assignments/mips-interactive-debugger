#include "ByteArray.h"
#include <stdio.h>
#include <string.h>

ByteArray::ByteArray(int size)
: bytes(size, 0x00)
{

}

ByteArray::ByteArray(const ByteArray &byteArray)
: bytes(byteArray.getSize(), 0x00) 
{
    for (int i = 0; i < byteArray.getSize(); i++) 
        bytes[i] = byteArray.getByteAt(i);
}

ByteArray::ByteArray(unsigned char *charArr, int size)
: bytes(size, 0x00)
{
    setBytes(charArr, size);
}

void ByteArray::setBytes(int fromPos, const ByteArray& subByteArray) {
    if (fromPos + subByteArray.getSize() > getSize()) throw("invalid subByteArray size");
    for (int i = fromPos, j = 0; j < subByteArray.getSize(); i++, j++)
        bytes[i] = subByteArray.getByteAt(j);
}


void ByteArray::setBytes(const ByteArray& byteArray) {
    if (byteArray.getSize() != this->getSize()) throw("invalid byteArr size");
    setBytes(0, byteArray);
}

void ByteArray::setBytes(unsigned char *charArr, int size) {
    if (size != this->getSize()) throw("Mismatch in array size while setting bytes");
    for (int i = 0; i < size; i++) bytes[i] = charArr[i];
}

int ByteArray::getSize() const {
    return bytes.size();
}

const ByteArray ByteArray::getBytes(int from, int size) const {
    ByteArray toReturn(size);
    for(int i = from, j = 0; j < size; i++, j++)       
        toReturn.setByteAt(j, getByteAt(i));  

    return toReturn;
}

const ByteArray ByteArray::getBytes() const {      
    return getBytes(0, getSize());
}


unsigned char ByteArray::getByteAt(int pos) const {
    return bytes[pos];
}


void ByteArray::print(FILE *file_stream) {
    for (int i = 0; i < getSize(); i++)
        fprintf(file_stream, "%02X ", bytes[i]);
    fprintf(file_stream, "\n");   
}

void ByteArray::setByteAt(int pos, unsigned char byte) {
    bytes[pos] = byte;
}