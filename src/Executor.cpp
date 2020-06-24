#include "Executor.h"
#include "Instruction.h"
#include <iostream>

Executor::Executor() {
    interpreter = new Interpreter(this);
    registers= new Registers();
}

Executor::~Executor() {
    delete interpreter;
    delete registers;
}

Instruction *Executor::executeInstruction(std::string instructionStr) {
    Instruction *instruction = interpreter->interpretInstruction(instructionStr);
    instruction->execute();
    return instruction;
}

Registers *Executor::getRegisters() {
    return registers;
}

//TODO: Questão da stack
void Executor::_lw(Register *reg1, Register *reg2, int offset) {
    int stackAddress = reg2->getValueAsInt() + offset;
    reg1->setValue(stack.loadBytes(stackAddress, 4));
}

void Executor::_sw(Register *reg1, Register *reg2, int offset) {
    int stackAddress = reg2->getValueAsInt() + offset;
    stack.writeBytes(stackAddress, reg1->getValue().asByteArray(), 4);
}

void Executor::_lb(Register *reg1, Register *reg2,int offset) {
    int stackAddress = reg2->getValueAsInt() + offset;
    reg1->setValue(stack.loadByte(stackAddress));
}

void Executor::_sb(Register *reg1, Register *reg2,int offset) {
    int stackAddress = reg2->getValueAsInt() + offset;
    stack.writeByte(stackAddress, reg1->getValue().asByteArray()[0]);
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

void Executor::_b(int jumpAddress){
    _beq(registers->ZERO, registers->ZERO, jumpAddress);
}

void Executor::_bal(int jumpAddress){
    _bgezal(registers->ZERO, jumpAddress);
}

void Executor::_bgt(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers->AT, reg2,reg1);
    _bne(registers->AT, registers->ZERO, jumpAddress);    
}


void Executor::_blt(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers->AT, reg1, reg2);
    _bne(registers->AT, registers->ZERO, jumpAddress);    
}

void Executor::_bge(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers->AT, reg1, reg2);
    _beq(registers->AT, registers->ZERO, jumpAddress);    
}

void Executor::_ble(Register *reg1, Register *reg2, int jumpAddress){
    _slt(registers->AT, reg2, reg1);
    _beq(registers->AT, registers->ZERO, jumpAddress);    
}

void Executor::_bgtu(Register *reg1, Register *reg2, int jumpAddress){
    _sltu(registers->AT, reg2, reg1);
    _bne(registers->AT, registers->ZERO, jumpAddress);    
}

void Executor::_beqz(Register *reg, int jumpAddress){
    _beq(reg, registers->ZERO, jumpAddress);    
}

void Executor::_beqi(Register *reg1, int immediate, int jumpAddress){
    _ori(registers->AT, registers->ZERO, immediate);    
    _bne(reg1, registers->AT, jumpAddress);    
}

//TODO: Questão do jump e tamanho da stack
void Executor::_jump(int jumpAddress){
    if(jumpAddress < 0 || jumpAddress >= stack.getStackSize()) printf("ERROR: Jump adress not implemented.\n");
    else registers->PC->setValue(jumpAddress);
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
    registers->LO->setValue(reg1->getValueAsInt() * reg2->getValueAsInt());   
}

void Executor::_mflo(Register *reg){
    reg->copyValue(registers->LO);   
}

void Executor::_mfhi(Register *reg){
    reg->copyValue(registers->HI);
}


void Executor::_mul(Register *reg1,Register *reg2,Register *reg3){
    _mult(reg2,reg3);
    _mflo(reg1);
}

void Executor::_div2(Register *reg1,Register *reg2) { 
    registers->LO->setValue(reg1->getValueAsInt() / reg2->getValueAsInt());   
    registers->HI->setValue(reg1->getValueAsInt() % reg2->getValueAsInt());
}

void Executor::_div3(Register *reg1,Register *reg2,Register *reg3) { 
    _div2(reg2,reg3);
    _mflo(reg1);
}

void Executor::_rem(Register *reg1,Register *reg2,Register *reg3) { 
    _div2(reg2,reg3);
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
    registers->RA->copyValue(registers->PC);
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
    registers->LO->setValue((int)((unsigned)reg1->getValueAsInt() / (unsigned)reg2->getValueAsInt()));   
    registers->HI->setValue((int)((unsigned)reg1->getValueAsInt() % (unsigned)reg2->getValueAsInt()));
}

