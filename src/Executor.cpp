#include "Executor.h"

Word Executor::_lw(int stackAddress) {
    return Word(stack.loadBytes(stackAddress, 4));
}

void Executor::_sw(int stackAdress, Word *word) {
    stack.writeBytes(stackAdress, word->asByteArray(), 4);
}

char Executor::_lb(int stackAddress) {
    return stack.loadByte(stackAddress);
}

void Executor::_sb(int stackAdress, char byte) {
    stack.writeByte(stackAdress, byte);
}

void Executor::_beq(Register *reg1, Register *reg2, int jumpAddress){
    if(reg1->getValueAsInt() == reg2->getValueAsInt()) _jump(jumpAddress);    
}

void Executor::_bgez(Register *reg, int jumpAddress){
    if(reg->getValueAsInt() >= 0) _jump(jumpAddress);    
}

void Executor::_bgezal(Register *reg, int jumpAddress){
    if(reg->getValueAsInt() >= 0) _jal(jumpAddress);    
    
}

void Executor::_bgtz(Register *reg, int jumpAddress){
    if(reg->getValueAsInt() > 0) _jump(jumpAddress);    
}

void Executor::_blez(Register *reg, int jumpAddress){
    if(reg->getValueAsInt() <= 0) _jump(jumpAddress);    
}

void Executor::_bltz(Register *reg, int jumpAddress){
    if(reg->getValueAsInt() < 0) _jump(jumpAddress);    
}

void Executor::_bltzal(Register *reg, int jumpAddress){
    if(reg->getValueAsInt() < 0) _jal(jumpAddress);    
}

void Executor::_bne(Register *reg1, Register *reg2, int jumpAddress){
    if(reg1->getValueAsInt() != reg2->getValueAsInt()) _jump(jumpAddress);    
}

//TODO:

void Executor::_b(int jumpAddress){
    _beq(registers.ZERO, registers.ZERO, jumpAddress);
}

void Executor::_bal(int jumpAddress){
    _bgezal(registers.ZERO, jumpAddress);
}

void Executor::_bgt(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers.AT, reg2,reg1);
    _bne(registers.AT, registers.ZERO, jumpAddress);    
}


void Executor::_blt(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers.AT, reg1, reg2);
    _bne(registers.AT, registers.ZERO, jumpAddress);    
}

void Executor::_bge(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers.AT, reg1, reg2);
    _beq(registers.AT, registers.ZERO, jumpAddress);    
}

void Executor::_ble(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers.AT, reg2, reg1);
    _beq(registers.AT, registers.ZERO, jumpAddress);    
}

void Executor::_bgtu(Register *reg1, Register *reg2, int jumpAddress){
    _sltu(registers.AT, reg2, reg1);
    _bne(registers.AT, registers.ZERO, jumpAddress);    
}

void Executor::_beqz(Register *reg, int jumpAddress){
    _beq(reg, registers.ZERO, jumpAddress);    
}

void Executor::_beq(Register *reg1, int immediate, int jumpAddress){
    _ori(registers.AT, registers.ZERO, immediate);    
    _beq(reg1, registers.AT, jumpAddress);    
}

void Executor::_beq(Register *reg1, int immediate, int jumpAddress){
    _ori(registers.AT, registers.ZERO, immediate);    
    _beq(reg1, registers.AT, jumpAddress);    
}

void Executor::_beq(Register *reg1, int immediate, int jumpAddress){
    _ori(registers.AT, registers.ZERO, immediate);    
    _bne(reg1, registers.AT, jumpAddress);    
}

//TODO:
void Executor::_jump(int jumpAddress){
    if(jumpAddress < 0 || jumpAddress >= stack.getStackSize()) printf("ERROR: Jump adress out of range.\n");
    else registers.PC->setValue(jumpAddress);
}

void Executor::_add(Register *reg1,Register *reg2,Register *reg3){
    reg1->setValue(reg2->getValueAsInt() + reg3->getValueAsInt());   
}

void Executor::_addi(Register *reg1, Register *reg2, int immediate){
    reg1->setValue(reg2->getValueAsInt() + immediate);   
}



void Executor::_sub(Register *reg1,Register *reg2,Register *reg3){
    reg1->setValue(reg2->getValueAsInt() - reg3->getValueAsInt());   
}

void Executor::_mult(Register *reg1,Register *reg2){
    registers.LO->setValue(reg1->getValueAsInt() * reg2->getValueAsInt());   
}

void Executor::_mflo(Register *reg){
    reg->copyValue(registers.LO);   
}

void Executor::_mfhi(Register *reg){
    reg->copyValue(registers.HI);
}


