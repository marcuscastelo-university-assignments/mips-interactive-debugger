#!/bin/python3
import signal, os, sys

#TODO: fazer o registrador $zero read-only (ver se tem outros read-only tb)
#TODO: help

inserted_instructions = []
inserted_breakpoints = []
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

stack = [b'\x00' for i in range(4096)]
register_values[registers_name_to_id['$sp']] = 4095

def lw_int():
    number = 0
    sp = register_values[registers_name_to_id['$sp']]
    for i in range(1,5): 
        number |= stack[sp-i]
        number << 8
    return number

def lw_string(string_size):
    string = ''
    sp = register_values[registers_name_to_id['$sp']]
    for i in range(1,string_size+1):
        string = stack[sp-i] + string
    return string

def sw(word):
    sp = register_values[registers_name_to_id['$sp']]
    if (word is int):
        for i in range(1,5): 
            stack[sp-(5-i)] = word & 255
            word >> 8
    elif word is str:
        for i in range(1,len(word)+1): stack[sp - (len(word) - i)] = word[i]

def lb():
    pass

def wb():
    pass
    
def make_syscall():
    v0_id = registers_name_to_id['$v0']
    v0_value = register_values[v0_id]
    
    if (v0_value == 1):
        a0_id = registers_name_to_id['$a0']
        a0_value = int(register_values[a0_id])
        print(a0_value)

    elif (v0_value == 2):
        f12_id = registers_name_to_id['$f12']
        f12_value = float(register_values[f12_id])
        print(f12_value)

    elif (v0_value == 3):
        f12_id = registers_name_to_id['$f12']
        f12_value = float(register_values[f12_id])
        print(f12_value)

    elif (v0_value == 4):
        a0_id = registers_name_to_id['$a0']
        a0_value = str(register_values[a0_id])
        print(a0_value)

    elif (v0_value == 5):
        v0_id = registers_name_to_id['$v0']
        v0_value = int(input())
        
    elif (v0_value == 6):
        v0_id = registers_name_to_id['$v0']
        v0_value = float(input())

    elif (v0_value == 7):
        v0_id = registers_name_to_id['$v0']
        v0_value = float(input())

    elif (v0_value == 8):
        pass #TODO: implementar syscall 8

    elif (v0_value == 10):
        pass
        
def is_label(str_to_verify):
    return str_to_verify.endswith(':')           

def print_reg(reg):
    print("|\t"+str(reg)+"\t:\t"+str(register_values[registers_name_to_id[reg]])+"\t|")

def print_reg_values():
    print("Current Position: "+str(register_values[registers_name_to_id["$pc"]])+"\n")
    print('-'*33)
    for i in registers_name_to_id:
        print_reg(i)
    print('-'*33)

def print_label(label):
    print("|\t"+str(label)+"\t:\t"+str(position_of_labels[label])+"\t|")

def print_labels():
    if len(position_of_labels.values()) == 0:
        print('There are currently no labels defined!')
        return
        
    print('-'*33)
    for i in position_of_labels.keys():
        print_label(i)
    print('-'*33)

def show_info(command_parts):
    if (command_parts[1] == "registers"): 
            print_reg_values()

    elif (command_parts[1] in registers_name_to_id.keys()):
        print('-'*33)
        print_reg(command_parts[1])
        print('-'*33)

    elif (command_parts[1] == "labels"):
        print_labels()

    elif (command_parts[1] in position_of_labels.keys()):
        print_label(command_parts[1])

def print_instruction(instruction):
    if (is_label(instruction)):
        print(f'\n{instruction}')
    else:
        print(f'\t{instruction}')

def show_instructions_all():
    len_instructions_vec = len(inserted_instructions)

    for i in range (len_instructions_vec):
        print_instruction(inserted_instructions[i])

def show_instructions_in(command_parts):
    inst_index = position_of_labels{command_parts[1]}
    len_instructions_vec = len(inserted_instructions)
    print_instruction(inserted_instructions[inst_index])
    inst_index += 1

    while inst_index < len_instructions_vec or inserted_instructions[inst_index]



