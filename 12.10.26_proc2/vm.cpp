#include "vm.h"

char operations[10][6] = {
    "HLT",  // 0
    "PUSH", // 1
    "ADD",  // 2
    "SUB",  // 3
    "DIV",  // 4
    "OUT",  // 5
    "POPr", // 6
    "PUSHr",// 7
    "MUL",  // 8
    "JMP",  // 9
};

void vm(struct processor * proc){

    
    struct stack stk = {};
    StackInit(&stk, 100);
    proc->stk = &stk;

    int cnt = 0;

    int h = 0;
    enum proc_operation operation = HLT;
    int x = 0;
    int pos = 0;
    int res = 0;
    int * elements = (int *)calloc(20, sizeof(int));
    int chto = 0, usl = 0, cuda = 0;

    while (proc->code[pos] != 0){
        operation = (enum proc_operation)proc->code[pos];
        //printf("\n------------\npos - %d  noperation - %s \n", pos,  operations[operation]);
        

        //printf("operation - %d\n", operation);
        switch (operation){
            case PUSH:
                pos += 1;
                x = proc->code[pos];
                StackPush(proc->stk, x);
                h += 1;
                break;


            case ADD:
                res = 0;
                if (h == 0){
                    h = (*proc->stk).size;
                }
                for (int i = 0; i < h; ++i){
                    res += StackPop(proc->stk);
                }
                StackPush(proc->stk, res);
                h = 0;
                break;


            
            case SUB:
                res = 0;
                if (h == 0){
                    h = (*proc->stk).size;
                }
                res = StackPop(proc->stk);
                for (int i = 1; i < h; ++i){
                    res -= StackPop(proc->stk);
                }

                StackPush(proc->stk, -res);
                h = 0;
                break;

            
            case DIV:
                res = 0;
                if (h == 0){
                    h = (*proc->stk).size;
                }
                for (int i = 0; i < h; ++i){
                    elements[i] = StackPop(proc->stk);
                }
                res = elements[h-1];
                for (int i = h-2; i >= 0; --i){
                    res /= elements[i];
                }
                StackPush(proc->stk, res);
                h = 0;
                break;

            
            case OUT:
                res = 0;
                res = StackPop(proc->stk);
                printf("OUT: %d\n", res);
                break;

            
            case POPr:
                pos += 1;
                proc->reg[proc->code[pos]] = StackPop(proc->stk);
                if (h != 0)
                    h -= 1;
                break;

            
            case PUSHr:
                pos += 1;
                StackPush(proc->stk, proc->reg[proc->code[pos]]);
                h += 1;
                break;

            
            case MUL:
                //PrintStack(proc->stk);
                res = 0;
                if (h == 0){
                    h = (*proc->stk).size;
                }
                //printf("h - %d\n", h);
                for (int i = 0; i < h; ++i){
                    elements[i] = StackPop(proc->stk);
                }
                res = elements[h-1];
                for (int i = h-2; i >= 0; --i){
                    res *= elements[i];
                }
                StackPush(proc->stk, res);
                h = 0;
                break;

            
            case JMP:
                pos += 1;
                pos = proc->code[pos];
                //printf("%d\n", pos);
                cnt += 1;
                pos -= 1;
                break;

            case JE:
                pos += 1;
                chto = proc->code[pos];
                pos += 1;
                usl = proc->code[pos];
                pos += 1;
                cuda = proc->code[pos];
                //printf("%d %d %d %d\n", chto, proc->reg[chto], usl, cuda);


                if (proc->reg[chto] == usl)
                    pos = cuda - 1;
                break;

        }

        //PrintStack(&stk);


        pos += 1;

    }



}
