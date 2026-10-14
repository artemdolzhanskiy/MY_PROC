#include "accembler.h"

void accembler(struct processor * proc, const char * name_r, const char * name_w){
    FILE * file_r = fopen(name_r, "r");
    FILE * file_w = fopen(name_w, "w");

    
    int * jumps = (int *)calloc(10, sizeof(int));
    for (int i = 0; i < 10; ++i) jumps[i] = -1;
    pre_jump(jumps, name_r);
    
    for (int i = 0; i < 10; ++i) printf("%d ", jumps[i]);
    printf("\n");

    char operation[20] = {};
    int x = 0;
    int pos = 0;
    while (!feof(file_r)){
        fscanf(file_r, " %s", &operation);

        if (operation[0] == ':'){
            fscanf(file_r, " %d", &x);
            continue;
        }

        if (!strcmp(operation, "HLT")){
            fprintf(file_w, "0\n");
            proc->code[pos] = 0;
        }
        
        if (!strcmp(operation, "PUSH")){
            fscanf(file_r, " %d", &x);
            fprintf(file_w, "1 %d\n", x);
            proc->code[pos] = 1;
            pos += 1;
            proc->code[pos] = x;
        }

        if (!strcmp(operation, "ADD")){
            fprintf(file_w, "2\n");
            proc->code[pos] = 2;
        }

        if (!strcmp(operation, "SUB")){
            fprintf(file_w, "3\n");
            proc->code[pos] = 3;
        }

        if (!strcmp(operation, "DIV")){
            fprintf(file_w, "4\n");
            proc->code[pos] = 4;
        }

        if (!strcmp(operation, "OUT")){
            fprintf(file_w, "5\n");
            proc->code[pos] = 5;
        }

        if (!strcmp(operation, "POPr")){
            int r = 0;
            fscanf(file_r, " %d", &r);
            fprintf(file_w, "6 %d\n", r);
            proc->code[pos] = 6;
            pos += 1;
            proc->code[pos] = r;
        }

        if (!strcmp(operation, "PUSHr")){
            int r = 0;
            fscanf(file_r, " %d", &r);
            fprintf(file_w, "7 %d\n", r);
            proc->code[pos] = 7;
            pos += 1;
            proc->code[pos] = r;

        }

        if (!strcmp(operation, "MUL")){
            fprintf(file_w, "8\n");
            proc->code[pos] = 8;
        }

        if (!strcmp(operation, "JMP")){
            int pr = 0;
            fscanf(file_r, " %d", &pr);
            fprintf(file_w, "9 %d\n", pr);
            proc->code[pos] = 9;
            pos += 1;
            proc->code[pos] = jumps[pr];
        }

        if (!strcmp(operation, "JE")){
            proc->code[pos] = 10;
            pos += 1;

            int chto = 0;
            fscanf(file_r, " %d", &chto);
            proc->code[pos] = chto;

            pos += 1;
            int usl = 0;
            fscanf(file_r, " %d", &usl);
            proc->code[pos] = usl;
            
            pos += 1;
            int pr = 0;
            fscanf(file_r, " %d", &pr);
            proc->code[pos] = jumps[pr];
            
            fprintf(file_w, "10 %d %d %d\n",chto, usl, pr);

        }

        if (!strcmp(operation, "JAE")){
            proc->code[pos] = 11;
        }

        if (!strcmp(operation, "JBE")){
            proc->code[pos] = 12;
        }

        if (!strcmp(operation, "JNE")){
            proc->code[pos] = 13;
        }

        if (!strcmp(operation, "IN")){
            proc->code[pos] = 14;
        }

        if (!strcmp(operation, "CALL")){
            proc->code[pos] = 15;
        }

        if (!strcmp(operation, "RET")){
            proc->code[pos] = 16;
        }


    
        pos += 1;
    }

    fclose(file_r);
    fclose(file_w);
}


void pre_jump(int *jumps, const char * name_r){
    FILE * file_r = fopen(name_r, "r");

    int pos = 0;
    int x = 0;
    char operation[20] = {};

    while (!feof(file_r)){
        fscanf(file_r, " %s", &operation);
        //printf("%s", operation);
        
        if (!strcmp(operation, "PUSH")
         || !strcmp(operation, "PUSHr")
         || !strcmp(operation, "POPr")
         || !strcmp(operation, "JMP") ){
            fscanf(file_r, " %d", &x);
            pos += 2;
            continue;
        }

        
        if (!strcmp(operation, ":")){
            //printf("ok\n");
            fscanf(file_r, " %d", &x);
            jumps[x] = pos;
            continue;
        }

        pos += 1;

    }

    fclose(file_r);
}