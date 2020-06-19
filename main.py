#TODO: fazer o registrador $zero read-only (ver se tem outros read-only tb)

inserted_instructions = []
position_of_labels = dict()
#Valores dos registradores
register_values = [0] * 67

registers_name_to_id = {
    "$zero": 0,
    "$at": 1,
    "$v0": 2,
    "$v1": 3,
    "$a0": 4,
    "$a1": 5,
    "$a2": 6,
    "$a3": 7,
    "$t0": 8,
    "$t1": 9,
    "$t2": 10,
    "$t3": 11,
    "$t4": 12,
    "$t5": 13,
    "$t6": 14,
    "$t7": 15,
    "$s0": 16,
    "$s1": 17,
    "$s2": 18,
    "$s3": 19,
    "$s4": 20,
    "$s5": 21,
    "$s6": 22,
    "$s7": 23,
    "$t8": 24,
    "$t9": 25,
    "$k0": 26,
    "$k1": 27,
    "$gp": 28,
    "$sp": 29,
    "$fp": 30,
    "$f0": 31,
    "$f1": 32,
    "$f2": 33,
    "$f3": 34,
    "$f4": 35,
    "$f5": 36,
    "$f6": 37,
    "$f7": 38,
    "$f8": 39,
    "$f9": 40,
    "$f10": 41,
    "$f11": 42,
    "$f12": 43,
    "$f13": 44,
    "$f14": 45,
    "$f15": 46,
    "$f16": 47,
    "$f17": 48,
    "$f18": 49,
    "$f19": 50,
    "$f20": 51,
    "$f21": 52,
    "$f22": 53,
    "$f23": 54,
    "$f24": 55,
    "$f25": 56,
    "$f26": 57,
    "$f27": 58,
    "$f28": 59,
    "$f29": 60,
    "$f30": 61,
    "$f31": 62,
    "$HI": 63,
    "$LO": 64,
    "$ra": 65,
    "$pc": 66
}


def get_command_parts_R_type(command, register_quantity=3):
    command_parts = command.split(' ')
    if (len(command_parts) != (register_quantity + 1)):
        print("Erro: Formato da instrução inválido (tipo R)")
        return tuple([None] * register_quantity)
    
    register_names = command_parts[1:]
    register_ids = []

    for register_name in register_names:
        if (register_name not in registers_name_to_id):
            print("Erro: " +register_name + " não é um registrador válido!")
            return tuple([None] * register_quantity)
        register_ids.append(int(registers_name_to_id[register_name]))

    return tuple(register_ids)

def get_command_parts_I_type(command, register_quantity=2):
    command_parts = command.split(' ')
    if (len(command_parts) != 1 + register_quantity + 1):
        print("Erro: Formato da instrução inválido (tipo I)")
        return tuple([None] * (register_quantity+1))
    register_names = command_parts[1:1+register_quantity]
    register_ids = []

    for register_name in register_names:
        if (register_name not in registers_name_to_id.keys()):
            print("Erro: " +register_name + " não é um registrador válido!")
            return tuple([None] * (register_quantity+1))
        register_ids.append(int(registers_name_to_id[register_name]))

    immediate = int(command_parts[register_quantity+1])

    #Adiciona à futura tupla 
    register_ids.append(immediate)

    #também retorna o imediato
    return tuple(register_ids)


def get_branch_true(bool_val,label):
    if(bool_val):
        if(label in position_of_labels):
            return (True, position_of_labels[label])
        else:
            return (True, -1)
    else:
        return(False, -1)


