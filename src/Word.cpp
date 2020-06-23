#include "Word.h"

Word Word::operator+(Word &other) {
    return Word(this->asInt() + other.asInt());
}

Word Word::operator-(Word &other) {
    return Word(this->asInt() - other.asInt());
}

Word Word::operator*(Word &other) {
    return Word(this->asInt() * other.asInt());
}

Word Word::operator/(Word &other) {
    return Word(this->asInt() / other.asInt());
}

Word Word::operator%(Word &other) {
    return Word(this->asInt() % other.asInt());
}

Word Word::operator&(Word &other) {
    return Word(this->asInt() & other.asInt());
}

Word Word::operator|(Word &other) {
    return Word(this->asInt() | other.asInt());
}

Word Word::operator^(Word &other) {
    return Word(this->asInt() ^ other.asInt());
}

Word Word::operator<(Word &other) {
    return Word(this->asInt() < other.asInt());
}

Word Word::operator<=(Word &other) {
    return Word(this->asInt() <= other.asInt());
}
Word Word::operator>(Word &other) {
    return Word(this->asInt() > other.asInt());

}
Word Word::operator>=(Word &other) {
    return Word(this->asInt() >= other.asInt());

}
Word Word::operator==(Word &other) {
    return Word(this->asInt() == other.asInt());
}


Word Word::operator+(int &other) {
    return Word(this->asInt() + other);
}

Word Word::operator-(int &other) {
    return Word(this->asInt() - other);
}

Word Word::operator*(int &other) {
    return Word(this->asInt() * other);
}

Word Word::operator/(int &other) {
    return Word(this->asInt() / other);
}

Word Word::operator%(int &other) {
    return Word(this->asInt() % other);
}

Word Word::operator&(int &other) {
    return Word(this->asInt() & other);
}

Word Word::operator|(int &other) {
    return Word(this->asInt() | other);
}

Word Word::operator^(int &other) {
    return Word(this->asInt() ^ other);
}


Word::Word() {
    setValue(0);
}

Word::Word(char *byteArr) {
    setValue(byteArr);   
}

Word::Word(int integer) {
    setValue(integer);
}

void Word::setValue(char *byteArr) {
    for (int i = 0; i < 4; i++) this->bytes[i] = byteArr[i];
}

void Word::setValue(int integer) {
    for (int i = 0; i < 4; i++) bytes[i] = integer & (int)(pow(2,8*(i+1))-1);
}

char *Word::asByteArray() {
    return bytes;    
}

int Word::asInt() {
    int integer = 0;
    for (int i = 0; i < 4; i++) integer |= bytes[i] << i*8;
    return integer;
}

Word::~Word()
{
}
