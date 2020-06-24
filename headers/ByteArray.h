#include <stdlib.h>

class ByteArray
{
    protected:
        int size;
        char *bytes;
    public:
        ByteArray(int size);
        ByteArray(unsigned char *charArr, int size);
        void setBytes(unsigned char *charArr, int size);
        unsigned char getByteAt(int pos);
        void setByteAt(int pos, unsigned char byte);
        ~ByteArray();
};


