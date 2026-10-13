#include <stdio.h> 
#include <stdlib.h>

#include "vm.h"

//#include "dizaccembler.h"


int main(){
    

    struct processor proc = {};

    
    accembler(&proc, "data.txt", "code.txt");

    for (int i = 0; i < 30; ++i) printf("%d ", proc.code[i]);
    printf("\n");
    
    vm(&proc);

    return 0;
}
