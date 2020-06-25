#include "Interpreter.h"

#include <vector>
#include "string_utils.h"

#define sef(F) instruction->setExecutionFunction(&Executor::_##F)

Interpreter::Interpreter(Executor *parentExecutor) {
    this->parentExecutor = parentExecutor;
}

Interpreter::~Interpreter()
{
}

void defineExecutionFunction(Instruction *instruction) {
         if (instruction->toString() == "lw") sef(lw);
    else if (instruction->toString() == "sw") sef(sw);
    else if (instruction->toString() == "lb") sef(lb);
    else if (instruction->toString() == "sb") sef(sb);
    else if (instruction->toString() == "beq") sef(beq);
    else if (instruction->toString() == "bgez") sef(bgez);
    else if (instruction->toString() == "bgezal") sef(bgezal);
    else if (instruction->toString() == "bgtz") sef(bgtz);
    else if (instruction->toString() == "blez") sef(blez);
    else if (instruction->toString() == "bltz") sef(bltz);
    else if (instruction->toString() == "bltzal") sef(bltzal);
    else if (instruction->toString() == "bne") sef(bne);
    else if (instruction->toString() == "b") sef(b);
    else if (instruction->toString() == "bal") sef(bal);
    else if (instruction->toString() == "bgt") sef(bgt);
    else if (instruction->toString() == "blt") sef(blt);
    else if (instruction->toString() == "bge") sef(bge);
    else if (instruction->toString() == "ble") sef(ble);
    else if (instruction->toString() == "bgtu") sef(bgtu);
    else if (instruction->toString() == "beqz") sef(beqz);
    else if (instruction->toString() == "beqi") sef(beqi);
    else if (instruction->toString() == "jump") sef(jump);
    else if (instruction->toString() == "add") sef(add);
    else if (instruction->toString() == "addi") sef(addi);
    else if (instruction->toString() == "sub") sef(sub);
    else if (instruction->toString() == "mult") sef(mult);
    else if (instruction->toString() == "mflo") sef(mflo);
    else if (instruction->toString() == "mfhi") sef(mfhi);
    else if (instruction->toString() == "mul") sef(mul);
    else if (instruction->toString() == "div2") sef(div2);
    else if (instruction->toString() == "div3") sef(div3);
    else if (instruction->toString() == "rem") sef(rem);
    else if (instruction->toString() == "and") sef(and);
    else if (instruction->toString() == "or") sef(or);
    else if (instruction->toString() == "xor") sef(xor);
    else if (instruction->toString() == "andi") sef(andi);
    else if (instruction->toString() == "ori") sef(ori);
    else if (instruction->toString() == "xori") sef(xori);
    else if (instruction->toString() == "slt") sef(slt);
    else if (instruction->toString() == "sltu") sef(sltu);
    else if (instruction->toString() == "slti") sef(slti);
    else if (instruction->toString() == "sltiu") sef(sltiu);
    else if (instruction->toString() == "jal") sef(jal);
    else if (instruction->toString() == "addiu") sef(addiu);
    else if (instruction->toString() == "addu") sef(addu);
    else if (instruction->toString() == "subu") sef(subu);
    else if (instruction->toString() == "divu") sef(divu);
    else if (instruction->toString() == "sllv") sef(sllv);
    else if (instruction->toString() == "jr") sef(jr);
    else if (instruction->toString() == "jalr") sef(jalr);
    else if (instruction->toString() == "lui") sef(lui);
    else if (instruction->toString() == "sll") sef(sll);
    else if (instruction->toString() == "noop") sef(noop);
    else if (instruction->toString() == "nop") sef(nop);
    else if (instruction->toString() == "sra") sef(sra);
    else if (instruction->toString() == "srl") sef(srl);
    else if (instruction->toString() == "syscall") sef(syscall);
    else if (instruction->toString() == "move") sef(move);
    else if (instruction->toString() == "srlv") sef(srlv);
    else if (instruction->toString() == "clear") sef(clear);
    else if (instruction->toString() == "li") sef(li);
    //TODO: fazer li pra short
    // else if (instruction->toString() == "li") sef(li);
    else if (instruction->toString() == "la") sef(la);
    else if (instruction->toString() == "nor") sef(nor);
    else if (instruction->toString() == "not") sef(not);
}

Instruction *Interpreter::interpretInstruction(std::string instructionStr) {
    std::vector<std::string> instruction_parts = split(instructionStr);
    std::vector<Register*> registers;
    std::vector<int> integers;

    if (instruction_parts.size() < 1) return new Instruction();

    Instruction *generated_instruction = new Instruction(instruction_parts[0], parentExecutor);

    defineExecutionFunction(generated_instruction);
    if (generated_instruction->isUnknown()) return generated_instruction;

    for (unsigned i = 1; i < instruction_parts.size(); i++) {
        if (isInteger(instruction_parts[i])) {
            integers.push_back(stoi(instruction_parts[i]));
        } 
        else { //TODO: implement label
            Register *reg = parentExecutor->getRegisters()->getRegisterByName(instruction_parts[i]);
            if (reg == NULL) {
                fprintf(stderr, "ERROR: invalid register provided: '%s'\n", instruction_parts[i].c_str());
                continue;
            }
            registers.push_back(reg);
        }
    }

    generated_instruction->feed(registers, integers);

    //TODO: arrumar beqi, div2, div3, etc


         

    return generated_instruction;
}