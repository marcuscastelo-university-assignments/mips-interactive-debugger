#include "Executor.h"
#include "Instruction.h"
#include <iostream>

//TODO: implementar comportamentos esquisitos de registradores temporarios (j label, etc) (e outros obscutos)
Executor::Executor()
: interpreter(new Interpreter(this)), stack(STACK_SIZE)
{
    registers.SP.setWord(stack.getSize());
}

Executor::~Executor() {
    delete interpreter;
}

void printInstructionMistake(Instruction *interpretedInstruction) {
    printf("The instruction '%s' should have recieved:\n%d Register(s) and %d Integer(s), instead \n%d Register(s) and %d Integer(s) have been passed.\n", interpretedInstruction->toString().c_str(), interpretedInstruction->getRegistersSupposedCount() , interpretedInstruction->getIntegersSupposedCount(), interpretedInstruction->getRegistersCount(), interpretedInstruction->getIntegersCount());
}

Instruction *Executor::executeInstructionStr(const std::string& instructionStr) const {
    Instruction *interpretedInstruction = interpreter->interpretInstruction(instructionStr);
    
    if(interpretedInstruction->isUnknown()) fprintf(stderr, "ERROR: unknown instruction: '%s'\n", interpretedInstruction->toString().c_str());
    else if (interpretedInstruction->isValid()) interpretedInstruction->execute();
    else if (true) printInstructionMistake(interpretedInstruction);  //this->isForUsuarioBurro())
    

    return interpretedInstruction;
}

const Registers &Executor::getRegisters() const {
    return registers;
}

Register &Executor::getRegister(const std::string& name) const {
    if (!registers.hasRegister(name)) throw new std::invalid_argument("Trying to get invalid register");
    return registers.getRegisterByName(name);
}

bool Executor::hasRegister(const std::string& name) const {
    return registers.hasRegister(name);
}

//TODO: Questão da stack
void Executor::_lw(Register *reg1, Register *reg2, int offset)  {
    int stackAddress = reg2->asInt() + offset;
    reg1->setWord(stack.getBytes(stackAddress, 4));
}

void Executor::_sw(Register *reg1, Register *reg2, int offset)  {
    int stackAddress = reg2->asInt() + offset;
    stack.setBytes(stackAddress, reg1->getWord().asByteArray());
}

void Executor::_lb(Register *reg1, Register *reg2,int offset)  {
    int stackAddress = reg2->asInt() + offset;
    Word newWord = reg1->getWord();
    newWord.setByteAt(3, stack.getByteAt(stackAddress));
    reg1->setWord(newWord);   
}

void Executor::_sb(Register *reg1, Register *reg2,int offset) {
    int stackAddress = reg2->asInt() + offset;
    stack.setByteAt(stackAddress, reg1->getWord().asByteArray().getByteAt(3));
}

void Executor::_beq(Register *reg1, Register *reg2, int jumpAddress) {
    if(reg1->asInt() == reg2->asInt()) _jump(jumpAddress);    
}

void Executor::_bgez(Register *reg, int jumpAddress) {
    if(reg->asInt() >= 0) _jump(jumpAddress);    
}

void Executor::_bgezal(Register *reg, int jumpAddress) {
    if(reg->asInt() >= 0) _jal(jumpAddress);    
    
}

void Executor::_bgtz(Register *reg, int jumpAddress) {
    if(reg->asInt() > 0) _jump(jumpAddress);    
}

void Executor::_blez(Register *reg, int jumpAddress) {
    if(reg->asInt() <= 0) _jump(jumpAddress);    
}

void Executor::_bltz(Register *reg, int jumpAddress) {
    if(reg->asInt() < 0) _jump(jumpAddress);    
}

void Executor::_bltzal(Register *reg, int jumpAddress) {
    if(reg->asInt() < 0) _jal(jumpAddress);    
}

void Executor::_bne(Register *reg1, Register *reg2, int jumpAddress) {
    if(reg1->asInt() != reg2->asInt()) _jump(jumpAddress);    
}

void Executor::_b(int jumpAddress) {
    _beq((Register*)&registers.ZERO, (Register*)&registers.ZERO, jumpAddress);
}

void Executor::_bal(int jumpAddress) {
    _bgezal((Register*)&registers.ZERO, jumpAddress);
}

