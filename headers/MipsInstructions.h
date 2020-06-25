#ifndef __INSTRUCTIONS__H__
#define __INSTRUCTIONS__H__

#include "Instruction.h"
#include <map>
#include <string>

class MipsInstructions {
    private:
        std::map<std::string, Instruction*> instructionByName; 
    public:
    MipsInstructions(void) {
        instructionByName[std::string("lw")] = lwInstruction = (new Instruction("lw"))->setExecutionFunction(Executor::_lw);
        instructionByName[std::string("sw")] = swInstruction = (new Instruction("sw"))->setExecutionFunction(Executor::_sw);
        instructionByName[std::string("lb")] = lbInstruction = (new Instruction("lb"))->setExecutionFunction(Executor::_lb);
        instructionByName[std::string("sb")] = sbInstruction = (new Instruction("sb"))->setExecutionFunction(Executor::_sb);
        instructionByName[std::string("beq")] = beqInstruction = (new Instruction("beq"))->setExecutionFunction(Executor::_beq);
        instructionByName[std::string("bgez")] = bgezInstruction = (new Instruction("bgez"))->setExecutionFunction(Executor::_bgez);
        instructionByName[std::string("bgezal")] = bgezalInstruction = (new Instruction("bgezal",LINK))->setExecutionFunction(Executor::_bgezal);
        instructionByName[std::string("bgtz")] = bgtzInstruction = (new Instruction("bgtz"))->setExecutionFunction(Executor::_bgtz);
        instructionByName[std::string("blez")] = blezInstruction = (new Instruction("blez"))->setExecutionFunction(Executor::_blez);
        instructionByName[std::string("bltz")] = bltzInstruction = (new Instruction("bltz"))->setExecutionFunction(Executor::_bltz);
        instructionByName[std::string("bltzal")] = bltzalInstruction = (new Instruction("bltzal",LINK))->setExecutionFunction(Executor::_bltzal);
        instructionByName[std::string("bne")] = bneInstruction = (new Instruction("bne"))->setExecutionFunction(Executor::_bne);
        instructionByName[std::string("b")] = bInstruction = (new Instruction("b"))->setExecutionFunction(Executor::_b);
        instructionByName[std::string("bal")] = balInstruction = (new Instruction("bal"))->setExecutionFunction(Executor::_bal);
        instructionByName[std::string("bgt")] = bgtInstruction = (new Instruction("bgt"))->setExecutionFunction(Executor::_bgt);
        instructionByName[std::string("blt")] = bltInstruction = (new Instruction("blt"))->setExecutionFunction(Executor::_blt);
        instructionByName[std::string("bge")] = bgeInstruction = (new Instruction("bge"))->setExecutionFunction(Executor::_bge);
        instructionByName[std::string("ble")] = bleInstruction = (new Instruction("ble"))->setExecutionFunction(Executor::_ble);
        instructionByName[std::string("bgtu")] = bgtuInstruction = (new Instruction("bgtu"))->setExecutionFunction(Executor::_bgtu);
        instructionByName[std::string("beqz")] = beqzInstruction = (new Instruction("beqz"))->setExecutionFunction(Executor::_beqz);
        instructionByName[std::string("beqi")] = beqiInstruction = (new Instruction("beqi"))->setExecutionFunction(Executor::_beqi);
        instructionByName[std::string("jump")] = jumpInstruction = (new Instruction("jump"))->setExecutionFunction(Executor::_jump);
        instructionByName[std::string("add")] = addInstruction = (new Instruction("add"))->setExecutionFunction(Executor::_add);
        instructionByName[std::string("addi")] = addiInstruction = (new Instruction("addi"))->setExecutionFunction(Executor::_addi);
        instructionByName[std::string("sub")] = subInstruction = (new Instruction("sub"))->setExecutionFunction(Executor::_sub);
        instructionByName[std::string("mult")] = multInstruction = (new Instruction("mult"))->setExecutionFunction(Executor::_mult);
        instructionByName[std::string("mflo")] = mfloInstruction = (new Instruction("mflo"))->setExecutionFunction(Executor::_mflo);
        instructionByName[std::string("mfhi")] = mfhiInstruction = (new Instruction("mfhi"))->setExecutionFunction(Executor::_mfhi);
        instructionByName[std::string("mul")] = mulInstruction = (new Instruction("mul"))->setExecutionFunction(Executor::_mul);
        instructionByName[std::string("div")] = div2Instruction = (new Instruction("div"))->setExecutionFunction(Executor::_div)->overloadSupposedIntegerCount(2);
        instructionByName[std::string("rem")] = remInstruction = (new Instruction("rem"))->setExecutionFunction(Executor::_rem);
        instructionByName[std::string("and")] = andInstruction = (new Instruction("and"))->setExecutionFunction(Executor::_and);
        instructionByName[std::string("or")] = orInstruction = (new Instruction("or"))->setExecutionFunction(Executor::_or);
        instructionByName[std::string("xor")] = xorInstruction = (new Instruction("xor"))->setExecutionFunction(Executor::_xor);
        instructionByName[std::string("andi")] = andiInstruction = (new Instruction("andi"))->setExecutionFunction(Executor::_andi);
        instructionByName[std::string("ori")] = oriInstruction = (new Instruction("ori"))->setExecutionFunction(Executor::_ori);
        instructionByName[std::string("xori")] = xoriInstruction = (new Instruction("xori"))->setExecutionFunction(Executor::_xori);
        instructionByName[std::string("slt")] = sltInstruction = (new Instruction("slt"))->setExecutionFunction(Executor::_slt);
        instructionByName[std::string("sltu")] = sltuInstruction = (new Instruction("sltu"))->setExecutionFunction(Executor::_sltu);
        instructionByName[std::string("slti")] = sltiInstruction = (new Instruction("slti"))->setExecutionFunction(Executor::_slti);
        instructionByName[std::string("sltiu")] = sltiuInstruction = (new Instruction("sltiu"))->setExecutionFunction(Executor::_sltiu);
        instructionByName[std::string("jal")] = jalInstruction = (new Instruction("jal",LINK))->setExecutionFunction(Executor::_jal);
        instructionByName[std::string("addiu")] = addiuInstruction = (new Instruction("addiu"))->setExecutionFunction(Executor::_addiu);
        instructionByName[std::string("addu")] = adduInstruction = (new Instruction("addu"))->setExecutionFunction(Executor::_addu);
        instructionByName[std::string("subu")] = subuInstruction = (new Instruction("subu"))->setExecutionFunction(Executor::_subu);
        instructionByName[std::string("divu")] = divuInstruction = (new Instruction("divu"))->setExecutionFunction(Executor::_divu);
        instructionByName[std::string("sllv")] = sllvInstruction = (new Instruction("sllv"))->setExecutionFunction(Executor::_sllv);
        instructionByName[std::string("jr")] = jrInstruction = (new Instruction("jr"))->setExecutionFunction(Executor::_jr);
        instructionByName[std::string("jalr")] = jalrInstruction = (new Instruction("jalr",LINK))->setExecutionFunction(Executor::_jalr);
        instructionByName[std::string("lui")] = luiInstruction = (new Instruction("lui"))->setExecutionFunction(Executor::_lui);
        instructionByName[std::string("sll")] = sllInstruction = (new Instruction("sll"))->setExecutionFunction(Executor::_sll);
        instructionByName[std::string("noop")] = noopInstruction = (new Instruction("noop"))->setExecutionFunction(Executor::_noop);
        instructionByName[std::string("nop")] = nopInstruction = (new Instruction("nop"))->setExecutionFunction(Executor::_nop);
        instructionByName[std::string("sra")] = sraInstruction = (new Instruction("sra"))->setExecutionFunction(Executor::_sra);
        instructionByName[std::string("srl")] = srlInstruction = (new Instruction("srl"))->setExecutionFunction(Executor::_srl);
        instructionByName[std::string("syscall")] = syscallInstruction = (new Instruction("syscall"))->setExecutionFunction(Executor::_syscall);
        instructionByName[std::string("move")] = moveInstruction = (new Instruction("move"))->setExecutionFunction(Executor::_move);
        instructionByName[std::string("srlv")] = srlvInstruction = (new Instruction("srlv"))->setExecutionFunction(Executor::_srlv);
        instructionByName[std::string("clear")] = clearInstruction = (new Instruction("clear"))->setExecutionFunction(Executor::_clear);
        instructionByName[std::string("li")] = liInstruction = (new Instruction("li"))->setExecutionFunction(Executor::_li);
        instructionByName[std::string("la")] = laInstruction = (new Instruction("la"))->setExecutionFunction(Executor::_la);
        instructionByName[std::string("nor")] = norInstruction = (new Instruction("nor"))->setExecutionFunction(Executor::_nor);
        instructionByName[std::string("not")] = notInstruction = (new Instruction("not"))->setExecutionFunction(Executor::_not);
    }

