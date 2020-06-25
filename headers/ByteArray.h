#ifndef __BYTEARRAY__H__
#define __BYTEARRAY__H__

#include <stdlib.h>


//TODO: operator[]
class ByteArray
{
    protected:
        int size;
        unsigned char *bytes;
    public:
        ByteArray(const ByteArray &byteArray);
        ByteArray(int size);
        ByteArray(unsigned char *charArr, int size);
        void setBytes(int fromPos, ByteArray subByteArray);
        void setBytes(unsigned char *charArr, int size);
        void setBytes(const ByteArray& byteArray);
        void setByteAt(int pos, unsigned char byte);

        const ByteArray getBytes(int from, int to) const;
        const ByteArray getBytes() const;
        unsigned char getByteAt(int pos) const;  

        int getSize() const;
        ~ByteArray();
};

#endif  //!__BYTEARRAY__H__
