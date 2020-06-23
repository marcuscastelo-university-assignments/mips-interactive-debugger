#include "Registers.h"

Registers::Registers() {
    this->registerNamesMap[s("$zero")] = Register("$zero");
    this->registerNamesMap[s("$at")] = Register("$at");
    this->registerNamesMap[s("$v0")] = Register("$v0");
    this->registerNamesMap[s("$v1")] = Register("$v1");
    this->registerNamesMap[s("$a0")] = Register("$a0");
    this->registerNamesMap[s("$a1")] = Register("$a1");
    this->registerNamesMap[s("$a2")] = Register("$a2");
    this->registerNamesMap[s("$a3")] = Register("$a3");
    this->registerNamesMap[s("$t0")] = Register("$t0");
    this->registerNamesMap[s("$t1")] = Register("$t1");
    this->registerNamesMap[s("$t2")] = Register("$t2");
    this->registerNamesMap[s("$t3")] = Register("$t3");
    this->registerNamesMap[s("$t4")] = Register("$t4");
    this->registerNamesMap[s("$t5")] = Register("$t5");
    this->registerNamesMap[s("$t6")] = Register("$t6");
    this->registerNamesMap[s("$t7")] = Register("$t7");
    this->registerNamesMap[s("$s0")] = Register("$s0");
    this->registerNamesMap[s("$s1")] = Register("$s1");
    this->registerNamesMap[s("$s2")] = Register("$s2");
    this->registerNamesMap[s("$s3")] = Register("$s3");
    this->registerNamesMap[s("$s4")] = Register("$s4");
    this->registerNamesMap[s("$s5")] = Register("$s5");
    this->registerNamesMap[s("$s6")] = Register("$s6");
    this->registerNamesMap[s("$s7")] = Register("$s7");
    this->registerNamesMap[s("$t8")] = Register("$t8");
    this->registerNamesMap[s("$t9")] = Register("$t9");
    this->registerNamesMap[s("$k0")] = Register("$k0");
    this->registerNamesMap[s("$k1")] = Register("$k1");
    this->registerNamesMap[s("$gp")] = Register("$gp");
    this->registerNamesMap[s("$sp")] = Register("$sp");
    this->registerNamesMap[s("$fp")] = Register("$fp");
    this->registerNamesMap[s("$f0")] = Register("$f0");
    this->registerNamesMap[s("$f1")] = Register("$f1");
    this->registerNamesMap[s("$f2")] = Register("$f2");
    this->registerNamesMap[s("$f3")] = Register("$f3");
    this->registerNamesMap[s("$f4")] = Register("$f4");
    this->registerNamesMap[s("$f5")] = Register("$f5");
    this->registerNamesMap[s("$f6")] = Register("$f6");
    this->registerNamesMap[s("$f7")] = Register("$f7");
    this->registerNamesMap[s("$f8")] = Register("$f8");
    this->registerNamesMap[s("$f9")] = Register("$f9");
    this->registerNamesMap[s("$f10")] = Register("$f10");
    this->registerNamesMap[s("$f11")] = Register("$f11");
    this->registerNamesMap[s("$f12")] = Register("$f12");
    this->registerNamesMap[s("$f13")] = Register("$f13");
    this->registerNamesMap[s("$f14")] = Register("$f14");
    this->registerNamesMap[s("$f15")] = Register("$f15");
    this->registerNamesMap[s("$f16")] = Register("$f16");
    this->registerNamesMap[s("$f17")] = Register("$f17");
    this->registerNamesMap[s("$f18")] = Register("$f18");
    this->registerNamesMap[s("$f19")] = Register("$f19");
    this->registerNamesMap[s("$f20")] = Register("$f20");
    this->registerNamesMap[s("$f21")] = Register("$f21");
    this->registerNamesMap[s("$f22")] = Register("$f22");
    this->registerNamesMap[s("$f23")] = Register("$f23");
    this->registerNamesMap[s("$f24")] = Register("$f24");
    this->registerNamesMap[s("$f25")] = Register("$f25");
    this->registerNamesMap[s("$f26")] = Register("$f26");
    this->registerNamesMap[s("$f27")] = Register("$f27");
    this->registerNamesMap[s("$f28")] = Register("$f28");
    this->registerNamesMap[s("$f29")] = Register("$f29");
    this->registerNamesMap[s("$f30")] = Register("$f30");
    this->registerNamesMap[s("$f31")] = Register("$f31");
    this->registerNamesMap[s("$HI")] = Register("$HI");
    this->registerNamesMap[s("$LO")] = Register("$LO");
    this->registerNamesMap[s("$ra")] = Register("$ra");
    this->registerNamesMap[s("$pc")] = Register("$pc");
}

Registers::~Registers() {
    
}