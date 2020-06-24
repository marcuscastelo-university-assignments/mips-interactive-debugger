#include "ByteArray.h"

ByteArray::ByteArray(int size) {
    this->size = size;
    bytes = (char *) malloc(size * sizeof(int));
}

ByteArray::ByteArray(unsigned char *charArr, int size): ByteArray(size) {
    this->setBytes(charArr, size);
}

void ByteArray::setBytes(unsigned char *charArr, int size) {
    if (size != this->size) throw("invalid charArr size");
    for (int i = 0; i < size; i++)
        bytes[i] = charArr[i];     
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