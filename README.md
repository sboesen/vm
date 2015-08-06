# VM

This is a single file VM written in C. Lexing/parsing isn't implemented, but it takes instructions and eval()'s them in a big switch statement until it gets a HLT. Currently the program is compiled into the interpreter, but passing it via arguments would be trivial given a lexer that spits out the proper instruction/data values.

Instruction set is currently:

PSH, // 1 arg, value  
POP, // 1 arg, register  
SET, // 2 arg, value, register  
MOV, // 2 arg, register, register  
ADD, // 0 arg  
DSP, // 1 arg, register  
CMP, // 2 args, register, register  
JEQ, // 1 arg, int # instructions to jump  
INP, // 1 arg, register  
HLT, // 0 arg  

which are all in an enum. Example program is in the `program` constant
