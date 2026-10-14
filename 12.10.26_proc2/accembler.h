#ifndef ACCEMBLER_H
#define ACCEMBLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

enum proc_operation{
    HLT   = 0,
    PUSH  = 1,
    ADD   = 2,  // +
    SUB   = 3,  // -
    DIV   = 4,  // /
    OUT   = 5,
    POPr  = 6,
    PUSHr = 7,
    MUL   = 8,  // *
    JMP   = 9,
    JE    = 10,  // ==
    JAE   = 11, // >=
    JBE   = 12, // <=
    JNE   = 13, // !=
    IN    = 14, 
    CALL  = 15,
    RET   = 16,
};

struct processor{
    int code[50];
    int reg[10];
    struct stack * stk;
};

void accembler(struct processor * proc, const char * name_r, const char * name_w);
void pre_jump(int *jumps, const char * name_r);

#endif