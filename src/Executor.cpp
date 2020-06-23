#include "Executor.h"

int Executor::registerIntValues(int regId){
    return registerValues[regId].asInt();
}

int Executor::nameToId(char *name){
    return registerNameToId[std::string(name)];
}

Word *Executor::_lw(int stackAddress) {
    return new Word(stack.loadBytes(stackAddress, 4));
}

void Executor::_sw(int stackAdress, Word *word) {
    this->stack.writeBytes(stackAdress, word->asByteArray(), 4);
}

char Executor::_lb(int stackAddress) {
    return this->stack.loadByte(stackAddress);
}

void Executor::_sb(int stackAdress, char byte) {
    this->stack.writeByte(stackAdress, byte);
}

void Executor::_beq(int reg1Id, int reg2Id, int jumpAddress){
    if(registerIntValues(reg1Id) == registerIntValues(reg2Id)) _jump(jumpAddress);    
}

void Executor::_bgez(int regId, int jumpAddress){
    if(registerIntValues(regId) >= 0) _jump(jumpAddress);    
}

void Executor::_bgezal(int regId, int jumpAddress){
    if(registerIntValues(regId) >= 0) _jal(jumpAddress);    
    
}

void Executor::_bgtz(int regId, int jumpAddress){
    if(registerIntValues(regId) > 0) _jump(jumpAddress);    
}

void Executor::_blez(int regId, int jumpAddress){
    if(registerIntValues(regId) <= 0) _jump(jumpAddress);    
}

void Executor::_bltz(int regId, int jumpAddress){
    if(registerIntValues(regId) < 0) _jump(jumpAddress);    
}

void Executor::_bltzal(int regId, int jumpAddress){
    if(registerIntValues(regId) < 0) _jal(jumpAddress);    
}

void Executor::_bne(int reg1Id, int reg2Id, int jumpAddress){
    if(registerIntValues(reg1Id) != registerIntValues(reg2Id)) _jump(jumpAddress);    
}



//TODO:

void Executor::_b(int jumpAddress){
    _beq(nameToId("$zero"),nameToId("$zero"),jumpAddress);
}

void Executor::_bal(int jumpAddress){
    _bgezal(nameToId("$zero"),jumpAddress);
}

void Executor::_bgt(int reg1Id, int reg2Id, int jumpAddress){
    _slt(nameToId("$at"),reg2Id,reg1Id);
    bne
}


void Executor::_beqz(int regId, int jumpAddress){
}

void Executor::_bnez(int regId, int jumpAddress){
}




void Executor::_blt(int reg1Id, int reg2Id, int jumpAddress){
}

void Executor::_ble(int reg1Id, int reg2Id, int jumpAddress){
}


void Executor::_bge(int reg1Id, int reg2Id, int jumpAddress){
}


void Executor::_jump(int jumpAddress){
    if(jumpAddress < 0 || jumpAddress >= this->stack.getStackSize()) printf("ERROR: Jump adress out of range.\n");
    else registerValues[this->registerNameToId[std::string("$pc")]].setValue(jumpAddress);
}

void Executor::_add(int reg1Id,int reg2Id,int reg3Id){
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) + registerIntValues(reg3Id));   
}

void Executor::_addi(int reg1Id, int reg2Id, int intValue){
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) + intValue);   
}

void Executor::_sub(int reg1Id,int reg2Id,int reg3Id){
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) - registerIntValues(reg3Id));   
}

void Executor::_mult(int reg1Id,int reg2Id){
    registerValues[nameToId("$LO")].setValue(registerIntValues(reg1Id) * registerIntValues(reg2Id));
}

void Executor::_mflo(int regId){
    registerValues[regId].setValue(registerIntValues(nameToId("$LO")));    
}

void Executor::_mfhi(int regId){
    registerValues[regId].setValue(registerIntValues(nameToId("$HI")));    
}


void Executor::_mul(int reg1Id,int reg2Id,int reg3Id){
    _mult(reg2Id,reg1Id);
    _mflo(reg1Id);
}

void Executor::_div(int reg1Id,int reg2Id) { 
    registerValues[nameToId("$LO")].setValue(registerIntValues(reg1Id) / registerIntValues(reg2Id));   
    registerValues[nameToId("$HI")].setValue(registerIntValues(reg1Id) % registerIntValues(reg2Id));   
}

void Executor::_div(int reg1Id,int reg2Id,int reg3Id) { 
    _div(reg2Id,reg3Id);
    _mflo(reg1Id);
}

void Executor::_rem(int reg1Id,int reg2Id,int reg3Id) { 
    _div(reg2Id,reg3Id);
    _mfhi(reg1Id);
}

void Executor::_and(int reg1Id, int reg2Id, int reg3Id) {
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) & registerIntValues(reg3Id));
}

void Executor::_or(int reg1Id, int reg2Id, int reg3Id) {
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) | registerIntValues(reg3Id));
}

void Executor::_xor(int reg1Id, int reg2Id, int reg3Id) {
    registerValues[reg1Id].setValue(pow(registerIntValues(reg2Id),registerIntValues(reg3Id)));
}

void Executor::_andi(int reg1Id, int reg2Id, int immediate) {
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) & immediate);
}

void Executor::_ori(int reg1Id, int reg2Id, int immediate) {
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) | immediate);
}

void Executor::_xori(int reg1Id, int reg2Id, int immediate) {
    registerValues[reg1Id].setValue(registerIntValues(reg2Id) ^ immediate);
}

void Executor::_slt(int reg1Id, int reg2Id, int reg3Id){
    if(registerIntValues(reg2Id) < registerIntValues(reg3Id)) registerValues[reg1Id].setValue(1);
    else registerValues[reg1Id].setValue(0);
}


void Executor::_sltu(int reg1Id, int reg2Id, int reg3Id){
    if((unsigned int)registerIntValues(reg2Id) < (unsigned int)registerIntValues(reg3Id)) 
        registerValues[reg1Id].setValue(1);
    else registerValues[reg1Id].setValue(0);
}


void Executor::_slti(int reg1Id, int reg2Id, int immediate){
    if(registerIntValues(reg2Id)<immediate) registerValues[reg1Id].setValue(1);
    else registerValues[reg1Id].setValue(0);
}

void Executor::_sltiu(int reg1Id, int reg2Id, unsigned immediate){
    if((unsigned int)registerIntValues(reg2Id)<immediate) registerValues[reg1Id].setValue(1);
    else registerValues[reg1Id].setValue(0);
}

void Executor::_jal(int jumpAddress){
    registerValues[nameToId("$ra")].setValue(registerIntValues(nameToId("$pc")));
    _jump(jumpAddress);
}


//void Executor::_()


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

