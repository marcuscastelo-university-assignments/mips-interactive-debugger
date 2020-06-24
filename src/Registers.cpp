#include "Registers.h"

Registers::Registers() {
    this->registerNamesMap[s("$zero")] = ZERO = new Register("$zero");
    this->registerNamesMap[s("$at")]   = AT = new Register("$at");
    this->registerNamesMap[s("$v0")]   = V0 = new Register("$v0");
    this->registerNamesMap[s("$v1")]   = V1 = new Register("$v1");
    this->registerNamesMap[s("$a0")]   = A0 = new Register("$a0");
    this->registerNamesMap[s("$a1")]   = A1 = new Register("$a1");
    this->registerNamesMap[s("$a2")]   = A2 = new Register("$a2");
    this->registerNamesMap[s("$a3")]   = A3 = new Register("$a3");
    this->registerNamesMap[s("$t0")]   = T0 = new Register("$t0");
    this->registerNamesMap[s("$t1")]   = T1 = new Register("$t1");
    this->registerNamesMap[s("$t2")]   = T2 = new Register("$t2");
    this->registerNamesMap[s("$t3")]   = T3 = new Register("$t3");
    this->registerNamesMap[s("$t4")]   = T4 = new Register("$t4");
    this->registerNamesMap[s("$t5")]   = T5 = new Register("$t5");
    this->registerNamesMap[s("$t6")]   = T6 = new Register("$t6");
    this->registerNamesMap[s("$t7")]   = T7 = new Register("$t7");
    this->registerNamesMap[s("$s0")]   = S0 = new Register("$s0");
    this->registerNamesMap[s("$s1")]   = S1 = new Register("$s1");
    this->registerNamesMap[s("$s2")]   = S2 = new Register("$s2");
    this->registerNamesMap[s("$s3")]   = S3 = new Register("$s3");
    this->registerNamesMap[s("$s4")]   = S4 = new Register("$s4");
    this->registerNamesMap[s("$s5")]   = S5 = new Register("$s5");
    this->registerNamesMap[s("$s6")]   = S6 = new Register("$s6");
    this->registerNamesMap[s("$s7")]   = S7 = new Register("$s7");
    this->registerNamesMap[s("$t8")]   = T8 = new Register("$t8");
    this->registerNamesMap[s("$t9")]   = T9 = new Register("$t9");
    this->registerNamesMap[s("$k0")]   = K0 = new Register("$k0");
    this->registerNamesMap[s("$k1")]   = K1 = new Register("$k1");
    this->registerNamesMap[s("$gp")]   = GP = new Register("$gp");
    this->registerNamesMap[s("$sp")]   = SP = new Register("$sp");
    this->registerNamesMap[s("$fp")]   = FP = new Register("$fp");
    this->registerNamesMap[s("$f0")]   = F0 = new Register("$f0");
    this->registerNamesMap[s("$f1")]   = F1 = new Register("$f1");
    this->registerNamesMap[s("$f2")]   = F2 = new Register("$f2");
    this->registerNamesMap[s("$f3")]   = F3 = new Register("$f3");
    this->registerNamesMap[s("$f4")]   = F4 = new Register("$f4");
    this->registerNamesMap[s("$f5")]   = F5 = new Register("$f5");
    this->registerNamesMap[s("$f6")]   = F6 = new Register("$f6");
    this->registerNamesMap[s("$f7")]   = F7 = new Register("$f7");
    this->registerNamesMap[s("$f8")]   = F8 = new Register("$f8");
    this->registerNamesMap[s("$f9")]   = F9 = new Register("$f9");
    this->registerNamesMap[s("$f10")]  = F10 = new Register("$f10");
    this->registerNamesMap[s("$f11")]  = F11 = new Register("$f11");
    this->registerNamesMap[s("$f12")]  = F12 = new Register("$f12");
    this->registerNamesMap[s("$f13")]  = F13 = new Register("$f13");
    this->registerNamesMap[s("$f14")]  = F14 = new Register("$f14");
    this->registerNamesMap[s("$f15")]  = F15 = new Register("$f15");
    this->registerNamesMap[s("$f16")]  = F16 = new Register("$f16");
    this->registerNamesMap[s("$f17")]  = F17 = new Register("$f17");
    this->registerNamesMap[s("$f18")]  = F18 = new Register("$f18");
    this->registerNamesMap[s("$f19")]  = F19 = new Register("$f19");
    this->registerNamesMap[s("$f20")]  = F20 = new Register("$f20");
    this->registerNamesMap[s("$f21")]  = F21 = new Register("$f21");
    this->registerNamesMap[s("$f22")]  = F22 = new Register("$f22");
    this->registerNamesMap[s("$f23")]  = F23 = new Register("$f23");
    this->registerNamesMap[s("$f24")]  = F24 = new Register("$f24");
    this->registerNamesMap[s("$f25")]  = F25 = new Register("$f25");
    this->registerNamesMap[s("$f26")]  = F26 = new Register("$f26");
    this->registerNamesMap[s("$f27")]  = F27 = new Register("$f27");
    this->registerNamesMap[s("$f28")]  = F28 = new Register("$f28");
    this->registerNamesMap[s("$f29")]  = F29 = new Register("$f29");
    this->registerNamesMap[s("$f30")]  = F30 = new Register("$f30");
    this->registerNamesMap[s("$f31")]  = F31 = new Register("$f31");
    this->registerNamesMap[s("$hi")]   = HI = new Register("$hi");
    this->registerNamesMap[s("$lo")]   = LO = new Register("$lo");
    this->registerNamesMap[s("$ra")]   = RA = new Register("$ra");
    this->registerNamesMap[s("$pc")]   = PC = new Register("$pc");
}

Register *Registers::getRegisterByName(std::string registerName) {
    return this->registerNamesMap[registerName];
}

void Registers::printRegisters(FILE *file_stream) {
    //TODO: deixara bonito
    fprintf(file_stream, "+-------------+");
    for (auto it = registerNamesMap.begin(); it != registerNamesMap.end(); it++)
        printRegister(it->second, file_stream);
    fprintf(file_stream, "+-------------+");


}

void Registers::printRegister(std::string name, FILE *file_stream) {
    printRegister(getRegisterByName(name), file_stream);
}

void Registers::printRegister(Register *reg, FILE *file_stream) {
    reg->print(file_stream);
}



Registers::~Registers() {

}