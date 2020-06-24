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


Instruction Interpreter::interpretInstruction(std::string instruction) {
    std::vector<std::string> instruction_parts = split(instruction);
    if (instruction_parts[0] == "j") return Instruction(instruction, Executor::_jump);
}