#ifndef __BYTEARRAY__H__
#define __BYTEARRAY__H__

#include <vector>
#include <stdio.h>
#include <stdlib.h>

class ByteArray
{
    protected:
        std::vector<unsigned char> bytes;
    public:
        ByteArray(const ByteArray &byteArray);
        ByteArray(int size);
        ByteArray(unsigned char *charArr, int size);
        void setBytes(int fromPos, const ByteArray& subByteArray);
        void setBytes(unsigned char *charArr, int size);
        void setBytes(const ByteArray& byteArray);
        void setByteAt(int pos, unsigned char byte);

        const ByteArray getBytes(int from, int size) const;
        const ByteArray getBytes() const;
        unsigned char getByteAt(int pos) const;  

        void print(FILE *file_stream = stdout) const;

        int getSize() const;

        char operator[] (int pos);
};

#endif  //!__BYTEARRAY__H__
