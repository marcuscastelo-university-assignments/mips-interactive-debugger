#include "ByteArray.h"

ByteArray::ByteArray(int size) {
    this->size = size;
    bytes = (char *) calloc(size, sizeof(int));
}

ByteArray::ByteArray(unsigned char *charArr, int size): ByteArray(size) {
    for (int i = 0; i < size; i++) bytes[i] = charArr[i];
}

void ByteArray::setBytes(int fromPos, ByteArray subByteArray) {
    if (fromPos + subByteArray.getSize() > size) throw("invalid subByteArray size");
    for (int i = fromPos, j = 0; i < subByteArray.getSize(); i++, j++)
        bytes[i] = subByteArray.getByteAt(j);
}

void ByteArray::setBytes(ByteArray byteArray) {
    if (byteArray.size != this->size) throw("invalid byteArr size");
    setBytes(0,byteArray);
}

int ByteArray::getSize() {
    return size;
}

ByteArray ByteArray::getBytes(int from, int size) {
    ByteArray toReturn(size);
    for(int i = 0; i < size; i++)       
        toReturn.setByteAt(i, getByteAt(from));        
    return toReturn;
}

ByteArray ByteArray::getBytes() {      
    return getBytes(0, size-1);
}


unsigned char ByteArray::getByteAt(int pos) {
    return bytes[pos];
}

void ByteArray::setByteAt(int pos, unsigned char byte) {
    bytes[pos] = byte;
}

ByteArray::~ByteArray() {
    free(bytes);
}