void Executor::_jr(Register *reg) {
    _jump(reg->getValueAsInt());
}

void Executor::_jalr(Register *reg) {
    _jal(reg->getValueAsInt());
}

void Executor::_lui(Register *reg, int immediate){
    reg->setValue(immediate << 16);
}

void Executor::_sll(Register *reg1, Register *reg2, int immediate){
    if (immediate < 0) _srl(reg1, reg2, -immediate);
    else reg1->setValue(reg2->getValueAsInt() << immediate);
}

void Executor::_sllv(Register *reg1, Register *reg2, Register *reg3){
    _sll(reg1, reg2, reg3->getValueAsInt());
}

void Executor::_sra(Register *reg1, Register *reg2, int immediate){
    reg1->setValue(reg2->getValueAsInt() >> immediate);
}

void Executor::_srl(Register *reg1, Register *reg2, int immediate){
    if (immediate == 0) return;
    int zeros = 0b01111111111111111111111111111111 >> (immediate-1);     
    reg1->setValue(zeros & (reg2->getValueAsInt() >> immediate));
}

void Executor::_noop() {}
void Executor::_nop() {}

void Executor::_srlv(Register *reg1, Register *reg2, Register *reg3){
    _srl(reg1, reg2, reg3->getValueAsInt());
}


void Executor::_move(Register *reg1, Register *reg2) {
    _or(reg1, reg2, registers->ZERO);
}

void Executor::_clear(Register *reg){
    _or(reg, registers->ZERO , registers->ZERO);
}

void Executor::_li(Register *reg1, short immediate){
    _ori(reg1, registers->ZERO, (int)immediate);
}

void Executor::_li(Register *reg1, int immediate){
    _lui(reg1, reg1->getValueAsInt() >> 16);
    _ori(reg1, reg1, immediate & 0x0000FFFF); 
}

void Executor::_la(Register *reg1, int address){
    _li(reg1, address);
}

void Executor::_nor(Register *reg1, Register *reg2,Register *reg3){
    reg1->setValue(~(reg2->getValueAsInt() | reg3->getValueAsInt()));
}

void Executor::_not(Register *reg1, Register *reg2){
    _nor(reg1, reg2, registers->ZERO);
}


//TODO: tirar foda
//Área FODA do syscall
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void Executor::syscall() {
    int operationCode = registers->V0->getValueAsInt();
    if (operationCode == 1) {
        std::cout << registers->A0->getValueAsInt();
    }
    else if (operationCode == 2){
        std::cout << "WARNING: Syscall not implemented" << std::endl;
    }
    else if (operationCode == 3){
        std::cout << "WARNING: Syscall not implemented" << std::endl;        
    }
    else if (operationCode == 4){
        //TODO: permitir acesso a outras regiões que não a stack
        int stringAddress = registers->A0->getValueAsInt();
        char c;
        while ((c = stack.loadByte(stringAddress++)) != '\0') std::cout << c;
        std::cout << std::endl;
    }
    else if (operationCode == 5){
        int temp;
        std::cin >> temp;
        registers->V0->setValue(temp);
    }
    else if (operationCode == 6){
        std::cout << "WARNING: Syscall not implemented" << std::endl;                
    }
    else if (operationCode == 7){
        std::cout << "WARNING: Syscall not implemented" << std::endl;                
    }
    else if (operationCode == 8){
        int offset = 0;
        char c;
        for (int i = 0; i < registers->A1->getValueAsInt(); i++) {
            std::cin >> c;
            stack.writeByte(registers->A0->getValueAsInt() + offset++, c);
        }
    }
    else if (operationCode == 9){
        std::cout << "WARNING: Syscall not implemented" << std::endl;                
        
    }
    else if (operationCode == 10){
        std::cout << "WARNING: Syscall not implemented" << std::endl;                
    }
    else if (operationCode == 11){
        //TODO: verificar qual é o low-order byte (vide https://i.imgur.com/HhQsemz.png)
        std::cout << registers->A0->getValue().asByteArray()[0];
    }
    else if (operationCode == 12){
        std::cout << "WARNING: Syscall not implemented" << std::endl;                
    }
    else std::cout << "WARNING: Syscall out of range" << std::endl;
}

