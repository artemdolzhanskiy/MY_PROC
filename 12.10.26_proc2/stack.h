#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

//#define STACK_DEBUG

typedef int stack_elem;


#ifdef STACK_DEBUG
#define ON_DEBUG(...) __VA_ARGS__
#else
#define ON_DEBUG(...) 
#endif





enum stack_error {OK = 0,
     CAPACITY_PIZDEC = 1,
         SIZE_PIZDEC = 2,
       MEMORY_PIZDEC = 3, 
             NE_PUSH = 4,
     L_CANARY_PIZDEC = 5,
     R_CANARY_PIZDEC = 6};



struct stack{
    stack_elem* data_p;
    char name_file_oprations[20];
    char stack_name[20];
    int line;
    int* l_canary;
    int* r_canary;
    stack_elem * data;
    int capacity;
    int size;
    enum stack_error err;
};

void StackCheck(struct stack * stk, const char * name, const char* file, int line );

void StackRecalloc(struct stack * stk, int new_capacity ON_DEBUG(,const char * name, const char* file, int line ) );

void StackInit(struct stack * stk, int capacity ON_DEBUG(,const char * name, const char* file, int line ) );

void StackPush(struct stack * stk, stack_elem value  );

stack_elem StackPop(struct stack * stk );

void StackDestroy(struct stack * stk ON_DEBUG(,const char * name, const char* file, int line ) );

void PrintStack(struct stack * stk);


#endif