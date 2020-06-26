#ifndef __INSTRUCTIONS__H__
#define __INSTRUCTIONS__H__

#include "Instruction.h"
#include <map>
#include <string>

class Instruction;

static const std::map<std::string,Instruction*> instructionByName = {
            { std::string("lw"), (new Instruction("lw"))->setExecutionFunction(&Executor::_lw) },
            { std::string("sw"), (new Instruction("sw"))->setExecutionFunction(&Executor::_sw) },
            { std::string("lb"), (new Instruction("lb"))->setExecutionFunction(&Executor::_lb) },
            { std::string("sb"), (new Instruction("sb"))->setExecutionFunction(&Executor::_sb) },
            { std::string("beq"), (new Instruction("beq"))->setExecutionFunction(&Executor::_beq)->setOverloadedIntegerCount(2)->setOverloadedRegisterCount(1)->setSupposedIntegerCount(1) },
            { std::string("bgez"), (new Instruction("bgez"))->setExecutionFunction(&Executor::_bgez) },
            { std::string("bgezal"), (new Instruction("bgezal"))->setExecutionFunction(&Executor::_bgezal) },
            { std::string("bgtz"), (new Instruction("bgtz"))->setExecutionFunction(&Executor::_bgtz) },
            { std::string("blez"), (new Instruction("blez"))->setExecutionFunction(&Executor::_blez) },
            { std::string("bltz"), (new Instruction("bltz"))->setExecutionFunction(&Executor::_bltz) },
            { std::string("bltzal"), (new Instruction("bltzal"))->setExecutionFunction(&Executor::_bltzal) },
            { std::string("bne"), (new Instruction("bne"))->setExecutionFunction(&Executor::_bne)->setOverloadedIntegerCount(2)->setOverloadedRegisterCount(1)->setSupposedIntegerCount(1) },
            { std::string("b"), (new Instruction("b"))->setExecutionFunction(&Executor::_b) },
            { std::string("bal"), (new Instruction("bal"))->setExecutionFunction(&Executor::_bal) },
            { std::string("bgt"), (new Instruction("bgt"))->setExecutionFunction(&Executor::_bgt) },
            { std::string("blt"), (new Instruction("blt"))->setExecutionFunction(&Executor::_blt) },
            { std::string("bge"), (new Instruction("bge"))->setExecutionFunction(&Executor::_bge) },
            { std::string("ble"), (new Instruction("ble"))->setExecutionFunction(&Executor::_ble) },
            { std::string("bgtu"), (new Instruction("bgtu"))->setExecutionFunction(&Executor::_bgtu) },
            { std::string("beqz"), (new Instruction("beqz"))->setExecutionFunction(&Executor::_beqz) },
            { std::string("j"), (new Instruction("j"))->setExecutionFunction(&Executor::_j) },
            { std::string("add"), (new Instruction("add"))->setExecutionFunction(&Executor::_add) },
            { std::string("addi"), (new Instruction("addi"))->setExecutionFunction(&Executor::_addi) },
            { std::string("sub"), (new Instruction("sub"))->setExecutionFunction(&Executor::_sub)->setOverloadedRegisterCount(2)->setOverloadedIntegerCount(1) },
            { std::string("subi"), (new Instruction("subi"))->setExecutionFunction(&Executor::_subi) },
            { std::string("mult"), (new Instruction("mult"))->setExecutionFunction(&Executor::_mult) },
            { std::string("mflo"), (new Instruction("mflo"))->setExecutionFunction(&Executor::_mflo) },
            { std::string("mfhi"), (new Instruction("mfhi"))->setExecutionFunction(&Executor::_mfhi) },
            { std::string("mul"), (new Instruction("mul"))->setExecutionFunction(&Executor::_mul) },
            { std::string("div"), (new Instruction("div"))->setExecutionFunction(&Executor::_div)->setOverloadedRegisterCount(2) },
            { std::string("rem"), (new Instruction("rem"))->setExecutionFunction(&Executor::_rem) },
            { std::string("and"), (new Instruction("and"))->setExecutionFunction(&Executor::_and) },
            { std::string("or"), (new Instruction("or"))->setExecutionFunction(&Executor::_or) },
            { std::string("xor"), (new Instruction("xor"))->setExecutionFunction(&Executor::_xor) },
            { std::string("andi"), (new Instruction("andi"))->setExecutionFunction(&Executor::_andi) },
            { std::string("ori"), (new Instruction("ori"))->setExecutionFunction(&Executor::_ori) },
            { std::string("xori"), (new Instruction("xori"))->setExecutionFunction(&Executor::_xori) },
            { std::string("slt"), (new Instruction("slt"))->setExecutionFunction(&Executor::_slt) },
            { std::string("sltu"), (new Instruction("sltu"))->setExecutionFunction(&Executor::_sltu) },
            { std::string("slti"), (new Instruction("slti"))->setExecutionFunction(&Executor::_slti) },
            { std::string("sltiu"), (new Instruction("sltiu"))->setExecutionFunction(&Executor::_sltiu) },
            { std::string("jal"), (new Instruction("jal"))->setExecutionFunction(&Executor::_jal) },
            { std::string("addiu"), (new Instruction("addiu"))->setExecutionFunction(&Executor::_addiu) },
            { std::string("addu"), (new Instruction("addu"))->setExecutionFunction(&Executor::_addu) },
            { std::string("subu"), (new Instruction("subu"))->setExecutionFunction(&Executor::_subu) },
            { std::string("divu"), (new Instruction("divu"))->setExecutionFunction(&Executor::_divu) },
            { std::string("sllv"), (new Instruction("sllv"))->setExecutionFunction(&Executor::_sllv) },
            { std::string("jr"), (new Instruction("jr"))->setExecutionFunction(&Executor::_jr) },
            { std::string("jalr"), (new Instruction("jalr"))->setExecutionFunction(&Executor::_jalr) },
            { std::string("lui"), (new Instruction("lui"))->setExecutionFunction(&Executor::_lui) },
            { std::string("sll"), (new Instruction("sll"))->setExecutionFunction(&Executor::_sll) },
            { std::string("noop"), (new Instruction("noop"))->setExecutionFunction(&Executor::_noop) },
            { std::string("nop"), (new Instruction("nop"))->setExecutionFunction(&Executor::_nop) },
            { std::string("sra"), (new Instruction("sra"))->setExecutionFunction(&Executor::_sra) },
            { std::string("srl"), (new Instruction("srl"))->setExecutionFunction(&Executor::_srl) },
            { std::string("syscall"), (new Instruction("syscall"))->setExecutionFunction(&Executor::_syscall) },
            { std::string("move"), (new Instruction("move"))->setExecutionFunction(&Executor::_move) },
            { std::string("srlv"), (new Instruction("srlv"))->setExecutionFunction(&Executor::_srlv) },
            { std::string("clear"), (new Instruction("clear"))->setExecutionFunction(&Executor::_clear) },
            { std::string("li"), (new Instruction("li"))->setExecutionFunction(&Executor::_li) },
            { std::string("la"), (new Instruction("la"))->setExecutionFunction(&Executor::_la) },
            { std::string("nor"), (new Instruction("nor"))->setExecutionFunction(&Executor::_nor) },
            { std::string("not"), (new Instruction("not"))->setExecutionFunction(&Executor::_not) },
            { std::string("label"), (new Instruction("label"))->setExecutionFunction(&Executor::_label) },
            { std::string("invalid"), (new Instruction("invalid", A_PASS))->setExecutionFunction(&Executor::_invalid) }

};

namespace MipsInstructions {
#include <string>

    Instruction *getInstructionByName(const std::string& instructionName) {
        auto pair = instructionByName.find(instructionName);
        if (pair == instructionByName.end()) return NULL;
        return pair->second;
    }
};

#endif  //!__INSTRUCTIONS__H__