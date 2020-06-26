#include "Interpreter.h"
#include "MipsInstructions.h"

#include <vector>
#include <iostream>
#include "string_utils.h"

Interpreter::Interpreter(Executor *parentExecutor) 
: parentExecutor(parentExecutor) 
{}

Instruction *Interpreter::interpretInstruction(const std::string& instructionStr) const {
    std::vector<std::string> instruction_parts = split(instructionStr);
    std::vector<Register*> registers;
    std::vector<int> integers;
    int intPos = 0,regPos = 0;

    //TODO: no_advance
    if (instruction_parts.size() < 1) return new Instruction("", A_PASS);

    Instruction *instruction = MipsInstructions::getInstructionByName(instruction_parts[0]);
    if (instruction == NULL) return new Instruction(instruction_parts[0], A_PASS);

    for (unsigned i = 1; i < instruction_parts.size(); i++) {
        if (isInteger(instruction_parts[i])) {
            instruction->feedIntegers(intPos++, stoi(instruction_parts[i]));
        } 
        else { //TODO: implement label
            try {
                Register &reg = parentExecutor->getRegisters().getRegisterByName(instruction_parts[i]);
                instruction->feedRegisters(regPos++,&reg);
            } catch (const std::invalid_argument& e) {
                fprintf(stderr, "ERROR: invalid register provided: '%s'\n", instruction_parts[i].c_str());
                std::cout << e.what() << std::endl;
            }
        }
    }

    //TODO: arrumar beqi, div2, div3, etc
    return instruction;
}