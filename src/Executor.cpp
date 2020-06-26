#include "Executor.h"
#include "Instruction.h"

#include "string_utils.h"
#include <iostream>
#include <stdexcept>

//TODO: implementar comportamentos esquisitos de registradores temporarios (j label, etc) (e outros obscutos)
Executor::Executor(Program &program)
: interpreter(new Interpreter(this)), program(program), stack(STACK_SIZE)
{
    registers.SP.setValue(stack.getSize());
}

Executor::~Executor() {
    delete interpreter;
}

Instruction *Executor::executeInstructionStr(const std::string& instructionStr) const {
    printf("%s\n", instructionStr.c_str());
    Instruction *interpretedInstruction = interpreter->interpretInstruction(instructionStr);

    if (interpretedInstruction->validate()) {
        try {
            interpretedInstruction->execute((Executor*)this);
        } catch (const std::exception& e) {
            fprintf(stderr, "%s\n", e.what());
            return NULL;
        }
        #include <iostream>
        using namespace std;
        ByteArray b = stack.getBytes();
        for (int i = b.getSize()-40; i < b.getSize(); i+=4) {
            Word wuw(stack.getBytes(i, 4));
            // cout << wuw.asInt() << endl;
        }

        int advanceOffset = interpretedInstruction->getAdvancePcType();
        ((Register&)registers.PC).setValue(registers.PC.asInt() + advanceOffset);
    }
    

    return interpretedInstruction;
}

