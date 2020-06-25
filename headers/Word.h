#ifndef __WORD__H__
#define __WORD__H__

#include <math.h>
#include <stdlib.h>

#include "ByteArray.h"

class Word : public ByteArray
{
    public:
        Word();
        Word(const ByteArray& byteArray);
        Word(unsigned char *bytes);
        Word(int integer);

        void setValue(int integer);
        void setValue(const ByteArray& byteArray);
        int asInt() const;
        const ByteArray& asByteArray() const;
        const Word clone() const;
};

#endif 