#ifndef __BYTEARRAY__H__
#define __BYTEARRAY__H__

#include <stdlib.h>

class ByteArray
{
    protected:
        int size;
        char *bytes;
    public:
        ByteArray(int size);
        ByteArray(unsigned char *charArr, int size);
        void setBytes(int fromPos, ByteArray subByteArray);
        void setBytes(ByteArray byteArray);
        void setByteAt(int pos, unsigned char byte);

        ByteArray getBytes(int from, int to);
        ByteArray getBytes();
        unsigned char getByteAt(int pos);  

        int getSize();
        ~ByteArray();
};

#endif  //!__BYTEARRAY__H__