const Program &Executor::getProgram() const {
    return program;
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

void Executor::_label(void) { }

void Executor::_invalid(nullptr_t _) { }

//TODO: Questão da stack
void Executor::_lw(Register *reg1, Register *reg2, int offset)  {
    int stackAddress = reg2->asInt() + offset;
    reg1->setValue(stack.getBytes(stackAddress, 4));
}

void Executor::_sw(Register *reg1, Register *reg2, int offset)  {
    int stackAddress = reg2->asInt() + offset;
    stack.setBytes(stackAddress, reg1->asByteArray() );
}

void Executor::_lb(Register *reg1, Register *reg2,int offset)  {
    int stackAddress = reg2->asInt() + offset;
    Word newWord = reg1->asInt();
    newWord.setByteAt(3, stack.getByteAt(stackAddress));
    reg1->setValue(newWord);   
}

void Executor::_sb(Register *reg1, Register *reg2,int offset) {
    int stackAddress = reg2->asInt() + offset;
    stack.setByteAt(stackAddress, reg1->asByteArray().getByteAt(3));
}


//TODO: retificar os ATs
void Executor::bnei(Register *reg1, int immediate, int jumpAddress) {
    _ori(&registers.AT,&registers.ZERO,immediate);
    bne(reg1,&registers.AT,jumpAddress);
}

void Executor::bne(Register *reg1, Register *reg2, int jumpAddress) {
    if(reg1->asInt() != reg2->asInt()) _j(jumpAddress);    
}

void Executor::_bne(Register *reg1, Register *reg2, int immediate, int jumpAddress) {
    if(reg2 == NULL) bnei(reg1,immediate,jumpAddress);
    else bne(reg1,reg2,jumpAddress);
}

void Executor::_beqi(Register *reg1, int immediate, int jumpAddress) {
    _ori(&registers.AT,&registers.ZERO,immediate);
    beq(reg1,&registers.AT,jumpAddress);
}

void Executor::beq(Register *reg1, Register *reg2, int jumpAddress) {
    if(reg1->asInt() == reg2->asInt()) _j(jumpAddress);    
}

void Executor::_beq(Register *reg1, Register *reg2, int immediate, int jumpAddress) {
    if(reg2 == NULL) _beqi(reg1,immediate,jumpAddress);
    else beq(reg1,reg2,jumpAddress);
}

void Executor::_bgez(Register *reg, int jumpAddress) {
    if(reg->asInt() >= 0) _j(jumpAddress);    
}

void Executor::_bgezal(Register *reg, int jumpAddress) {
    if(reg->asInt() >= 0) _jal(jumpAddress);    
    
}

void Executor::_bgtz(Register *reg, int jumpAddress) {
    if(reg->asInt() > 0) _j(jumpAddress);    
}

void Executor::_blez(Register *reg, int jumpAddress) {
    if(reg->asInt() <= 0) _j(jumpAddress);    
}

void Executor::_bltz(Register *reg, int jumpAddress) {
    if(reg->asInt() < 0) _j(jumpAddress);    
}

void Executor::_bltzal(Register *reg, int jumpAddress) {
    if(reg->asInt() < 0) _jal(jumpAddress);    
}

void Executor::_b(int jumpAddress) {
    beq((Register*)&registers.ZERO, (Register*)&registers.ZERO, jumpAddress);
}

void Executor::_bal(int jumpAddress) {
    _bgezal((Register*)&registers.ZERO, jumpAddress);
}

void Executor::_bgt(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg2,reg1);
    bne((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}


void Executor::_blt(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg1, reg2);
    bne((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_bge(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg1, reg2);
    beq((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_ble(Register *reg1, Register *reg2, int jumpAddress) {
    _slt((Register*)&registers.AT, reg2, reg1);
    beq((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_bgtu(Register *reg1, Register *reg2, int jumpAddress) {
    _sltu((Register*)&registers.AT, reg2, reg1);
    bne((Register*)&registers.AT, (Register*)&registers.ZERO, jumpAddress);    
}

void Executor::_beqz(Register *reg, int jumpAddress) {
    beq(reg, (Register*)&registers.ZERO, jumpAddress);    
}

//TODO: Questão do jump e tamanho da stack
    //TODO: PEGAR O TAMANHO DO PROGRAMA
void Executor::_j(int jumpAddress) {
    if(jumpAddress < -4 || jumpAddress >= 4 * (int) program.getInstructionsVectorSize()) throw std::out_of_range("ERROR: Jump address out of range.\n");
    else registers.PC.setValue(jumpAddress - 4);
}

void Executor::_add(Register *reg1,Register *reg2,Register *reg3) {
    reg1->setValue(reg2->asInt() + reg3->asInt());   
}

void Executor::_addi(Register *reg1, Register *reg2, int immediate) {
    reg1->setValue(reg2->asInt() + immediate);   
}

void Executor::_sub(Register *reg1,Register *reg2,Register *reg3) {
    reg1->setValue(reg2->asInt() - reg3->asInt());   
}

void Executor::_mult(Register *reg1,Register *reg2) {
    registers.LO.setValue(reg1->asInt() * reg2->asInt());   
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

void Executor::div2(Register *reg1,Register *reg2) {  
    registers.LO.setValue(reg1->asInt() / reg2->asInt());   
    registers.HI.setValue(reg1->asInt() % reg2->asInt());
}

void Executor::div3(Register *reg1,Register *reg2,Register *reg3) {  
    div2(reg2,reg3);
    _mflo(reg1);
}

void Executor::_div(Register *reg1,Register *reg2,Register *reg3){
    if(reg3 == NULL) div2(reg1, reg2);
    else div3(reg1, reg2, reg3);
}

void Executor::_rem(Register *reg1,Register *reg2,Register *reg3) {  
    div2(reg2,reg3);
    _mfhi(reg1);
}

void Executor::_and(Register *reg1, Register *reg2, Register *reg3)  {
    reg1->setValue(reg2->asInt() & reg3->asInt());
}

void Executor::_or(Register *reg1, Register *reg2, Register *reg3)  {
    reg1->setValue(reg2->asInt() | reg3->asInt());
}

void Executor::_xor(Register *reg1, Register *reg2, Register *reg3)  {
    reg1->setValue(reg2->asInt() ^ reg3->asInt());
}

void Executor::_andi(Register *reg1, Register *reg2, int immediate)  {
    reg1->setValue(reg2->asInt() & immediate);
}

void Executor::_ori(Register *reg1, Register *reg2, int immediate)  {
    reg1->setValue(reg2->asInt() | immediate);
}

void Executor::_xori(Register *reg1, Register *reg2, int immediate)  {
    reg1->setValue(reg2->asInt() ^ immediate);
}

void Executor::_slt(Register *reg1, Register *reg2, Register *reg3) {
    if(reg2->asInt() < reg3->asInt()) reg1->setValue(1);
    else reg1->setValue(0);
}

void Executor::_sltu(Register *reg1, Register *reg2, Register *reg3) {
    if((unsigned)reg2->asInt() < (unsigned)reg3->asInt()) reg1->setValue(1); 
    else reg1->setValue(0);
}

void Executor::_slti(Register *reg1, Register *reg2, int immediate) {
    if(reg2->asInt() < immediate) reg1->setValue(1);
    else reg1->setValue(0);
}

void Executor::_sltiu(Register *reg1, Register *reg2, unsigned immediate) {
    if((unsigned)reg2->asInt() < immediate) reg1->setValue(1);
    else reg1->setValue(0);
}

void Executor::_jal(int jumpAddress) {
    registers.RA.setValue(registers.PC.asInt() + 4);
    _j(jumpAddress);
}

void Executor::_addiu(Register *reg1, Register *reg2, unsigned int immediate) {
    reg1->setValue((int)((unsigned)reg2->asInt() + immediate));   
}

void Executor::_addu(Register *reg1,Register *reg2,Register *reg3) {
    _add(reg1, reg2, reg3);
}

void Executor::_subu(Register *reg1,Register *reg2,Register *reg3) {
    _sub(reg1, reg2, reg3);
}

void Executor::_divu(Register *reg1,Register *reg2) {  
    registers.LO.setValue((int)((unsigned)reg1->asInt() / (unsigned)reg2->asInt()));   
    registers.HI.setValue((int)((unsigned)reg1->asInt() % (unsigned)reg2->asInt()));
}

void Executor::_jr(Register *reg)  {
    _j(reg->asInt());
}

void Executor::_jalr(Register *reg)  {
    _jal(reg->asInt());
}

void Executor::_lui(Register *reg, int immediate) {
    reg->setValue(immediate << 16);
}

void Executor::_sll(Register *reg1, Register *reg2, int immediate) {
    if (immediate < 0) _srl(reg1, reg2, -immediate);
    else reg1->setValue(reg2->asInt() << immediate);
}

void Executor::_sllv(Register *reg1, Register *reg2, Register *reg3) {
    _sll(reg1, reg2, reg3->asInt());
}

void Executor::_sra(Register *reg1, Register *reg2, int immediate) {
    reg1->setValue(reg2->asInt() >> immediate);
}

void Executor::_srl(Register *reg1, Register *reg2, int immediate) {
    if (immediate == 0) return;
    int zeros = 0b01111111111111111111111111111111 >> (immediate-1);     
    reg1->setValue(zeros & (reg2->asInt() >> immediate));
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
    reg1->setValue(~(reg2->asInt() | reg3->asInt()));
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
        std::cout << registers.A0.asInt() << std::endl;
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
        std::string line = getLine();
        int linei = stoi(line);
        registers.V0.setValue(linei);
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
        std::cout << registers.A0.asByteArray().getByteAt(3);
    }
    else if (operationCode == 12){
        std::cout << "WARNING: Syscall not implemented" << std::endl;                
    }
    else std::cout << "WARNING: Syscall out of range" << std::endl;
}

