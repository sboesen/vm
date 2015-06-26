#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
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
  PRINT
} InstructionSet;

typedef enum {
  A,
  B,
  C,
  D,
  E,
  F,
  IP,
  SP,
  FLAGS,
  NUM_OF_REGISTERS
} Registers;

#define pop() (stack[sp--])
#define ip (registers[IP])
#define sp (registers[SP])

#define zro_bit 0x0001


const int program[] = {
  PSH, 6,
  POP, A,
  MOV, A, B,
  CMP, A, B,
  JEQ, 4,
  DSP, A,
  DSP, B,
  HLT
};

int registers[NUM_OF_REGISTERS];

int stack[256];
bool running = true;


void eval(int instr) {
  //printf("Evaluating inst %d, ip == %d, sp == %d\n", instr, ip, sp);
  switch (instr) {
  case HLT: {
    running = false;
    break;
  }
  case PSH: {
    stack[++sp] = program[++ip];
    break;
  }
  case ADD: {
    int a = pop();
    int b = pop();
    stack[++sp] = a + b;
    break;
  }
  case POP: {
    int reg = program[++ip];
    int value = pop();
    registers[reg] = value;
    break;
  }
  case DSP: {
    int reg = program[++ip];
    printf("DSP: %d\n", registers[reg]);
    break;
  }
  case CMP: {
    int reg1 = registers[program[++ip]];
    int reg2 = registers[program[++ip]];
    if (reg1 == reg2) {
      registers[FLAGS] = 1;
    } else {
      registers[FLAGS] = 0;
    }
    break;
  }
  case JEQ: {
    int eql = registers[FLAGS];
    int jump_offset = program[++ip];
    if (eql) {
      ip += jump_offset;
    }
    break;
  }
  case INP: {
    int user_int;
    printf("Give me an int, please: ");
    scanf("%d", &user_int);
    registers[program[++ip]] = user_int;
    break;
  }
  case MOV: {
    int src_reg = program[++ip];
    int dest_reg = program[++ip];
    registers[dest_reg] = registers[src_reg];
    break;
  }
  case SET: {
    int dest_reg = program[++ip];
    int value = program[++ip];
    registers[dest_reg] = value;
    break;
  }

  }
}

int fetch() {
  return program[ip];
}


int main() {
  while (running) {
    eval(fetch());
    ip++;
  }
  return 0;
}
