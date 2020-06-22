#include "AsmProgram.h"

#define s(x) (std::string(x))

AsmProgram::AsmProgram() {
    this->registerNameToId[s("$zero")] = 0;
    this->registerNameToId[s("$at")] =   1;
    this->registerNameToId[s("$v0")] =   2;
    this->registerNameToId[s("$v1")] =   3;
    this->registerNameToId[s("$a0")] =   4;
    this->registerNameToId[s("$a1")] =   5;
    this->registerNameToId[s("$a2")] =   6;
    this->registerNameToId[s("$a3")] =   7;
    this->registerNameToId[s("$t0")] =   8;
    this->registerNameToId[s("$t1")] =   9;
    this->registerNameToId[s("$t2")] =   10;
    this->registerNameToId[s("$t3")] =   11;
    this->registerNameToId[s("$t4")] =   12;
    this->registerNameToId[s("$t5")] =   13;
    this->registerNameToId[s("$t6")] =   14;
    this->registerNameToId[s("$t7")] =   15;
    this->registerNameToId[s("$s0")] =   16;
    this->registerNameToId[s("$s1")] =   17;
    this->registerNameToId[s("$s2")] =   18;
    this->registerNameToId[s("$s3")] =   19;
    this->registerNameToId[s("$s4")] =   20;
    this->registerNameToId[s("$s5")] =   21;
    this->registerNameToId[s("$s6")] =   22;
    this->registerNameToId[s("$s7")] =   23;
    this->registerNameToId[s("$t8")] =   24;
    this->registerNameToId[s("$t9")] =   25;
    this->registerNameToId[s("$k0")] =   26;
    this->registerNameToId[s("$k1")] =   27;
    this->registerNameToId[s("$gp")] =   28;
    this->registerNameToId[s("$sp")] =   29;
    this->registerNameToId[s("$fp")] =   30;
    this->registerNameToId[s("$f0")] =   31;
    this->registerNameToId[s("$f1")] =   32;
    this->registerNameToId[s("$f2")] =   33;
    this->registerNameToId[s("$f3")] =   34;
    this->registerNameToId[s("$f4")] =   35;
    this->registerNameToId[s("$f5")] =   36;
    this->registerNameToId[s("$f6")] =   37;
    this->registerNameToId[s("$f7")] =   38;
    this->registerNameToId[s("$f8")] =   39;
    this->registerNameToId[s("$f9")] =   40;
    this->registerNameToId[s("$f10")] =  41;
    this->registerNameToId[s("$f11")] =  42;
    this->registerNameToId[s("$f12")] =  43;
    this->registerNameToId[s("$f13")] =  44;
    this->registerNameToId[s("$f14")] =  45;
    this->registerNameToId[s("$f15")] =  46;
    this->registerNameToId[s("$f16")] =  47;
    this->registerNameToId[s("$f17")] =  48;
    this->registerNameToId[s("$f18")] =  49;
    this->registerNameToId[s("$f19")] =  50;
    this->registerNameToId[s("$f20")] =  51;
    this->registerNameToId[s("$f21")] =  52;
    this->registerNameToId[s("$f22")] =  53;
    this->registerNameToId[s("$f23")] =  54;
    this->registerNameToId[s("$f24")] =  55;
    this->registerNameToId[s("$f25")] =  56;
    this->registerNameToId[s("$f26")] =  57;
    this->registerNameToId[s("$f27")] =  58;
    this->registerNameToId[s("$f28")] =  59;
    this->registerNameToId[s("$f29")] =  60;
    this->registerNameToId[s("$f30")] =  61;
    this->registerNameToId[s("$f31")] =  62;
    this->registerNameToId[s("$HI")] =   63;
    this->registerNameToId[s("$LO")] =   64;
    this->registerNameToId[s("$ra")] =   65;
    this->registerNameToId[s("$pc")] =   66;
}

AsmProgram::lw(int offset,){



}