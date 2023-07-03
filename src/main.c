#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



int main(){

    Btree arv = criar_btree(3);
    Par *parArray = processaDados();
    
    insere(&arv, parArray);
  
    printBtree(arv.raiz);
    
    printf("\n");

    return 0;
}
