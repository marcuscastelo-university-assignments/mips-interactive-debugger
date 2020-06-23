#include "Executor.h"

char *Executor::lw(int stackAddress) {
    return this->stack.loadBytes(stackAddress, 4);
}

void Executor::sw(int stackAdress, char* word) {
    this->stack.writeBytes(stackAdress, word, 4);
}

char Executor::lb(int stackAddress) {
    return this->stack.loadByte(stackAddress);
}

void Executor::sb(int stackAdress, char word) {
    this->stack.writeByte(stackAdress, word);
}

void Executor::beqz(int regId, int jumpAddress){
    if(regId == 0) jump(jumpAddress);
}

void Executor::bnez(int regId, int jumpAddress){
    if(regId != 0) jump(jumpAddress);    
}

void Executor::bgez(int regId, int jumpAddress){
    if(regId >= 0) jump(jumpAddress);    
}

void Executor::bgtz(int regId, int jumpAddress){
    if(regId > 0) jump(jumpAddress);    
}

void Executor::blez(int regId, int jumpAddress){
    if(regId <= 0) jump(jumpAddress);    
}

void Executor::bltz(int regId, int jumpAddress){
    if(regId < 0) jump(jumpAddress);    
}

void Executor::bgezal(int regId, int jumpAddress){
    if(regId >= 0) jump(jumpAddress);    
}

void Executor::bltzal(int regId, int jumpAddress){
    if(regId < 0) jump(jumpAddress);    
}

void Executor::bne(int reg1Id, int reg2Id, int jumpAddress){
    if(reg1Id != reg2Id) jump(jumpAddress);    
}

void Executor::beq(int reg1Id, int reg2Id, int jumpAddress){
    if(reg1Id == reg2Id) jump(jumpAddress);    
}

void Executor::blt(int reg1Id, int reg2Id, int jumpAddress){
    if(reg1Id < reg2Id) jump(jumpAddress);    
}

void Executor::ble(int reg1Id, int reg2Id, int jumpAddress){
    if(reg1Id <= reg2Id) jump(jumpAddress);    
}

void Executor::bgt(int reg1Id, int reg2Id, int jumpAddress){
    if(reg1Id > reg2Id) jump(jumpAddress);    
}

void Executor::bge(int reg1Id, int reg2Id, int jumpAddress){
    if(reg1Id >= reg2Id) jump(jumpAddress);    
}

void Executor::jump(int jumpAddress){
    if(jumpAddress < 0 || jumpAddress >= this->stack.getStackSize()) printf("ERROR: Jump adress out of range.\n");
    else registerValues[this->registerNameToId[std::string("$pc")]] = jumpAddress;
}



/*
def get_branch_true(bool_val,label):
    if(bool_val):
        if(label in position_of_labels.keys()):
            return (True, position_of_labels[label])
        else:
            return (True, -1)
    else:
        return(False, -1)


def get_command_parts_branch(command):
    command_parts = command.split()
    registers1 = ["beqz","bnez","bgez","bgtz","blez","bltz","bgezal","bltzal"]
    registers2 = ["bne","beq","blt","ble","bgt","bge"]  
    
    link_registers = ["bgezal","bltzal"]


    value2 = 0
    if(command_parts[0] in registers1):
        if(len(command_parts)!=3):
            print("Erro: Formato da instrução inválido")
            return (None, None)
    if(command_parts[0] in registers2):
        if(len(command_parts)!=4):
            print("Erro: Formato da instrução inválido")
            return (None, None)
        
        if(command_parts[2].isdigit()):
            value2 = int(command_parts[2])
        else:
            if(command_parts[2] not in registers_name_to_id.keys()):
                print(f'Erro: Registrador {command_parts[2]} inexistente')
                return (None, None)
            value2 = register_values[registers_name_to_id[command_parts[2]]]

    else:
        print("Erro: Formato da instrução inválido")
        return (None, None)

    if(command_parts[1] not in registers_name_to_id.keys()):
        print(f'[{command_parts[1]}] != [{list(registers_name_to_id.keys())[0]}]')
        print(f'Erro: Registrador {command_parts[1]} inexistente')
        return (None,None)
    value1 = register_values[registers_name_to_id[command_parts[1]]]

    command_eq = ["beq","bez"]
    command_dif = ["bne","bnez"]
    command_less = ["bltz","bltzal","blt"]
    command_less_eq = ["blez","ble"]
    command_greater = ["bgtz","bgt"]
    command_greater_eq = ["bgez","bgezal","bge"]


    should_jump, branch_jump_pos = False, -1
    if command_parts[0] in command_eq:
        should_jump, branch_jump_pos = get_branch_true(value1 == value2, command_parts[-1])
    elif(command_parts[0] in command_dif ):
        should_jump, branch_jump_pos = get_branch_true(value1 != value2,command_parts[-1])
    elif(command_parts[0] in command_less ):
        should_jump, branch_jump_pos = get_branch_true(value1 < value2,command_parts[-1])
    elif(command_parts[0] in command_less_eq ):
        should_jump, branch_jump_pos = get_branch_true(value1 <= value2,command_parts[-1])
    elif(command_parts[0] in command_greater ):
        should_jump, branch_jump_pos = get_branch_true(value1 > value2,command_parts[-1])        
    elif(command_parts[0] in command_greater_eq ):
        should_jump, branch_jump_pos = get_branch_true(value1 >= value2,command_parts[-1])
    else:
        print("ERRO: Comando fora dos valores existentes")
        return (None, None)

    if(command_parts[0] in link_registers and should_jump == True and branch_jump_pos!= -1):

        ra_id = registers_name_to_id["$ra"]
        register_values[ra_id] = register_values[registers_name_to_id['$pc']]+1

        print("A posição atual"+str(registers_name_to_id["$ra"])+"foi salva no registrador $ra")

    return should_jump, branch_jump_pos        
*/

