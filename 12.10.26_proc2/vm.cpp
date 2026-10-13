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
    int operation = 0;
    int x = 0;
    int pos = 0;
    while (proc->code[pos] != 0){
        operation = proc->code[pos];
        //printf("\n------------\npos - %d  noperation - %s \n", pos,  operations[operation]);
        

        //PUSH
        if (operation == 1){
            pos += 1;
            x = proc->code[pos];
            StackPush(proc->stk, x);
            h += 1;
        }

        //ADD
        if (operation == 2){
            int res = 0;
            if (h == 0){
                h = (*proc->stk).size;
            }
            for (int i = 0; i < h; ++i){
                res += StackPop(proc->stk);
            }
            StackPush(proc->stk, res);
            h = 0;
        }

        //SUB
        if (operation == 3){
            int res = 0;
            if (h == 0){
                h = (*proc->stk).size;
            }
            res = StackPop(proc->stk);
            for (int i = 1; i < h; ++i){
                res -= StackPop(proc->stk);
            }

            StackPush(proc->stk, -res);
            h = 0;
        }

        //DIV
        if (operation == 4){
            int res = 0;
            if (h == 0){
                h = (*proc->stk).size;
            }
            int * elements = (int *)calloc(h, sizeof(int));
            for (int i = 0; i < h; ++i){
                elements[i] = StackPop(proc->stk);
            }
            res = elements[h-1];
            for (int i = h-2; i >= 0; --i){
                res /= elements[i];
            }
            StackPush(proc->stk, res);
            h = 0;
        }

        //OUT
        if (operation == 5){
            int res = 0;
            res = StackPop(proc->stk);
            printf("OUT: %d\n", res);
        }

        //POPr
        if (operation == 6){
            pos += 1;
            proc->reg[proc->code[pos]] = StackPop(proc->stk);
            if (h != 0)
                h -= 1;
        }

        //PUSHr
        if (operation == 7){
            pos += 1;
            StackPush(proc->stk, proc->reg[proc->code[pos]]);
            h += 1;
        }

        //MUL
        if (operation == 8){
            //printf("h - %d\n", h);
            int res = 0;
            if (h == 0){
                h = (*proc->stk).size;
            }
            int * elements = (int *)calloc(h, sizeof(int));
            for (int i = 0; i < h; ++i){
                elements[i] = StackPop(proc->stk);
            }
            res = elements[h-1];
            for (int i = h-2; i >= 0; --i){
                res *= elements[i];
            }
            //PrintStack(&stk);
            StackPush(proc->stk, res);
            //PrintStack(&stk);
            h = 0;
        }

        //JMP
        if (operation == 9){
            pos += 1;
            pos = proc->code[pos];
            //printf("%d\n", pos);
            cnt += 1;
            pos -= 1;
            if (cnt == 4) exit(0);
        }

        //PrintStack(&stk);


        pos += 1;

    }



}
