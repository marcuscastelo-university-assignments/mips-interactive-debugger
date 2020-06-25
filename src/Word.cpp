#include "Word.h"

#define WORD_SIZE 4
#include <stdio.h>

Word::Word(): ByteArray(WORD_SIZE) {}

Word::Word(unsigned char *byteArr): ByteArray(byteArr, WORD_SIZE) { }

Word::Word(const ByteArray& bytearray): ByteArray(bytearray.getBytes()){
    if (bytearray.getSize() != WORD_SIZE) throw("bytearray is not word-sized");
}

Word::Word(int integer): Word() {
    setValue(integer);
}

void Word::setValue(const ByteArray& byteArray) {
    this->setBytes(byteArray);
}

void Word::setValue(int integer) {
    for (int i = 0; i < 4; i++) setByteAt(i, (char) ((integer >> (3-i)*8) & 0x000000FF));
}

const ByteArray& Word::asByteArray() const {
    const Word &w = *this;
    return w;
}

const Word Word::clone() const {
    return *this;
}

int Word::asInt() const {
    unsigned integer = 0;
    for (int i = 0; i < 4; i++) {
        integer |= getByteAt(i) << 8*(3-i);
    }
    
    return (int) integer;
}
