#include "Registers.h"
#include <stdexcept>

Registers::Registers():
ZERO("$zero", READONLY), AT("$at"), V0("$v0"), V1("$v1"), A0("$a0"), A1("$a1"), A2("$a2"), A3("$a3"), T0("$t0", TEMPORARY), T1("$t1", TEMPORARY), T2("$t2",TEMPORARY), T3("$t3",TEMPORARY), T4("$t4",TEMPORARY), T5("$t5",TEMPORARY), T6("$t6",TEMPORARY), T7("$t7",TEMPORARY), S0("$s0"), S1("$s1"), S2("$s2"), S3("$s3"), S4("$s4"), S5("$s5"), S6("$s6"), S7("$s7"), T8("$t8",TEMPORARY), T9("$t9",TEMPORARY), K0("$k0", -1,READONLY), K1("$k1", -1,READONLY),GP("$gp"), SP("$sp"), FP("$fp"), F0("$f0"), F1("$f1"), F2("$f2"), F3("$f3"), F4("$f4", TEMPORARY), F5("$f5", TEMPORARY), F6("$f6", TEMPORARY), F7("$f7", TEMPORARY), F8("$f8", TEMPORARY), F9("$f9", TEMPORARY), F10("$f10", TEMPORARY), F11("$f11",TEMPORARY), F12("$f12",TEMPORARY), F13("$f13",TEMPORARY), F14("$f14",TEMPORARY), F15("$f15",TEMPORARY), F16("$f16",TEMPORARY), F17("$f17",TEMPORARY), F18("$f18",TEMPORARY), F19("$f19",TEMPORARY), F20("$f20"), F21("$f21"), F22("$f22"), F23("$f23"), F24("$f24"), F25("$f25"), F26("$f26"), F27("$f27"), F28("$f28"), F29("$f29"), F30("$f30"), F31("$f31"), HI("$hi"), LO("$lo"), RA("$ra"), PC("$pc", -4)
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


Registers::Registers(const Registers& other):
ZERO(other.ZERO), AT(other.AT), V0(other.V0), V1(other.V1), A0(other.A0), A1(other.A1), A2(other.A2), A3(other.A3), T0(other.T0), T1(other.T1), T2(other.T2), T3(other.T3), T4(other.T4), T5(other.T5), T6(other.T6), T7(other.T7), S0(other.S0), S1(other.S1), S2(other.S2), S3(other.S3), S4(other.S4), S5(other.S5), S6(other.S6), S7(other.S7), T8(other.T8), T9(other.T9), K0(other.K0),K1(other.K1),GP(other.GP), SP(other.SP), FP(other.FP), F0(other.F0), F1(other.F1), F2(other.F2), F3(other.F3), F4(other.F4), F5(other.F5), F6(other.F6), F7(other.F7), F8(other.F8), F9(other.F9), F10(other.F10), F11(other.F11), F12(other.F12), F13(other.F13), F14(other.F14), F15(other.F15), F16(other.F16), F17(other.F17), F18(other.F18), F19(other.F19), F20(other.F20), F21(other.F21), F22(other.F22), F23(other.F23), F24(other.F24), F25(other.F25), F26(other.F26), F27(other.F27), F28(other.F28), F29(other.F29), F30(other.F30), F31(other.F31), HI(other.HI), LO(other.LO), RA(other.RA), PC(other.PC)
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

std::map<std::string, Register*> Registers::getRegisterMap() const {
    return this->registerNamesMap;
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