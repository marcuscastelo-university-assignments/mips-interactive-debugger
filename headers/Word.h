#include <math.h>
#include <stdlib.h>

class Word
{
    private:
        char bytes[4];
    public:
        Word();
        Word(char *byteArr);
        Word(int integer);
        void setValue(int integer);
        void setValue(char *byteArr);
        int asInt();
        char *asByteArray();
        ~Word();
};

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
    char *byteArr = (char*) malloc(4*sizeof(char));
    for (int i = 0; i < 4; i++) byteArr[i] = this->bytes[i];
    return byteArr;    
}

int Word::asInt() {
    int integer = 0;
    for (int i = 0; i < 4; i++) integer |= bytes[i] << i*8;
    return integer;
}

Word::~Word()
{
}
