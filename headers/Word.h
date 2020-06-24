#ifndef __WORD__H__
#define __WORD__H__

#include <math.h>
#include <stdlib.h>

class Word
{
    private:
        char bytes[4] = {0, 0, 0, 0};
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

#endif 