def get_command_parts_R_type(command, register_quantity=3):
    command_parts = command.split(' ')
    if (len(command_parts) != (register_quantity + 1)):
        print("Erro: Formato da instrução inválido (tipo R)")
        return tuple([None] * register_quantity)
    
    register_names = command_parts[1:]
    register_ids = []

    for register_name in register_names:
        if (register_name not in registers_name_to_id):
            print(f'Erro: {register_name} não é um registrador válido!')
            return tuple([None] * register_quantity)
        register_ids.append(int(registers_name_to_id[register_name]))

    return tuple(register_ids)

def get_command_parts_I_type(command, register_quantity=2):
    command_parts = command.split(' ')
    if (len(command_parts) != 1 + register_quantity + 1):
        print("Erro: Formato da instrução inválido (tipo I)")
        print(command_parts)
        return tuple([None] * (register_quantity+1))
    register_names = command_parts[1:1+register_quantity]
    register_ids = []

    for register_name in register_names:
        if (register_name not in registers_name_to_id.keys()):
            print(f'Erro: {register_name} não é um registrador válido!')
            return tuple([None] * (register_quantity+1))
        register_ids.append(int(registers_name_to_id[register_name]))

    immediate = int(command_parts[register_quantity+1])

    #Adiciona à futura tupla 
    register_ids.append(immediate)

    #também retorna o imediato
    return tuple(register_ids)


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


