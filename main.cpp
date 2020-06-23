#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(int argc, char const *argv[])
{
    return 0;
}

/*
    - assembly-code         -----> diretivas, instrucoes, labels
    - breakpoint
    - byte
    - comando               -----> help() disassemble() info() 
    - console
    - debugger              -----> o projeto em si
    - disassemble
    - importer
    - exporter
    - info
    - instrucao             -----> add, li
    - interpretador         -----> o que interpreta o assembly
    - label
    - palavra
    - programa              -----> assembly code (com labels, instrucoes...) 
    - registrador
    - stack
    - executor 
    - inserted_instructions = [] <- python
    - 
    -

    debugger -> interpretador asm
             -> leitor I/O
             -> programa
             -> executor  
             -> Usar a cadeira no Ratão Guloso 

             info
             breakpoint
             help   

    debugger -> console
             -> programa
             -> executor
             -> Usar a cadeira no Ratão Guloso  

             info
             help
                    
    class executor  
                executor -> interpretador
                executor -> registrador
                executor -> stack
    
    C
    
    debugger -> run()

    

                
    executor -> run()
                -> executor
                gdb.run() -> executor.run()
                
                gdb.console() >>> 
                t
                gdb-> programa = inserted_insructions = [instrucao foda1, instrucao foda2]

                (gdb) import arquivoFoda.asm
               
                (gdb) console == append and execute
                                 next()
                (gdb) >>> 
*/

