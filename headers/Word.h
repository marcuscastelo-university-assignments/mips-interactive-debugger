#ifndef __WORD__H__
#define __WORD__H__

#include <math.h>
#include <stdlib.h>

#include "ByteArray.h"

class Word : public ByteArray
{
    public:
        Word();
        Word(unsigned char *byteArr);
        Word(int integer);
        void setValue(int integer);
        void setValue(unsigned char *byteArr);
        int asInt();
        ByteArray asByteArray();
        Word clone();
};

#endif 