def get_command_parts_branch(command):
    command = command.split()
    registers1 = ["beqz","bnez","bgez","bgtz","blez","bltz","bgezal","bltzal"]
    registers2 = ["bne","beq","blt","ble","bgt","bge"]
    link_registers = ["bgezal","bltzal"]


    value2 = 0
    if(command[0] in registers1):
        if(len(command)!=3):
            print("Erro: Formato da instrução inválido")
            return (None, None)
    if(command[0] in registers2):
        if(len(command)!=4):
            print("Erro: Formato da instrução inválido")
            return (None, None)
        if(command[2].isdigit()):
            value2 = int(command[2])
        else:
            if(command[2] not in registers_name_to_id):
                print("Erro: Registrador inexistente")
                return (None, None)
            value2 = register_values[command[2]]

    else:
        print("Erro: Formato da instrução inválido")
        return (None, None)

    if(command[1] not in registers_name_to_id):
        print("Erro: Registrador inexistente")
        return (None,None)
    value1 = register_values[command[1]]

    command_eq = ["beq","bez"]
    command_dif = ["bne","bnez"]
    command_less = ["bltz","bltzal","blt"]
    command_less_eq = ["blez","ble"]
    command_greater = ["bgtz","bgt"]
    command_greater_eq = ["bgez","bgezal","bge"]


    should_jump, branch_jump_pos = False, -1
    if command[0] in command_eq:
        should_jump, branch_jump_pos = get_branch_true(value1 == value2, command)
    elif(command[0] in command_dif ):
        should_jump, branch_jump_pos = get_branch_true(value1 != value2,command)
    elif(command[0] in command_less ):
        should_jump, branch_jump_pos = get_branch_true(value1 < value2,command)
    elif(command[0] in command_less_eq ):
        should_jump, branch_jump_pos = get_branch_true(value1 <= value2,command)
    elif(command[0] in command_greater ):
        should_jump, branch_jump_pos = get_branch_true(value1 > value2,command)        
    elif(command[0] in command_greater_eq ):
        should_jump, branch_jump_pos = get_branch_true(value1 >= value2,command)
    else:
        print("ERRO: Comando fora dos valores existentes")
        return (None, None)

    if(command[0] in link_registers):
        registers_name_to_id["$ra"] = register_values[registers_name_to_id['$PC']]+1
        print("A posição atual"+str(registers_name_to_id["$ra"])+"foi salva no registrador $ra")

    return should_jump, branch_jump_pos        

