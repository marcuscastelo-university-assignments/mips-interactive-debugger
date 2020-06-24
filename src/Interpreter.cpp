#include "Interpreter.h"

#include <functional>
#include <vector>
#include "string_utils.h"


Interpreter::Interpreter(Executor *parentExecutor) {
    this->parentExecutor = parentExecutor;
}

Interpreter::~Interpreter()
{
}

Instruction *Interpreter::interpretInstruction(std::string instruction) {
    std::vector<std::string> instruction_parts = split(instruction);
    std::vector<Register*> registers;
    std::vector<int> integers;

    for (unsigned i = 1; i < instruction_parts.size(); i++) {
        if (isInteger(instruction_parts[i])) {
            integers.push_back(stoi(instruction_parts[i]));
        } else {
            parentExecutor->getRegisters()->getRegisterByName(instruction_parts[i])
            registers.push_back();
        }
    }
    
    //TODO: arrumar beqi, div2, div3, etc

         if (instruction_parts[0] == "lw") return (new Instruction(instruction, parentExecutor, &Executor::_lw))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sw") return (new Instruction(instruction, parentExecutor, &Executor::_sw))->add(registers)->add(integers);
    else if (instruction_parts[0] == "lb") return (new Instruction(instruction, parentExecutor, &Executor::_lb))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sb") return (new Instruction(instruction, parentExecutor, &Executor::_sb))->add(registers)->add(integers);
    else if (instruction_parts[0] == "beq") return (new Instruction(instruction, parentExecutor, &Executor::_beq))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bgez") return (new Instruction(instruction, parentExecutor, &Executor::_bgez))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bgezal") return (new Instruction(instruction, parentExecutor, &Executor::_bgezal))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bgtz") return (new Instruction(instruction, parentExecutor, &Executor::_bgtz))->add(registers)->add(integers);
    else if (instruction_parts[0] == "blez") return (new Instruction(instruction, parentExecutor, &Executor::_blez))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bltz") return (new Instruction(instruction, parentExecutor, &Executor::_bltz))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bltzal") return (new Instruction(instruction, parentExecutor, &Executor::_bltzal))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bne") return (new Instruction(instruction, parentExecutor, &Executor::_bne))->add(registers)->add(integers);
    else if (instruction_parts[0] == "b") return (new Instruction(instruction, parentExecutor, &Executor::_b))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bal") return (new Instruction(instruction, parentExecutor, &Executor::_bal))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bgt") return (new Instruction(instruction, parentExecutor, &Executor::_bgt))->add(registers)->add(integers);
    else if (instruction_parts[0] == "blt") return (new Instruction(instruction, parentExecutor, &Executor::_blt))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bge") return (new Instruction(instruction, parentExecutor, &Executor::_bge))->add(registers)->add(integers);
    else if (instruction_parts[0] == "ble") return (new Instruction(instruction, parentExecutor, &Executor::_ble))->add(registers)->add(integers);
    else if (instruction_parts[0] == "bgtu") return (new Instruction(instruction, parentExecutor, &Executor::_bgtu))->add(registers)->add(integers);
    else if (instruction_parts[0] == "beqz") return (new Instruction(instruction, parentExecutor, &Executor::_beqz))->add(registers)->add(integers);
    else if (instruction_parts[0] == "beqi") return (new Instruction(instruction, parentExecutor, &Executor::_beqi))->add(registers)->add(integers);
    else if (instruction_parts[0] == "jump") return (new Instruction(instruction, parentExecutor, &Executor::_jump))->add(registers)->add(integers);
    else if (instruction_parts[0] == "add") return (new Instruction(instruction, parentExecutor, &Executor::_add))->add(registers)->add(integers);
    else if (instruction_parts[0] == "addi") return (new Instruction(instruction, parentExecutor, &Executor::_addi))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sub") return (new Instruction(instruction, parentExecutor, &Executor::_sub))->add(registers)->add(integers);
    else if (instruction_parts[0] == "mult") return (new Instruction(instruction, parentExecutor, &Executor::_mult))->add(registers)->add(integers);
    else if (instruction_parts[0] == "mflo") return (new Instruction(instruction, parentExecutor, &Executor::_mflo))->add(registers)->add(integers);
    else if (instruction_parts[0] == "mfhi") return (new Instruction(instruction, parentExecutor, &Executor::_mfhi))->add(registers)->add(integers);
    else if (instruction_parts[0] == "mul") return (new Instruction(instruction, parentExecutor, &Executor::_mul))->add(registers)->add(integers);
    else if (instruction_parts[0] == "div2") return (new Instruction(instruction, parentExecutor, &Executor::_div2))->add(registers)->add(integers);
    else if (instruction_parts[0] == "div3") return (new Instruction(instruction, parentExecutor, &Executor::_div3))->add(registers)->add(integers);
    else if (instruction_parts[0] == "rem") return (new Instruction(instruction, parentExecutor, &Executor::_rem))->add(registers)->add(integers);
    else if (instruction_parts[0] == "and") return (new Instruction(instruction, parentExecutor, &Executor::_and))->add(registers)->add(integers);
    else if (instruction_parts[0] == "or") return (new Instruction(instruction, parentExecutor, &Executor::_or))->add(registers)->add(integers);
    else if (instruction_parts[0] == "xor") return (new Instruction(instruction, parentExecutor, &Executor::_xor))->add(registers)->add(integers);
    else if (instruction_parts[0] == "andi") return (new Instruction(instruction, parentExecutor, &Executor::_andi))->add(registers)->add(integers);
    else if (instruction_parts[0] == "ori") return (new Instruction(instruction, parentExecutor, &Executor::_ori))->add(registers)->add(integers);
    else if (instruction_parts[0] == "xori") return (new Instruction(instruction, parentExecutor, &Executor::_xori))->add(registers)->add(integers);
    else if (instruction_parts[0] == "slt") return (new Instruction(instruction, parentExecutor, &Executor::_slt))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sltu") return (new Instruction(instruction, parentExecutor, &Executor::_sltu))->add(registers)->add(integers);
    else if (instruction_parts[0] == "slti") return (new Instruction(instruction, parentExecutor, &Executor::_slti))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sltiu") return (new Instruction(instruction, parentExecutor, &Executor::_sltiu))->add(registers)->add(integers);
    else if (instruction_parts[0] == "jal") return (new Instruction(instruction, parentExecutor, &Executor::_jal))->add(registers)->add(integers);
    else if (instruction_parts[0] == "addiu") return (new Instruction(instruction, parentExecutor, &Executor::_addiu))->add(registers)->add(integers);
    else if (instruction_parts[0] == "addu") return (new Instruction(instruction, parentExecutor, &Executor::_addu))->add(registers)->add(integers);
    else if (instruction_parts[0] == "subu") return (new Instruction(instruction, parentExecutor, &Executor::_subu))->add(registers)->add(integers);
    else if (instruction_parts[0] == "divu") return (new Instruction(instruction, parentExecutor, &Executor::_divu))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sllv") return (new Instruction(instruction, parentExecutor, &Executor::_sllv))->add(registers)->add(integers);
    else if (instruction_parts[0] == "jr") return (new Instruction(instruction, parentExecutor, &Executor::_jr))->add(registers)->add(integers);
    else if (instruction_parts[0] == "jalr") return (new Instruction(instruction, parentExecutor, &Executor::_jalr))->add(registers)->add(integers);
    else if (instruction_parts[0] == "lui") return (new Instruction(instruction, parentExecutor, &Executor::_lui))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sll") return (new Instruction(instruction, parentExecutor, &Executor::_sll))->add(registers)->add(integers);
    else if (instruction_parts[0] == "noop") return (new Instruction(instruction, parentExecutor, &Executor::_noop))->add(registers)->add(integers);
    else if (instruction_parts[0] == "nop") return (new Instruction(instruction, parentExecutor, &Executor::_nop))->add(registers)->add(integers);
    else if (instruction_parts[0] == "sra") return (new Instruction(instruction, parentExecutor, &Executor::_sra))->add(registers)->add(integers);
    else if (instruction_parts[0] == "srl") return (new Instruction(instruction, parentExecutor, &Executor::_srl))->add(registers)->add(integers);
    else if (instruction_parts[0] == "syscall") return (new Instruction(instruction, parentExecutor, &Executor::syscall))->add(registers)->add(integers);
    else if (instruction_parts[0] == "move") return (new Instruction(instruction, parentExecutor, &Executor::_move))->add(registers)->add(integers);
    else if (instruction_parts[0] == "srlv") return (new Instruction(instruction, parentExecutor, &Executor::_srlv))->add(registers)->add(integers);
    else if (instruction_parts[0] == "clear") return (new Instruction(instruction, parentExecutor, &Executor::_clear))->add(registers)->add(integers);
    else if (instruction_parts[0] == "li") return (new Instruction(instruction, parentExecutor, &Executor::_li))->add(registers)->add(integers);
    //TODO: fazer li pra short
    // else if (instruction_parts[0] == "li") return (new Instruction(instruction, parentExecutor, &Executor::_li))->add(registers)->add(integers);
    else if (instruction_parts[0] == "la") return (new Instruction(instruction, parentExecutor, &Executor::_la))->add(registers)->add(integers);
    else if (instruction_parts[0] == "nor") return (new Instruction(instruction, parentExecutor, &Executor::_nor))->add(registers)->add(integers);
    else if (instruction_parts[0] == "not") return (new Instruction(instruction, parentExecutor, &Executor::_not))->add(registers)->add(integers);
    return (new Instruction(nullptr))->add(registers)->add(integers);
}