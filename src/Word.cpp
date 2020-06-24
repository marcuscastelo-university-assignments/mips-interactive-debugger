#include "Word.h"

#define WORD_SIZE 4

Word::Word(): ByteArray(WORD_SIZE) {}

Word::Word(unsigned char *byteArr): ByteArray(byteArr, WORD_SIZE) { }

Word::Word(ByteArray bytearray): Word() {
    if (bytearray.getSize() != WORD_SIZE) throw("bytearray is not word-sized");
    this->setBytes(bytearray);
}

Word::Word(int integer): Word() {
    setValue(integer);
}

void Word::setValue(ByteArray byteArray) {
    this->setBytes(byteArray);
}

void Word::setValue(int integer) {
    for (int i = 0; i < 4; i++) setByteAt(i, (char) ((integer >> (3-i)*8) & 0x000000FF));
}

ByteArray Word::asByteArray() {
    return (ByteArray) *this;
}

Word Word::clone() {
    return *this;
}

int Word::asInt() {
    unsigned integer = 0;
    for (int i = 0; i < 4; i++) {
        integer |= getByteAt(i) << 8*(3-i);
    }
    
    return (int) integer;
}
