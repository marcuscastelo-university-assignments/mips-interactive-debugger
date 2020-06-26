#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <map>
#include <string>

#include "Interpreter.h"
#include "Registers.h"
#include "ByteArray.h"
#include "Program.h"

typedef ByteArray Stack;
#define STACK_SIZE 4096 //4KB

class Interpreter;
class Instruction;
class Executor{
    private:
        Interpreter *interpreter;
        Program& program;
        Registers registers;
        Stack stack;

        void div2(Register *reg1,Register *reg2);
        void div3(Register *reg1,Register *reg2, Register *reg3);
        void beqi(Register *reg1, int immediate, int jumpAddress);
        void beq(Register *reg1, Register *reg2, int jumpAddress);
        void bnei(Register *reg, int immediate, int jumpAddress);
        void bne(Register *reg1, Register *reg2, int jumpAddress);
        void sub(Register *reg1,Register *reg2,Register *reg3);
    public:
        Executor(Program& program);
        ~Executor();

        const Program &getProgram() const;
        const Registers &getRegisters() const;
        Register &getRegister(const std::string& name) const;

        Instruction *executeInstructionStr(const std::string& instruction) const;
        bool hasRegister(const std::string& name) const;



        //void getInstructionInformation();

        void _lw(Register *reg1, Register *reg2, int offset);
        void _sw(Register *reg1, Register *reg2, int offset);
        void _lb(Register *reg1, Register *reg2,int offset);
        void _sb(Register *reg1, Register *reg2,int offset);
        void _beq(Register *reg1, Register *reg2, int jumpAddress, int immediate);
        void _bne(Register *reg1, Register *reg2, int jumpAddress, int immediate);
        void _bgez(Register *reg, int jumpAddress);
        void _bgezal(Register *reg, int jumpAddress);
        void _bgtz(Register *reg, int jumpAddress);
        void _blez(Register *reg, int jumpAddress);
        void _bltz(Register *reg, int jumpAddress);
        void _bltzal(Register *reg, int jumpAddress);
        void _b(int jumpAddress);
        void _bal(int jumpAddress);
        void _bgt(Register *reg1, Register *reg2, int jumpAddress);
        void _blt(Register *reg1, Register *reg2, int jumpAddress);
        void _bge(Register *reg1, Register *reg2, int jumpAddress);
        void _ble(Register *reg1, Register *reg2, int jumpAddress);
        void _bgtu(Register *reg1, Register *reg2, int jumpAddress);
        void _beqz(Register *reg, int jumpAddress);
        void _j(int);
        void _add(Register *reg1,Register *reg2,Register *reg3);
        void _addi(Register *reg1, Register *reg2, int immediate);
        void _sub(Register *reg1,Register *reg2,Register *reg3, int immediate);
        void _subi(Register *reg1, Register *reg2, int immediate);
        void _mult(Register *reg1,Register *reg2);
        void _multu(Register *reg1,Register *reg2);
        void _mflo(Register *reg);
        void _mfhi(Register *reg);
        void _mul(Register *reg1,Register *reg2,Register *reg3);

        void _div(Register *reg1,Register *reg2, Register *reg3 = NULL);
        void _rem(Register *reg1,Register *reg2, Register *reg3);
        void _and(Register *reg1, Register *reg2, Register *reg3);
        void _or(Register *reg1, Register *reg2, Register *reg3);
        void _xor(Register *reg1, Register *reg2, Register *reg3);
        void _andi(Register *reg1, Register *reg2, int immediate);
        void _ori(Register *reg1, Register *reg2, int immediate);
        void _xori(Register *reg1, Register *reg2, int immediate);
        void _slt(Register *reg1, Register *reg2, Register *reg3);
        void _sltu(Register *reg1, Register *reg2, Register *reg3);
        void _slti(Register *reg1, Register *reg2, int immediate);
        void _sltiu(Register *reg1, Register *reg2, unsigned immediate);
        void _jal(int jumpAddress);

        void _addiu(Register *reg1, Register *reg2, unsigned int immediate);
        void _addu(Register *reg1,Register *reg2,Register *reg3);
        void _subu(Register *reg1,Register *reg2,Register *reg3);
        void _divu(Register *reg1,Register *reg2);
                
        void _sllv(Register *reg1,Register *reg2,Register *reg3);
        void _jr(Register *reg);
        void _jalr(Register *reg);
        void _lui(Register *reg,int immediate);
        void _sll(Register *reg1,Register *reg2,int immediate);
        void _noop();
        void _nop();
        void _sra(Register *reg1, Register *reg2, int immediate);
        void _srl(Register *reg1, Register *reg2, int immediate);
        
        void _syscall();
        void _move(Register *reg1, Register *reg2);
        void _srlv(Register *reg1, Register *reg2, Register *reg3);
        void _clear(Register *reg);
        void _li(Register *reg1, short immediate);
        void _li(Register *reg1, int immediate);
        void _la(Register *reg1, int address);
        void _nor(Register *reg1, Register *reg2,Register *reg3);
        void _not(Register *reg1, Register *reg2);
        void _label();
        void _invalid(nullptr_t _);

};

#endif