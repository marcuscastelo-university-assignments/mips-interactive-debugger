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
        Word operator+(Word &other);
        Word operator-(Word &other);
        Word operator*(Word &other);
        Word operator/(Word &other);
        Word operator%(Word &other);
        Word operator&(Word &other);
        Word operator|(Word &other);
        Word operator^(Word &other);
        bool operator<(Word &other);
        bool operator<=(Word &other);
        bool operator>(Word &other);
        bool operator>=(Word &other);
        bool operator==(Word &other);

        Word operator+(int &value);
        Word operator-(int &value);
        Word operator*(int &value);
        Word operator/(int &value);
        Word operator%(int &value);
        Word operator&(int &value);
        Word operator|(int &value);
        Word operator^(int &value);
};