def interpret_command(command):
    command = command.replace(',','')
    command_parts = (" ".join(command.split(' '))).split()

    #Sai do programa
    if (command_parts[0] == 'exit'):
        exit(0)

    #Roda o programa
    elif (command_parts[0] == 'run'):
        pass #TODO: fazer as coisas

    #Adiciona novas labels ao codigo
    elif command.endswith(':'):
        if (len(command_parts) != 1):
            print('Cannot have spaces in label identifier')
            return False
            
        #Verifica se o a label ja existe no codigo
        if (command_parts[0][:-1] in position_of_labels):
            print(f'Label {command_parts[-1][:-1]} already exists')
            return False
            
        position_of_labels[command[:-1]] = len(inserted_instructions)
        print(position_of_labels[command[:-1]])
        return True
    
    #INSTRUCAO 'j' (JUMP)
    elif (command_parts[0] == 'j' or command_parts == 'b'):
        if (len(command_parts) != 2):
            print(f'Invalid sintax of command \'{command_parts[0]}\'. Use: {command_parts[0]} <label_identifier>')
            return False
        
        if (command_parts[1] not in position_of_labels):
            print(f'Label {command_parts[-1][:-1]} does not exist')
            return False
            
        position_of_labels[command[:-1]] = len(inserted_instructions)
        print(position_of_labels[command[:-1]])
        return True

    #INSTRUCAO 'add'
    elif (command_parts[0] == 'add'):
        print('add foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        if (reg1_id == None or reg2_id == None or reg3_id == None): return False
        register_values[reg1_id] = register_values[reg2_id] + register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
       
    #INSTRUCAO 'addi'
    elif (command_parts[0] == 'addi'):
        print('addi foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        if (reg1_id == None or reg2_id == None or immediate == None): return False
        register_values[reg1_id] = register_values[reg2_id] + immediate
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))

    #INSTRUCAO 'li'
    elif (command_parts[0] == 'li'):
        print('li foda (tipo I)')
        reg1_id, immediate = get_command_parts_I_type(command, 1)
        register_values[reg1_id] = immediate #addi $reg1, $zero, immediate
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))

    #INSTRUCAO 'sub'
    elif (command_parts[0] == 'sub'):
        print('sub foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        if (reg1_id == None): return False
        register_values[reg1_id] = register_values[reg2_id] - register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
    
    #INSTRUCAO 'mult'
    elif (command_parts[0] == 'mult'):
        print('instrucao mult foda')

    #INSTRUCAO 'mul'
    elif (command_parts[0] == 'mul'):
        print('pseudo instrucao mult foda')
        
    #INSTRUCAO 'div'
    elif (command_parts[0] == 'div'):
        if (len(command_parts) == 3):
            print('div foda')
            reg1_id, reg2_id = get_command_parts_R_type(command, 2)
            v1, v2 = register_values[reg1_id], register_values[reg2_id]
            quocient = v1 // v2
            rest = v1 % v2
            
            register_values[registers_name_to_id['$LO']] = quocient
            register_values[registers_name_to_id['$HI']] = rest
            print("Novo valor de $HI = " + str(register_values[registers_name_to_id['$HI']]))
            print("Novo valor de $LO = " + str(register_values[registers_name_to_id['$LO']]))

        elif (len(command_parts) == 4):
            print('pseudo div foda')
            reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command, 3)
            v1, v2 = register_values[reg2_id], register_values[reg3_id]
            quocient = v1 // v2
            rest = v1 % v2
            
            register_values[reg3_id] = quocient
            register_values[registers_name_to_id['$LO']] = quocient
            register_values[registers_name_to_id['$HI']] = rest
            print("Novo valor de $HI = " + str(register_values[registers_name_to_id['$HI']]))
            print("Novo valor de $LO = " + str(register_values[registers_name_to_id['$LO']]))
            print("Novo valor de " + command[1] + " = " + str(register_values[reg1_id]))

        else:
            print('div errada ai amigao')
            return False
 
    #INSTRUCAO 'rem'
    elif (command_parts[0] == 'rem'):
        pass

    #instruções de branch
    elif (command[0] in ["bgez", "bgtz", "blez", "bltz", "beqz", "beq", "bne", "blt", "ble", "bgt", "bge"]):
        should_jump, branch_jump_pos = False, -1
        should_jump, branch_jump_pos = get_command_parts_branch(command)
        if(should_jump == None and branch_jump_pos == None):
            pass
        elif(not should_jump):
            print("Condições para o branch não foram satisfeitas")
        elif(should_jump == True and branch_jump_pos == -1):
            print("Label não incializada")
        else:
            print("Foi feito um branch para a posição "+str(branch_jump_pos))
        pass
    
    #INSTRUCAO 'and'
    elif (command_parts[0] == 'and'):
        print('and foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        register_values[reg1_id] = register_values[reg2_id] & register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + register_values[reg1_id])
        pass

    #INSTRUCAO 'andi'
    elif (command_parts[0] == 'andi'):
        print('andi foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        register_values[reg1_id] = register_values[reg2_id] & immediate
        print("Novo valor de " + command_parts[1] + " = " + register_values[reg1_id])
        pass
    
    #INSTRUCAO 'or'
    elif (command_parts[0] == 'or'):
        print('or foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        register_values[reg1_id] = register_values[reg2_id] | register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + register_values[reg1_id])
        pass

    #INSTRUCAO 'ori'
    elif (command_parts[0] == 'ori'):
        print('ori foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        register_values[reg1_id] = register_values[reg2_id] | immediate
        print("Novo valor de " + command_parts[1] + " = " + register_values[reg1_id])
        pass

    
    #INSTRUCAO 'xor'
    elif (command_parts[0] == 'xor'):
        print('xor foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        register_values[reg1_id] = register_values[reg2_id] ^ register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + register_values[reg1_id])
        pass

    #INSTRUCAO 'xori'
    elif (command_parts[0] == 'xori'):
        print('xori foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        register_values[reg1_id] = register_values[reg2_id] ^ immediate
        print("Novo valor de " + command_parts[1] + " = " + register_values[reg1_id])
        pass

    #INSTRUCAO 'mflo'
    elif (command_parts[0] == 'mflo'):
        pass

    #INSTRUCAO 'mfhi'
    elif (command_parts[0] == 'mfhi'):
        pass

    #INSTRUCAO 'jal'
    elif (command_parts[0] == 'jal'):
        if (len(command_parts) != 2):
            print('Invalid use of \'jal\'')
            return False
        
        ra_id = registers_name_to_id['$ra']
        pc_id = registers_name_to_id['$pc']
        register_values[ra_id] = register_values[pc_id] + 1
        interpret_command('j '+command_parts[1])
    
    #INSTRUCAO 'jalr'
    elif (command_parts[0] == 'jalr'):
        pass

    #INSTRUCAO 'jr'
    elif (command_parts[0] == 'jr'):
        if (len(command_parts) != 2):
            print('Invalid use of \'jr\'')
            return False

        pc_id = registers_name_to_id['$pc']
        ra_id = registers_name_to_id['$ra']
        register_values[pc_id] = register_values[ra_id]

    #INSTRUCAO 'syscall'
    elif (command_parts[0] == 'syscall'):
        if (len(command_parts) != 1):
            print('Invalid use of \'Syscall\'. Invalidating instruction.')
            return False

        pass #TODO: fazer a syscall

        
    #Comando invalido ou nao implementado
    else:
        print("Command not implemented or command does not exist")
        return False
    
    return True


def loop():
    command = input("[MIPS Debugger] >>> ")
    if (interpret_command(command) == True):
        inserted_instructions.append(command)

def main():
    print('Starting MIPS Debugger.\nUse the instruction \'run\' to run the program.n\nUse instruction \'exit\' to finish the program.\n')
    while True:
        loop()

if (__name__ == '__main__'):
    main()

#TODO: FAZER O PC FUNCIONAR
#TODO: fazer o .data section
#TODO: 