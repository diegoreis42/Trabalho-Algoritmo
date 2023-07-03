#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int main(){

    int op = 0, elem;
    BTree tree;
    tree.root = createNode();
    FILE *f = fopen(FILE_NAME, "r");

            Par *parArray = processaDados();
    do{
        printf("\nMenu: ");
        printf("\n1 - Criar indice;"
               "\n2 - Procurar elementos;"
               "\n3 - Remover registro;"
               "\n4 - Sair.\n"
               "\nOpcao: ");
        scanf("%d",&op);

        if(op == 1){
            printf("Processando...\n");
            sleep(1);

            for(int i = 0; i < 10000; i++) {
              insertBTree(&tree, parArray[i]);
            }
        }

        if(op == 2){
          scanf("%d", &elem);
          procuraPokemon(tree, elem, f);
        }

        if(op == 3){
          scanf("%d", &elem);
          deleteBTreeKey(&tree, elem);
        }
    }
    while(op != 4);


free(parArray);
fclose(f);
    return 0;
}