    Instruction *lwInstruction;
    Instruction *swInstruction;
    Instruction *lbInstruction;
    Instruction *sbInstruction;
    Instruction *beqInstruction;
    Instruction *bgezInstruction;
    Instruction *bgezalInstruction;
    Instruction *bgtzInstruction;
    Instruction *blezInstruction;
    Instruction *bltzInstruction;
    Instruction *bltzalInstruction;
    Instruction *bneInstruction;
    Instruction *bInstruction;
    Instruction *balInstruction;
    Instruction *bgtInstruction;
    Instruction *bltInstruction;
    Instruction *bgeInstruction;
    Instruction *bleInstruction;
    Instruction *bgtuInstruction;
    Instruction *beqzInstruction;
    Instruction *beqiInstruction;
    Instruction *jumpInstruction;
    Instruction *addInstruction;
    Instruction *addiInstruction;
    Instruction *subInstruction;
    Instruction *multInstruction;
    Instruction *mfloInstruction;
    Instruction *mfhiInstruction;
    Instruction *mulInstruction;
    Instruction *div2Instruction;
    Instruction *div3Instruction;
    Instruction *remInstruction;
    Instruction *andInstruction;
    Instruction *orInstruction;
    Instruction *xorInstruction;
    Instruction *andiInstruction;
    Instruction *oriInstruction;
    Instruction *xoriInstruction;
    Instruction *sltInstruction;
    Instruction *sltuInstruction;
    Instruction *sltiInstruction;
    Instruction *sltiuInstruction;
    Instruction *jalInstruction;
    Instruction *addiuInstruction;
    Instruction *adduInstruction;
    Instruction *subuInstruction;
    Instruction *divuInstruction;
    Instruction *sllvInstruction;
    Instruction *jrInstruction;
    Instruction *jalrInstruction;
    Instruction *luiInstruction;
    Instruction *sllInstruction;
    Instruction *noopInstruction;
    Instruction *nopInstruction;
    Instruction *sraInstruction;
    Instruction *srlInstruction;
    Instruction *syscallInstruction;
    Instruction *moveInstruction;
    Instruction *srlvInstruction;
    Instruction *clearInstruction;
    Instruction *liInstruction;
    Instruction *laInstruction;
    Instruction *norInstruction;
    Instruction *notInstruction;
};

#endif  //!__INSTRUCTIONS__H__