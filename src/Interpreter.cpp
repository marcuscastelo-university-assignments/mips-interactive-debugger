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

    for (unsigned i = 0; i < instruction_parts.size(); i++) {
        if (isInteger(instruction_parts[i])) {
            integers.push_back(stoi(instruction_parts[i]));
        } else {
            registers.push_back(parentExecutor->getRegisters()->getRegisterByName(instruction_parts[i]));
        }
    }
    
    //TODO: arrumar beqi, div2, div3, etc

         if (instruction_parts[1] == "lw") return (new Instruction(instruction, parentExecutor, &Executor::_lw))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sw") return (new Instruction(instruction, parentExecutor, &Executor::_sw))->add(registers)->add(integers);
    else if (instruction_parts[1] == "lb") return (new Instruction(instruction, parentExecutor, &Executor::_lb))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sb") return (new Instruction(instruction, parentExecutor, &Executor::_sb))->add(registers)->add(integers);
    else if (instruction_parts[1] == "beq") return (new Instruction(instruction, parentExecutor, &Executor::_beq))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bgez") return (new Instruction(instruction, parentExecutor, &Executor::_bgez))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bgezal") return (new Instruction(instruction, parentExecutor, &Executor::_bgezal))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bgtz") return (new Instruction(instruction, parentExecutor, &Executor::_bgtz))->add(registers)->add(integers);
    else if (instruction_parts[1] == "blez") return (new Instruction(instruction, parentExecutor, &Executor::_blez))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bltz") return (new Instruction(instruction, parentExecutor, &Executor::_bltz))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bltzal") return (new Instruction(instruction, parentExecutor, &Executor::_bltzal))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bne") return (new Instruction(instruction, parentExecutor, &Executor::_bne))->add(registers)->add(integers);
    else if (instruction_parts[1] == "b") return (new Instruction(instruction, parentExecutor, &Executor::_b))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bal") return (new Instruction(instruction, parentExecutor, &Executor::_bal))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bgt") return (new Instruction(instruction, parentExecutor, &Executor::_bgt))->add(registers)->add(integers);
    else if (instruction_parts[1] == "blt") return (new Instruction(instruction, parentExecutor, &Executor::_blt))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bge") return (new Instruction(instruction, parentExecutor, &Executor::_bge))->add(registers)->add(integers);
    else if (instruction_parts[1] == "ble") return (new Instruction(instruction, parentExecutor, &Executor::_ble))->add(registers)->add(integers);
    else if (instruction_parts[1] == "bgtu") return (new Instruction(instruction, parentExecutor, &Executor::_bgtu))->add(registers)->add(integers);
    else if (instruction_parts[1] == "beqz") return (new Instruction(instruction, parentExecutor, &Executor::_beqz))->add(registers)->add(integers);
    else if (instruction_parts[1] == "beqi") return (new Instruction(instruction, parentExecutor, &Executor::_beqi))->add(registers)->add(integers);
    else if (instruction_parts[1] == "jump") return (new Instruction(instruction, parentExecutor, &Executor::_jump))->add(registers)->add(integers);
    else if (instruction_parts[1] == "add") return (new Instruction(instruction, parentExecutor, &Executor::_add))->add(registers)->add(integers);
    else if (instruction_parts[1] == "addi") return (new Instruction(instruction, parentExecutor, &Executor::_addi))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sub") return (new Instruction(instruction, parentExecutor, &Executor::_sub))->add(registers)->add(integers);
    else if (instruction_parts[1] == "mult") return (new Instruction(instruction, parentExecutor, &Executor::_mult))->add(registers)->add(integers);
    else if (instruction_parts[1] == "mflo") return (new Instruction(instruction, parentExecutor, &Executor::_mflo))->add(registers)->add(integers);
    else if (instruction_parts[1] == "mfhi") return (new Instruction(instruction, parentExecutor, &Executor::_mfhi))->add(registers)->add(integers);
    else if (instruction_parts[1] == "mul") return (new Instruction(instruction, parentExecutor, &Executor::_mul))->add(registers)->add(integers);
    else if (instruction_parts[1] == "div2") return (new Instruction(instruction, parentExecutor, &Executor::_div2))->add(registers)->add(integers);
    else if (instruction_parts[1] == "div3") return (new Instruction(instruction, parentExecutor, &Executor::_div3))->add(registers)->add(integers);
    else if (instruction_parts[1] == "rem") return (new Instruction(instruction, parentExecutor, &Executor::_rem))->add(registers)->add(integers);
    else if (instruction_parts[1] == "and") return (new Instruction(instruction, parentExecutor, &Executor::_and))->add(registers)->add(integers);
    else if (instruction_parts[1] == "or") return (new Instruction(instruction, parentExecutor, &Executor::_or))->add(registers)->add(integers);
    else if (instruction_parts[1] == "xor") return (new Instruction(instruction, parentExecutor, &Executor::_xor))->add(registers)->add(integers);
    else if (instruction_parts[1] == "andi") return (new Instruction(instruction, parentExecutor, &Executor::_andi))->add(registers)->add(integers);
    else if (instruction_parts[1] == "ori") return (new Instruction(instruction, parentExecutor, &Executor::_ori))->add(registers)->add(integers);
    else if (instruction_parts[1] == "xori") return (new Instruction(instruction, parentExecutor, &Executor::_xori))->add(registers)->add(integers);
    else if (instruction_parts[1] == "slt") return (new Instruction(instruction, parentExecutor, &Executor::_slt))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sltu") return (new Instruction(instruction, parentExecutor, &Executor::_sltu))->add(registers)->add(integers);
    else if (instruction_parts[1] == "slti") return (new Instruction(instruction, parentExecutor, &Executor::_slti))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sltiu") return (new Instruction(instruction, parentExecutor, &Executor::_sltiu))->add(registers)->add(integers);
    else if (instruction_parts[1] == "jal") return (new Instruction(instruction, parentExecutor, &Executor::_jal))->add(registers)->add(integers);
    else if (instruction_parts[1] == "addiu") return (new Instruction(instruction, parentExecutor, &Executor::_addiu))->add(registers)->add(integers);
    else if (instruction_parts[1] == "addu") return (new Instruction(instruction, parentExecutor, &Executor::_addu))->add(registers)->add(integers);
    else if (instruction_parts[1] == "subu") return (new Instruction(instruction, parentExecutor, &Executor::_subu))->add(registers)->add(integers);
    else if (instruction_parts[1] == "divu") return (new Instruction(instruction, parentExecutor, &Executor::_divu))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sllv") return (new Instruction(instruction, parentExecutor, &Executor::_sllv))->add(registers)->add(integers);
    else if (instruction_parts[1] == "jr") return (new Instruction(instruction, parentExecutor, &Executor::_jr))->add(registers)->add(integers);
    else if (instruction_parts[1] == "jalr") return (new Instruction(instruction, parentExecutor, &Executor::_jalr))->add(registers)->add(integers);
    else if (instruction_parts[1] == "lui") return (new Instruction(instruction, parentExecutor, &Executor::_lui))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sll") return (new Instruction(instruction, parentExecutor, &Executor::_sll))->add(registers)->add(integers);
    else if (instruction_parts[1] == "noop") return (new Instruction(instruction, parentExecutor, &Executor::_noop))->add(registers)->add(integers);
    else if (instruction_parts[1] == "nop") return (new Instruction(instruction, parentExecutor, &Executor::_nop))->add(registers)->add(integers);
    else if (instruction_parts[1] == "sra") return (new Instruction(instruction, parentExecutor, &Executor::_sra))->add(registers)->add(integers);
    else if (instruction_parts[1] == "srl") return (new Instruction(instruction, parentExecutor, &Executor::_srl))->add(registers)->add(integers);
    else if (instruction_parts[1] == "syscall") return (new Instruction(instruction, parentExecutor, &Executor::syscall))->add(registers)->add(integers);
    else if (instruction_parts[1] == "move") return (new Instruction(instruction, parentExecutor, &Executor::_move))->add(registers)->add(integers);
    else if (instruction_parts[1] == "srlv") return (new Instruction(instruction, parentExecutor, &Executor::_srlv))->add(registers)->add(integers);
    else if (instruction_parts[1] == "clear") return (new Instruction(instruction, parentExecutor, &Executor::_clear))->add(registers)->add(integers);
    else if (instruction_parts[1] == "li") return (new Instruction(instruction, parentExecutor, &Executor::_li))->add(registers)->add(integers);
    else if (instruction_parts[1] == "li") return (new Instruction(instruction, parentExecutor, &Executor::_li))->add(registers)->add(integers);
    else if (instruction_parts[1] == "la") return (new Instruction(instruction, parentExecutor, &Executor::_la))->add(registers)->add(integers);
    else if (instruction_parts[1] == "nor") return (new Instruction(instruction, parentExecutor, &Executor::_nor))->add(registers)->add(integers);
    else if (instruction_parts[1] == "not") return (new Instruction(instruction, parentExecutor, &Executor::_not))->add(registers)->add(integers);
    return (new Instruction(nullptr))->add(registers)->add(integers);
}