def interpret_command(command):
    if (command.replace(' ','') == ''): return False
    if (command.encode('ascii') == b'\x0c' or command in ['cls', 'clear'] ): 
        os.system('cls' if os.name == 'nt' else 'clear')
        return False

    command = command.replace(',',' ')
    command = command.replace('  ',' ')
    command_parts = command.split(' ')
    


    #Sai do programa
    if (command_parts[0] == 'exit'):
        return "Exit_signal"

    #Roda o programa
    elif (command_parts[0] == 'run'):
        return False #TODO: fazer as coisas

    #Adiciona novas labels ao codigo
    elif command.endswith(':'):
        if (len(command_parts) != 1):
            print('Cannot have spaces in label identifier')
            return False
            
        #Verifica se o a label ja existe no codigo
        if (command_parts[0][:-1] in position_of_labels):
            print(f'Label {command_parts[-1][:-1]} already exists')
            return False
            
        position_of_labels[command[:-1]] = register_values[registers_name_to_id['$pc']] + 1
        print(position_of_labels[command[:-1]])
        return True
    
    #INSTRUCAO 'j' (JUMP)
    elif (command_parts[0] == 'j' or command_parts[0] == 'b'):
        if (len(command_parts) != 2):
            print(f'Invalid sintax of command \'{command_parts[0]}\'. Use: {command_parts[0]} <label_identifier>')
            return False
        
        if (command_parts[1] not in position_of_labels):
            print(f'Label {command_parts[-1]} does not exist')
            return False
            
        pc_id = registers_name_to_id['$pc']
        register_values[pc_id] = position_of_labels[command_parts[1]] - 1
        return True

    #INSTRUCAO 'add'
    elif (command_parts[0] == 'add'):
        print('add foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        if (None in [reg1_id, reg2_id, reg3_id]): return False
        register_values[reg1_id] = register_values[reg2_id] + register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
       
    #INSTRUCAO 'addi'
    elif (command_parts[0] == 'addi'):
        print('addi foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        if (None in [reg1_id, reg2_id, immediate]): return False
        register_values[reg1_id] = register_values[reg2_id] + immediate
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))

    #INSTRUCAO 'li'
    elif (command_parts[0] == 'li'):
        print('li foda (tipo I)')
        reg1_id, immediate = get_command_parts_I_type(command, 1)
        if (None in [reg1_id, immediate]): return False
        register_values[reg1_id] = immediate #addi $reg1, $zero, immediate
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))

    #INSTRUCAO 'sub'
    elif (command_parts[0] == 'sub'):
        print('sub foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        if (None in [reg1_id, reg2_id, reg3_id]): return False
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
            if (None in [reg1_id, reg2_id]): return False
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
            if (None in [reg1_id, reg2_id, reg3_id]): return False
            v1, v2 = register_values[reg2_id], register_values[reg3_id]
            quocient = v1 // v2
            rest = v1 % v2
            
            register_values[reg1_id] = quocient
            register_values[registers_name_to_id['$LO']] = quocient
            register_values[registers_name_to_id['$HI']] = rest
            print("Novo valor de $HI = " + str(register_values[registers_name_to_id['$HI']]))
            print("Novo valor de $LO = " + str(register_values[registers_name_to_id['$LO']]))
            print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))

        else:
            print('div errada ai amigao')
            return False
 
    #INSTRUCAO 'rem'
    elif (command_parts[0] == 'rem'):
        if (len(command_parts) == 3):
            print('div foda')
            reg1_id, reg2_id = get_command_parts_R_type(command, 2)
            if (None in [reg1_id, reg2_id]): return False
            v1, v2 = register_values[reg1_id], register_values[reg2_id]
            quocient = v1 // v2
            rest = v1 % v2
            
            register_values[reg1_id] = rest
            register_values[registers_name_to_id['$LO']] = quocient
            register_values[registers_name_to_id['$HI']] = rest

            print("Novo valor de $HI = " + str(register_values[registers_name_to_id['$HI']]))
            print("Novo valor de $LO = " + str(register_values[registers_name_to_id['$LO']]))
            print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))

        else:
            print('div errada ai amigao')
            return False

        pass

    #instruções de branch
    elif (command_parts[0] in ["bgez", "bgtz", "blez", "bltz", "beqz", "beq", "bne", "blt", "ble", "bgt", "bge", "bgezal", "bltzal"]):
        should_jump, branch_jump_pos = get_command_parts_branch(command)
        if(should_jump == None and branch_jump_pos == None):
            return False
        elif(not should_jump):
            print("Condições para o branch não foram satisfeitas")
        elif(should_jump == True and branch_jump_pos == -1):
            print("Label não incializada")
        else:
            print("Foi feito um branch para a posição "+str(branch_jump_pos))
            pc_id = registers_name_to_id['$pc']
            register_values[pc_id] = position_of_labels[command_parts[-1]] - 1
    
    #INSTRUCAO 'and'
    elif (command_parts[0] == 'and'):
        print('and foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        register_values[reg1_id] = register_values[reg2_id] & register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
        pass

    #INSTRUCAO 'andi'
    elif (command_parts[0] == 'andi'):
        print('andi foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        register_values[reg1_id] = register_values[reg2_id] & immediate
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
        pass
    
    #INSTRUCAO 'or'
    elif (command_parts[0] == 'or'):
        print('or foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        register_values[reg1_id] = register_values[reg2_id] | register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
        pass

    #INSTRUCAO 'ori'
    elif (command_parts[0] == 'ori'):
        print('ori foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        register_values[reg1_id] = register_values[reg2_id] | immediate
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
        pass

    
    #INSTRUCAO 'xor'
    elif (command_parts[0] == 'xor'):
        print('xor foda (tipo R)')
        reg1_id, reg2_id, reg3_id = get_command_parts_R_type(command)
        register_values[reg1_id] = register_values[reg2_id] ^ register_values[reg3_id]
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
        pass

    #INSTRUCAO 'xori'
    elif (command_parts[0] == 'xori'):
        print('xori foda (tipo I)')
        reg1_id, reg2_id, immediate = get_command_parts_I_type(command)
        register_values[reg1_id] = register_values[reg2_id] ^ immediate
        print("Novo valor de " + command_parts[1] + " = " + str(register_values[reg1_id]))
        pass

    #INSTRUCAO 'mflo'
    elif (command_parts[0] == 'mflo'):
        if (len(command_parts[0]) != 2):
            print('Invalid use of \'mflo\'')
            return False
            
        reg1_id = get_command_parts_R_type(command, 1)
        lo_id = registers_name_to_id['$LO']

        register_values[reg1_id] = register_values[lo_id]
                

    #INSTRUCAO 'mfhi'
    elif (command_parts[0] == 'mfhi'):
        if (len(command_parts[0]) != 2):
            print('Invalid use of \'mfhi\'')
            return False

        reg1_id = get_command_parts_R_type(command, 1)
        hi_id = registers_name_to_id['$HI']

        register_values[reg1_id] = register_values[hi_id]

    #INSTRUCAO 'jal'
    elif (command_parts[0] == 'jal'):
        if (len(command_parts) != 2):
            print('Invalid use of \'jal\'')
            return False
        
        ra_id = registers_name_to_id['$ra']
        pc_id = registers_name_to_id['$pc']
        register_values[ra_id] = register_values[pc_id] + 1
        interpret_command('j ' + command_parts[1])
    
    #INSTRUCAO 'jalr'
    elif (command_parts[0] == 'jalr'):
        reg1_id, = get_command_parts_R_type(command, 1)
        ra_id = registers_name_to_id['$ra']
        pc_id = registers_name_to_id['$pc']
        register_values[ra_id] = register_values[pc_id] + 1
        register_values[pc_id] = register_values[reg1_id] - 1

    #INSTRUCAO 'jr'
    elif (command_parts[0] == 'jr'):
        if (len(command_parts) != 2):
            print('Invalid use of \'jr\'')
            return False

        reg1_id = get_command_parts_R_type(command, 1)
        
        pc_id = registers_name_to_id['$pc']
        register_values[pc_id] = register_values[reg1_id] - 1

    #INSTRUCAO 'syscall'
    elif (command_parts[0] == 'syscall'):
        if (len(command_parts) != 1):
            print('Invalid use of \'Syscall\'. Invalidating instruction.')
            return False

        make_syscall()

    elif (command_parts[0] == "info"):
        show_info(command_parts)
        return False


    #Comando invalido ou nao implementado
    else:
        print(f'MIPS Debugger: Command not implemented or command does not exist: {command_parts[0]}')
        return False
    
    return True
    

def data_section():
    pass

def text_section():
    print("You are in the .text section.")
    while True:
        command = ''
        try:
            command = input("(MIPS Debugger) >>> ")
        except:
            print('') # Go to the next line so printing looks better.
            continue
            
        
        result = interpret_command(command)

        if (result == True):
            inserted_instructions.append(command)
            pc_id = registers_name_to_id['$pc']
            register_values[pc_id] += 1

        elif (result == "Exit_signal"):
            break


def console():
    data_section()
    text_section()

def run():
    pass

def disassemble(command_parts):
    if (len(command_parts) == 1):
        show_instructions_all()
        return

    #TODO: remover
    print('easter egg, quero me matar')
    len_command_parts = len(command_parts) 

    for i in range (1, len_command_parts):
        if (command_parts[i] not in position_of_labels.keys()):
            continue

        show_instructions_in(command_parts[i])


def make_breakpoint(command_parts):
    pass

def export_code(command_parts):
    pass

def debugger():
    while True:
        command = str(input('(MIPS Debugger) '))
        command_parts = command.split()
        if (len(command_parts) == 0):
            continue

        if (command_parts[0] == 'console'):
            console()

        elif (command_parts[0] == 'run'):
            run()

        elif (command_parts[0] == 'disassemble'): #TODO: mudar o nome pra algo que faca mais sentido
            disassemble(command_parts)

        elif (command_parts[0] == 'b' or command_parts[0] == 'breakpoint'):
            make_breakpoint(command_parts)

        elif (command_parts[0] == 'info'):
            show_info(command_parts)

        elif (command_parts[0] == 'export'):
            export_code(command_parts)

        elif (command_parts[0] == 'help'):
            pass

        elif (command_parts[0] == 'quit'):
            break

        else:
            print(f'Command \'{command_parts[0]}\' does not exist')


#Ignora o CTRL+C, o que acontece em boa parte dos terminais interativos
def sigint_handler(signum, frame):
    return

def main():
    signal.signal(signal.SIGINT, sigint_handler)
    
    print('Starting MIPS Debugger.')
    debugger()

if (__name__ == '__main__'):
    main()

#TODO: FAZER O PC FUNCIONAR
#TODO: fazer o .data section
#TODO: 



# Set the signal handler