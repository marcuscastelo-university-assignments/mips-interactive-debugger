#include "Word.h"

Word::Word(): ByteArray(4) {}

Word::Word(unsigned char *byteArr): Word() {
    setValue(byteArr);   
}

Word::Word(int integer): Word() {
    setValue(integer);
}

void Word::setValue(unsigned char *byteArr) {
    this->setBytes(byteArr, 4);
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