void Executor::_mul(Register *reg1,Register *reg2,Register *reg3){
    _mult(reg2,reg1);
    _mflo(reg1);
}

void Executor::_div(Register *reg1,Register *reg2) { 
    registers.LO->setValue(reg1->getValueAsInt() / reg2->getValueAsInt());   
    registers.HI->setValue(reg1->getValueAsInt() % reg2->getValueAsInt());
}

void Executor::_div(Register *reg1,Register *reg2,Register *reg3) { 
    _div(reg2,reg3);
    _mflo(reg1);
}

void Executor::_rem(Register *reg1,Register *reg2,Register *reg3) { 
    _div(reg2,reg3);
    _mfhi(reg1);
}

void Executor::_and(Register *reg1, Register *reg2, Register *reg3) {
    reg1->setValue(reg2->getValueAsInt() & reg3->getValueAsInt());
}

void Executor::_or(Register *reg1, Register *reg2, Register *reg3) {
    reg1->setValue(reg2->getValueAsInt() | reg3->getValueAsInt());
}

void Executor::_xor(Register *reg1, Register *reg2, Register *reg3) {
    reg1->setValue(reg2->getValueAsInt() ^ reg3->getValueAsInt());
}

void Executor::_andi(Register *reg1, Register *reg2, int immediate) {
    reg1->setValue(reg2->getValueAsInt() & immediate);
}

void Executor::_ori(Register *reg1, Register *reg2, int immediate) {
    reg1->setValue(reg2->getValueAsInt() | immediate);
}

void Executor::_xori(Register *reg1, Register *reg2, int immediate) {
    reg1->setValue(reg2->getValueAsInt() ^ immediate);
}

void Executor::_slt(Register *reg1, Register *reg2, Register *reg3){
    if(reg2->getValueAsInt() < reg3->getValueAsInt()) reg1->setValue(1);
    else reg1->setValue(0);
}

void Executor::_sltu(Register *reg1, Register *reg2, Register *reg3){
    if((unsigned)reg2->getValueAsInt() < (unsigned)reg3->getValueAsInt()) reg1->setValue(1); 
    else reg1->setValue(0);
}

void Executor::_slti(Register *reg1, Register *reg2, int immediate){
    if(reg2->getValueAsInt() < immediate) reg1->setValue(1);
    else reg1->setValue(0);
}

void Executor::_sltiu(Register *reg1, Register *reg2, unsigned immediate){
    if((unsigned)reg2->getValueAsInt() < immediate) reg1->setValue(1);
    else reg1->setValue(0);
}

void Executor::_jal(int jumpAddress){
    registers.RA->copyValue(registers.PC);
    _jump(jumpAddress);
}

void Executor::_addiu(Register *reg1, Register *reg2, unsigned int immediate){
    reg1->setValue((int)((unsigned)reg2->getValueAsInt() + immediate));   
}

void Executor::_addu(Register *reg1,Register *reg2,Register *reg3){
    _add(reg1, reg2, reg3);
}

void Executor::_subu(Register *reg1,Register *reg2,Register *reg3){
    _sub(reg1, reg2, reg3);
}

void Executor::_divu(Register *reg1,Register *reg2) { 
    registers.LO->setValue((int)((unsigned)reg1->getValueAsInt() / (unsigned)reg2->getValueAsInt()));   
    registers.HI->setValue((int)((unsigned)reg1->getValueAsInt() % (unsigned)reg2->getValueAsInt()));
}

void Executor::_jr(Register *reg) {
    _jump(reg->getValueAsInt());
}

void Executor::_lui(Register *reg, int immediate){
    reg->setValue(immediate << 16);
}

void Executor::_sll(Register *reg1, Register *reg2, int immediate){
    reg1->setValue(reg2->getValueAsInt() << immediate);
}

void Executor::_sllv(Register *reg1, Register *reg2, Register *reg3){
    _sll(reg1, reg2, reg3->getValueAsInt());
}

void Executor::_sra(Register *reg1, Register *reg2, int immediate){
    reg1->setValue( reg2->getValueAsInt() >> immediate));
}

void Executor::_srl(Register *reg1, Register *reg2, int immediate){
    int zeros = 0b01111111111111111111111111111111 >> immediate;     
    reg1->setValue(zeros & (reg2->getValueAsInt() >> immediate));
}



void Executor::_noop() {}
void Executor::_nop() {}

/*

addiu *
addu *
divu *
jr *
lui *
multu
noop *
sll *
sllv *
sra 
srl
srlv
subu *
syscall





move
clear
li 16
li 32
la
mul -> checar?
div3 -> checar
jalr
not
nop *

*/