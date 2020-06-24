#include "Interpreter.h"

#include <vector>
#include "string_utils.h"

#define sef(F) generated_instruction->setExecutionFunction(&Executor::_##F)

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
    int invalidRegisters = 0;

    if (instruction_parts.size() < 1) return new Instruction(nullptr);

    for (unsigned i = 1; i < instruction_parts.size(); i++) {
        if (isInteger(instruction_parts[i])) {
            integers.push_back(stoi(instruction_parts[i]));
        } 
        else { //TODO: implement label
            Register *reg = parentExecutor->getRegisters()->getRegisterByName(instruction_parts[i]);
            if (reg == NULL) {
                fprintf(stderr, "ERROR: invalid register provided: '%s'\n", instruction_parts[i].c_str());
                invalidRegisters += 1;
                continue;
            }
            registers.push_back(reg);
        }
    }

    Instruction *generated_instruction = new Instruction(instruction_parts[0], parentExecutor);
    generated_instruction->feed(registers, integers);

    //TODO: arrumar beqi, div2, div3, etc


         if (instruction_parts[0] == "lw") sef(lw);
    else if (instruction_parts[0] == "sw") sef(sw);
    else if (instruction_parts[0] == "lb") sef(lb);
    else if (instruction_parts[0] == "sb") sef(sb);
    else if (instruction_parts[0] == "beq") sef(beq);
    else if (instruction_parts[0] == "bgez") sef(bgez);
    else if (instruction_parts[0] == "bgezal") sef(bgezal);
    else if (instruction_parts[0] == "bgtz") sef(bgtz);
    else if (instruction_parts[0] == "blez") sef(blez);
    else if (instruction_parts[0] == "bltz") sef(bltz);
    else if (instruction_parts[0] == "bltzal") sef(bltzal);
    else if (instruction_parts[0] == "bne") sef(bne);
    else if (instruction_parts[0] == "b") sef(b);
    else if (instruction_parts[0] == "bal") sef(bal);
    else if (instruction_parts[0] == "bgt") sef(bgt);
    else if (instruction_parts[0] == "blt") sef(blt);
    else if (instruction_parts[0] == "bge") sef(bge);
    else if (instruction_parts[0] == "ble") sef(ble);
    else if (instruction_parts[0] == "bgtu") sef(bgtu);
    else if (instruction_parts[0] == "beqz") sef(beqz);
    else if (instruction_parts[0] == "beqi") sef(beqi);
    else if (instruction_parts[0] == "jump") sef(jump);
    else if (instruction_parts[0] == "add") sef(add);
    else if (instruction_parts[0] == "addi") sef(addi);
    else if (instruction_parts[0] == "sub") sef(sub);
    else if (instruction_parts[0] == "mult") sef(mult);
    else if (instruction_parts[0] == "mflo") sef(mflo);
    else if (instruction_parts[0] == "mfhi") sef(mfhi);
    else if (instruction_parts[0] == "mul") sef(mul);
    else if (instruction_parts[0] == "div2") sef(div2);
    else if (instruction_parts[0] == "div3") sef(div3);
    else if (instruction_parts[0] == "rem") sef(rem);
    else if (instruction_parts[0] == "and") sef(and);
    else if (instruction_parts[0] == "or") sef(or);
    else if (instruction_parts[0] == "xor") sef(xor);
    else if (instruction_parts[0] == "andi") sef(andi);
    else if (instruction_parts[0] == "ori") sef(ori);
    else if (instruction_parts[0] == "xori") sef(xori);
    else if (instruction_parts[0] == "slt") sef(slt);
    else if (instruction_parts[0] == "sltu") sef(sltu);
    else if (instruction_parts[0] == "slti") sef(slti);
    else if (instruction_parts[0] == "sltiu") sef(sltiu);
    else if (instruction_parts[0] == "jal") sef(jal);
    else if (instruction_parts[0] == "addiu") sef(addiu);
    else if (instruction_parts[0] == "addu") sef(addu);
    else if (instruction_parts[0] == "subu") sef(subu);
    else if (instruction_parts[0] == "divu") sef(divu);
    else if (instruction_parts[0] == "sllv") sef(sllv);
    else if (instruction_parts[0] == "jr") sef(jr);
    else if (instruction_parts[0] == "jalr") sef(jalr);
    else if (instruction_parts[0] == "lui") sef(lui);
    else if (instruction_parts[0] == "sll") sef(sll);
    else if (instruction_parts[0] == "noop") sef(noop);
    else if (instruction_parts[0] == "nop") sef(nop);
    else if (instruction_parts[0] == "sra") sef(sra);
    else if (instruction_parts[0] == "srl") sef(srl);
    else if (instruction_parts[0] == "syscall") sef(syscall);
    else if (instruction_parts[0] == "move") sef(move);
    else if (instruction_parts[0] == "srlv") sef(srlv);
    else if (instruction_parts[0] == "clear") sef(clear);
    else if (instruction_parts[0] == "li") sef(li);
    //TODO: fazer li pra short
    // else if (instruction_parts[0] == "li") sef(li);
    else if (instruction_parts[0] == "la") sef(la);
    else if (instruction_parts[0] == "nor") sef(nor);
    else if (instruction_parts[0] == "not") sef(not);
    return generated_instruction;
}