void Executor::_bgt(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg2,reg1);
    _bne((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}


void Executor::_blt(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg1, reg2);
    _bne((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_bge(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg1, reg2);
    _beq((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_ble(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg2, reg1);
    _beq((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_bgtu(Register *reg1, Register *reg2, int jumpAddress) {
    _sltu((Register*)&registers.AT, reg2, reg1);
    _bne((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_beqz(Register *reg, int jumpAddress) {
    _beq(reg, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_beqi(Register *reg1, int immediate, int jumpAddress) {
    _ori((Register*)&registers.AT, (Register*)&registers.ZERO, immediate);    
    _bne(reg1, (Register*)&registers.AT, jumpAddress);    
}

//TODO: Questão do jump e tamanho da stack
void Executor::_jump(int jumpAddress) {
    //TODO: PEGAR O TAMANHO DO PROGRAMA
    if(jumpAddress < 0 || jumpAddress >= 50135) printf("ERROR: Jump adress not implemented.\n");
    else registers.PC.setWord(jumpAddress);
}

void Executor::_add(Register *reg1,Register *reg2,Register *reg3) {
    reg1->setWord(reg2->asInt() + reg3->asInt());   
}

void Executor::_addi(Register *reg1, Register *reg2, int immediate) {
    reg1->setWord(reg2->asInt() + immediate);   
}

void Executor::_sub(Register *reg1,Register *reg2,Register *reg3) {
    reg1->setWord(reg2->asInt() - reg3->asInt());   
}

void Executor::_mult(Register *reg1,Register *reg2) {
    registers.LO.setWord(reg1->asInt() * reg2->asInt());   
}

void Executor::_mflo(Register *reg) {
    reg->copy(registers.LO);   
}

void Executor::_mfhi(Register *reg) {
    reg->copy(registers.HI);
}


void Executor::_mul(Register *reg1,Register *reg2,Register *reg3) {
    _mult(reg2,reg3);
    _mflo(reg1);
}

void Executor::_div2(Register *reg1,Register *reg2) {  
    registers.LO.setWord(reg1->asInt() / reg2->asInt());   
    registers.HI.setWord(reg1->asInt() % reg2->asInt());
}

void Executor::_div3(Register *reg1,Register *reg2,Register *reg3) {  
    _div2(reg2,reg3);
    _mflo(reg1);
}

void Executor::_rem(Register *reg1,Register *reg2,Register *reg3) {  
    _div2(reg2,reg3);
    _mfhi(reg1);
}

void Executor::_and(Register *reg1, Register *reg2, Register *reg3)  {
    reg1->setWord(reg2->asInt() & reg3->asInt());
}

void Executor::_or(Register *reg1, Register *reg2, Register *reg3)  {
    reg1->setWord(reg2->asInt() | reg3->asInt());
}

void Executor::_xor(Register *reg1, Register *reg2, Register *reg3)  {
    reg1->setWord(reg2->asInt() ^ reg3->asInt());
}

void Executor::_andi(Register *reg1, Register *reg2, int immediate)  {
    reg1->setWord(reg2->asInt() & immediate);
}

void Executor::_ori(Register *reg1, Register *reg2, int immediate)  {
    reg1->setWord(reg2->asInt() | immediate);
}

void Executor::_xori(Register *reg1, Register *reg2, int immediate)  {
    reg1->setWord(reg2->asInt() ^ immediate);
}

void Executor::_slt(Register *reg1, Register *reg2, Register *reg3) {
    if(reg2->asInt() < reg3->asInt()) reg1->setWord(1);
    else reg1->setWord(0);
}

void Executor::_sltu(Register *reg1, Register *reg2, Register *reg3) {
    if((unsigned)reg2->asInt() < (unsigned)reg3->asInt()) reg1->setWord(1); 
    else reg1->setWord(0);
}

void Executor::_slti(Register *reg1, Register *reg2, int immediate) {
    if(reg2->asInt() < immediate) reg1->setWord(1);
    else reg1->setWord(0);
}

void Executor::_sltiu(Register *reg1, Register *reg2, unsigned immediate) {
    if((unsigned)reg2->asInt() < immediate) reg1->setWord(1);
    else reg1->setWord(0);
}

void Executor::_jal(int jumpAddress) {
    registers.RA.copy(registers.PC);
    _jump(jumpAddress);
}

void Executor::_addiu(Register *reg1, Register *reg2, unsigned int immediate) {
    reg1->setWord((int)((unsigned)reg2->asInt() + immediate));   
}

void Executor::_addu(Register *reg1,Register *reg2,Register *reg3) {
    _add(reg1, reg2, reg3);
}

void Executor::_subu(Register *reg1,Register *reg2,Register *reg3) {
    _sub(reg1, reg2, reg3);
}

void Executor::_divu(Register *reg1,Register *reg2) {  
    registers.LO.setWord((int)((unsigned)reg1->asInt() / (unsigned)reg2->asInt()));   
    registers.HI.setWord((int)((unsigned)reg1->asInt() % (unsigned)reg2->asInt()));
}

void Executor::_jr(Register *reg)  {
    _jump(reg->asInt());
}

void Executor::_jalr(Register *reg)  {
    _jal(reg->asInt());
}

void Executor::_lui(Register *reg, int immediate) {
    reg->setWord(immediate << 16);
}

void Executor::_sll(Register *reg1, Register *reg2, int immediate) {
    if (immediate < 0) _srl(reg1, reg2, -immediate);
    else reg1->setWord(reg2->asInt() << immediate);
}

void Executor::_sllv(Register *reg1, Register *reg2, Register *reg3) {
    _sll(reg1, reg2, reg3->asInt());
}

void Executor::_sra(Register *reg1, Register *reg2, int immediate) {
    reg1->setWord(reg2->asInt() >> immediate);
}

void Executor::_srl(Register *reg1, Register *reg2, int immediate) {
    if (immediate == 0) return;
    int zeros = 0b01111111111111111111111111111111 >> (immediate-1);     
    reg1->setWord(zeros & (reg2->asInt() >> immediate));
}

void Executor::_noop()  {}
void Executor::_nop()  {}

void Executor::_srlv(Register *reg1, Register *reg2, Register *reg3) {
    _srl(reg1, reg2, reg3->asInt());
}


void Executor::_move(Register *reg1, Register *reg2)  {
    _or(reg1, reg2, (Register*)&registers.ZERO);
}

void Executor::_clear(Register *reg) {
    _or(reg, (Register*)&registers.ZERO , (Register*)&registers.ZERO);
}

void Executor::_li(Register *reg1, short immediate) {
    _ori(reg1, (Register*)&registers.ZERO, (int)immediate);
}

void Executor::_li(Register *reg1, int immediate) {
    _lui(reg1, immediate >> 16);
    _ori(reg1, reg1, immediate & 0x0000FFFF); 
}

void Executor::_la(Register *reg1, int address) {
    _li(reg1, address);
}

void Executor::_nor(Register *reg1, Register *reg2,Register *reg3) {
    reg1->setWord(~(reg2->asInt() | reg3->asInt()));
}

void Executor::_not(Register *reg1, Register *reg2) {
    _nor(reg1, reg2, (Register*)&registers.ZERO);
}


//TODO: tirar foda
//Área FODA do syscall
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void Executor::_syscall()  {
    int operationCode = registers.V0.asInt();
    if (operationCode == 1) {
        std::cout << registers.A0.asInt();
    }
    else if (operationCode == 2){
        std::cout << "WARNING: Syscall not implemented" << std::endl;
    }
    else if (operationCode == 3){
        std::cout << "WARNING: Syscall not implemented" << std::endl;        
    }
    else if (operationCode == 4){
        //TODO: permitir acesso a outras regiões que não a stack
        int stringAddress = registers.A0.asInt();
        char c;
        while ((c = stack.getByteAt(stringAddress++)) != '\0') std::cout << c;
        std::cout << std::endl;
    }
    else if (operationCode == 5){
        int temp;
        std::cin >> temp;
        registers.V0.setWord(temp);
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
        for (int i = 0; i < registers.A1.asInt(); i++) {
            std::cin >> c;
            stack.setBytes(registers.A0.asInt() + offset++, c);
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
        std::cout << registers.A0.getWord().asByteArray().getByteAt(3);
    }
    else if (operationCode == 12){
        std::cout << "WARNING: Syscall not implemented" << std::endl;                
    }
    else std::cout << "WARNING: Syscall out of range" << std::endl;
}

