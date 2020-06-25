#include "Word.h"

#define WORD_SIZE 4
#include <stdio.h>

Word::Word(): ByteArray(WORD_SIZE) {}

Word::Word(unsigned char *byteArr): ByteArray(byteArr, WORD_SIZE) { }


//TODO: delete
static void _printByteArray(ByteArray *foda) {
    for (int i = 0; i < foda->getSize(); i++)
    {
        printf("%02X ", foda->getByteAt(i));
    }
    printf("\n");
    
}


Word::Word(const Word& word): ByteArray(word.getBytes()) { }

Word::Word(ByteArray bytearray): Word() {
    if (bytearray.getSize() != WORD_SIZE) throw("bytearray is not word-sized");
    this->setBytes(bytearray);
}

Word::Word(int integer): Word() {
    setValue(integer);
}

//TODO: delete
static void printByteArray(ByteArray *foda) {
    for (int i = 0; i < foda->getSize(); i++)
    {
        printf("%02X ", foda->getByteAt(i));
    }
    printf("\n");
    
}
void Word::setValue(ByteArray byteArray) {
    printf("Word@setValue: \n");
    printByteArray(&byteArray);
    this->setBytes(byteArray);
}

void Word::setValue(int integer) {
    for (int i = 0; i < 4; i++) setByteAt(i, (char) ((integer >> (3-i)*8) & 0x000000FF));
}

ByteArray Word::asByteArray() {
    return ByteArray(this->getBytes());
}

Word Word::clone() {
    return *this;
}

int Word::asInt() const {
    unsigned integer = 0;
    for (int i = 0; i < 4; i++) {
        integer |= getByteAt(i) << 8*(3-i);
    }
    
    return (int) integer;
}
