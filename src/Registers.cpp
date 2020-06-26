#include "Registers.h"
#include <stdexcept>

Registers::Registers():
ZERO(Register("$zero", READONLY)), AT(Register("$at")), V0(Register("$v0")), V1(Register("$v1")), A0(Register("$a0")), A1(Register("$a1")), A2(Register("$a2")), A3(Register("$a3")), T0(Register("$t0"), TEMPORARY), T1(Register("$t1"), TEMPORARY), T2(Register("$t2"),TEMPORARY), T3(Register("$t3"),TEMPORARY), T4(Register("$t4"),TEMPORARY), T5(Register("$t5"),TEMPORARY), T6(Register("$t6"),TEMPORARY), T7(Register("$t7"),TEMPORARY), S0(Register("$s0")), S1(Register("$s1")), S2(Register("$s2")), S3(Register("$s3")), S4(Register("$s4")), S5(Register("$s5")), S6(Register("$s6")), S7(Register("$s7")), T8(Register("$t8"),TEMPORARY), T9(Register("$t9"),TEMPORARY), K0(Register("$k0", -1, READONLY)), K1(Register("$k1", -1, READONLY)), GP(Register("$gp")), SP(Register("$sp")), FP(Register("$fp")), F0(Register("$f0")), F1(Register("$f1")), F2(Register("$f2")), F3(Register("$f3")), F4(Register("$f4", 0, TEMPORARY)), F5(Register("$f5", 0, TEMPORARY)), F6(Register("$f6", 0, TEMPORARY)), F7(Register("$f7", 0, TEMPORARY)), F8(Register("$f8", 0, TEMPORARY)), F9(Register("$f9", 0, TEMPORARY)), F10(Register("$f10", 0, TEMPORARY)), F11(Register("$f11"),TEMPORARY), F12(Register("$f12"),TEMPORARY), F13(Register("$f13"),TEMPORARY), F14(Register("$f14"),TEMPORARY), F15(Register("$f15"),TEMPORARY), F16(Register("$f16"),TEMPORARY), F17(Register("$f17"),TEMPORARY), F18(Register("$f18"),TEMPORARY), F19(Register("$f19"),TEMPORARY), F20(Register("$f20")), F21(Register("$f21")), F22(Register("$f22")), F23(Register("$f23")), F24(Register("$f24")), F25(Register("$f25")), F26(Register("$f26")), F27(Register("$f27")), F28(Register("$f28")), F29(Register("$f29")), F30(Register("$f30")), F31(Register("$f31")), HI(Register("$hi")), LO(Register("$lo")), RA(Register("$ra")), PC(Register("$pc", -4))
{
    this->registerNamesMap[s("$zero")] = &ZERO;
    this->registerNamesMap[s("$at")]   = &AT;
    this->registerNamesMap[s("$v0")]   = &V0;
    this->registerNamesMap[s("$v1")]   = &V1;
    this->registerNamesMap[s("$a0")]   = &A0;
    this->registerNamesMap[s("$a1")]   = &A1;
    this->registerNamesMap[s("$a2")]   = &A2;
    this->registerNamesMap[s("$a3")]   = &A3;
    this->registerNamesMap[s("$t0")]   = &T0;
    this->registerNamesMap[s("$t1")]   = &T1;
    this->registerNamesMap[s("$t2")]   = &T2;
    this->registerNamesMap[s("$t3")]   = &T3;
    this->registerNamesMap[s("$t4")]   = &T4;
    this->registerNamesMap[s("$t5")]   = &T5;
    this->registerNamesMap[s("$t6")]   = &T6;
    this->registerNamesMap[s("$t7")]   = &T7;
    this->registerNamesMap[s("$s0")]   = &S0;
    this->registerNamesMap[s("$s1")]   = &S1;
    this->registerNamesMap[s("$s2")]   = &S2;
    this->registerNamesMap[s("$s3")]   = &S3;
    this->registerNamesMap[s("$s4")]   = &S4;
    this->registerNamesMap[s("$s5")]   = &S5;
    this->registerNamesMap[s("$s6")]   = &S6;
    this->registerNamesMap[s("$s7")]   = &S7;
    this->registerNamesMap[s("$t8")]   = &T8;
    this->registerNamesMap[s("$t9")]   = &T9;
    this->registerNamesMap[s("$k0")]   = &K0;
    this->registerNamesMap[s("$k1")]   = &K1;
    this->registerNamesMap[s("$gp")]   = &GP;
    this->registerNamesMap[s("$sp")]   = &SP;
    this->registerNamesMap[s("$fp")]   = &FP;
    this->registerNamesMap[s("$f0")]   = &F0;
    this->registerNamesMap[s("$f1")]   = &F1;
    this->registerNamesMap[s("$f2")]   = &F2;
    this->registerNamesMap[s("$f3")]   = &F3;
    this->registerNamesMap[s("$f4")]   = &F4;
    this->registerNamesMap[s("$f5")]   = &F5;
    this->registerNamesMap[s("$f6")]   = &F6;
    this->registerNamesMap[s("$f7")]   = &F7;
    this->registerNamesMap[s("$f8")]   = &F8;
    this->registerNamesMap[s("$f9")]   = &F9;
    this->registerNamesMap[s("$f10")]  = &F10;
    this->registerNamesMap[s("$f11")]  = &F11;
    this->registerNamesMap[s("$f12")]  = &F12;
    this->registerNamesMap[s("$f13")]  = &F13;
    this->registerNamesMap[s("$f14")]  = &F14;
    this->registerNamesMap[s("$f15")]  = &F15;
    this->registerNamesMap[s("$f16")]  = &F16;
    this->registerNamesMap[s("$f17")]  = &F17;
    this->registerNamesMap[s("$f18")]  = &F18;
    this->registerNamesMap[s("$f19")]  = &F19;
    this->registerNamesMap[s("$f20")]  = &F20;
    this->registerNamesMap[s("$f21")]  = &F21;
    this->registerNamesMap[s("$f22")]  = &F22;
    this->registerNamesMap[s("$f23")]  = &F23;
    this->registerNamesMap[s("$f24")]  = &F24;
    this->registerNamesMap[s("$f25")]  = &F25;
    this->registerNamesMap[s("$f26")]  = &F26;
    this->registerNamesMap[s("$f27")]  = &F27;
    this->registerNamesMap[s("$f28")]  = &F28;
    this->registerNamesMap[s("$f29")]  = &F29;
    this->registerNamesMap[s("$f30")]  = &F30;
    this->registerNamesMap[s("$f31")]  = &F31;
    this->registerNamesMap[s("$hi")]   = &HI;
    this->registerNamesMap[s("$lo")]   = &LO;
    this->registerNamesMap[s("$ra")]   = &RA;
    this->registerNamesMap[s("$pc")]   = &PC;
}

Register &Registers::getRegisterByName(const std::string& registerName) const {
    auto it = this->registerNamesMap.find(registerName);
    if (it == registerNamesMap.end()) throw std::invalid_argument("Trying to get invalid register name");
    return *it->second;
}

void Registers::printRegisters(FILE *file_stream) const {
    //TODO: deixar bonito
    fprintf(file_stream, "+-------------+\n");
    for (auto it = registerNamesMap.begin(); it != registerNamesMap.end(); it++)
        printRegister(*it->second, file_stream);
    fprintf(file_stream, "+-------------+\n");


}

void Registers::printRegister(const std::string& name, FILE *file_stream) const {
    printRegister(getRegisterByName(name), file_stream);
}

void Registers::printRegister(const Register& reg, FILE *file_stream) const {
    reg.print(file_stream);
}

bool Registers::hasRegister(const std::string& name) const {
    return !(registerNamesMap.find(name) == registerNamesMap.end());
}

void Registers::setValue(const std::string& name, int value) const {
    Register &reg = getRegisterByName(name); 
    reg.setValue(value);
}

int Registers::getValue(const std::string& name) const {
    Register &reg = getRegisterByName(name);
    return reg.asInt();
}

Registers::~Registers() {}