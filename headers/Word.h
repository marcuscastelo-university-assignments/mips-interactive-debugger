#ifndef __WORD__H__
#define __WORD__H__

#include <math.h>
#include <stdlib.h>

#include "ByteArray.h"

class Word : public ByteArray
{
    public:
        Word();
        Word(ByteArray byteArray);
        Word(unsigned char *bytes);
        Word(int integer);
        void setValue(int integer);
        void setValue(ByteArray byteArray);
        int asInt();
        ByteArray asByteArray();
        Word clone();
};

#endif 