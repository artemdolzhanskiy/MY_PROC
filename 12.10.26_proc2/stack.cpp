#include "stack.h"




void StackCheck(struct stack * stk, const char * name, const char* file, int line){
    if (stk->capacity < 0){
        stk->err = CAPACITY_PIZDEC;
        printf("\nERROR!\n");
        printf("in %s in line %d in %s capacity < 0\n", file, line, name);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
    if (stk->capacity < stk->size){
        stk->err =SIZE_PIZDEC;
        printf("\nERROR!\n");
        printf("in %s in line %d in %s capacity < size\n", file, line, name);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
    if (stk->capacity == stk->size){
        stk->err = NE_PUSH;
        printf("\nWARNING!\n");
        printf("in %s in line %d in %s srack full: size = capacity = %d\n", file, line, name, stk->size);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
    
    if (*stk->l_canary != 0x3143DA){
        stk->err = L_CANARY_PIZDEC;
        printf("\nRROR!\n");
        printf("in %s in line %d in %s l_canary not 0x3143DA\n", file, line, name);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
    if (*stk->r_canary != 0x3143DA){
        stk->err = R_CANARY_PIZDEC;
        printf("\nERROR!\n");
        printf("in %s in line %d in %s r_canary not 0x3143DA\n", file, line, name);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
}

void StackRecalloc(struct stack * stk, int new_capacity ON_DEBUG(,const char * name, const char* file, int line ) ){

    ON_DEBUG(
    if (new_capacity < 0){
        stk->err = CAPACITY_PIZDEC;
        printf("\n[STACK_DEBUG] ERROR!\n");
        printf("in file %s in line %d in %s capacity < 0\n", file, line, name);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
    if (stk->capacity < 0){
        stk->err = CAPACITY_PIZDEC;
        printf("\n[STACK_DEBUG] ERROR!\n");
        printf("in file %s in line %d in %s capacity < 0\n", file, line, name);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
    )

    FILE * file_operations = fopen(stk->name_file_oprations, "a");
    fprintf(file_operations,"StackRecalloc of [%s]: capacity before - %d, after - %d \n\n", stk->stack_name, stk->capacity, new_capacity);
    fclose(file_operations);

    stk->size = fmin(stk->size, new_capacity);

    stack_elem * data_save = (stack_elem*)(calloc(stk->size, sizeof(stack_elem)));
    for (int i = 0; i < stk->size; ++i){
        data_save[i] = stk->data[i];
    }

    stk->capacity = new_capacity;

    free(stk->data_p);

    stk->data_p = (stack_elem*)(calloc(new_capacity + 2, sizeof(stack_elem)));
    

    stk->l_canary = stk->data_p;
    stk->data = stk->data_p + 1;
    stk->r_canary = stk->data_p + new_capacity + 1;

    stk->err = OK;

    for (int i = 0; i < stk->size; ++i){
        stk->data[i] = data_save[i];
    }

    *stk->l_canary = 0x3143DA;
    *stk->r_canary = 0x3143DA;

    free((void*)data_save);


    StackCheck(stk, __func__, __FILE__, __LINE__ );
}

void StackInit(struct stack * stk, int capacity ON_DEBUG(,const char * name, const char* file, int line ) ){
    
    ON_DEBUG(
    if (capacity < 0){
        stk->err = CAPACITY_PIZDEC;
        printf("\n[STACK_DEBUG] ERROR!\n");
        printf("in file %s in line %d in %s capacity < 0\n", file, line, name);
        printf("DOLZHANSKIYlib soboleznuet\n\n");
        exit(0);
    }
    )

    FILE * file_operations = fopen(stk->name_file_oprations, "a");
    fprintf(file_operations,"StackInit of [%s]: capacity - %d \n\n", stk->stack_name, capacity);
    fclose(file_operations);

    stk->size = 0;
    stk->capacity = capacity;

    stk->data_p = (stack_elem*)(calloc(capacity+2, sizeof(stack_elem)));
    stk->l_canary = stk->data_p;
    stk->data = stk->data_p + 1;
    stk->r_canary = stk->data_p + capacity + 1;

    stk->err = OK;

    *stk->l_canary = 0x3143DA;
    *stk->r_canary = 0x3143DA;
}
// 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
// 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F

void StackPush(struct stack * stk, stack_elem value){
    
    if (stk->capacity == stk->size){
        StackRecalloc(stk, stk->size + 1 ON_DEBUG(,__func__, __FILE__, __LINE__ ) );
    }

    
    stk->data[stk->size++] = value;
    assert(stk->err == OK);

    FILE * file_operations = fopen(stk->name_file_oprations, "a");
    fprintf(file_operations,"StackPush of [%s]: new front element - %d, new size - %d \n\n", stk->stack_name, value, stk->size);
    fclose(file_operations);

}


stack_elem StackPop(struct stack * stk){

       
    stack_elem res = stk->data[stk->size-1];
    stk->data[stk->size-1] = 0;
    stk->size -= 1;

    FILE * file_operations = fopen(stk->name_file_oprations, "a");
    fprintf(file_operations,"StackPop of [%s]: front element - %d, new size - %d \n\n", stk->stack_name, res, stk->size);
    fclose(file_operations);
 
    return res;
}

void PrintStack(struct stack * stk){
    printf("\ninfo about stack:\n");
    printf("capacity = %d\n", stk->capacity);
    printf("size = %d\n", stk->size);

    printf("front elem<----------------------------\n");
    if (stk->size == 0) 
        printf("no elem in stack");
    for (int i = stk->size - 1; i >= 0; --i) printf("%d ", stk->data[i]);
    printf("\n");

    if (stk->err == OK) printf("error - OK");
    if (stk->err == CAPACITY_PIZDEC) printf("error - CAPACITY_PIZDEC");
    if (stk->err == SIZE_PIZDEC) printf("error - SIZE_PIZDEC");
    if (stk->err == MEMORY_PIZDEC) printf("error - MEMORY_PIZDEC"); 

    printf("\n");
}




void StackDestroy(struct stack * stk ON_DEBUG(,const char * name, const char* file, int line ) ){
    free((void*)stk->capacity);
    free((void*)stk->size);
    free((void*)stk->data);
    free((void*)stk->err);
    free(stk);
}
