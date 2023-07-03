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

            for(int i = 0; i < NUM_LINES; i++) {
              insertBTree(&tree, parArray[i]);
            }
        }

        if(op == 2){
          printf("Insira indice do pokemon: ");
          scanf("%d", &elem);
          printf("\n");
          
          procuraPokemon(tree, elem, f);
        }

        if(op == 3){
          printf("Insira indice do pokemon: ");
          scanf("%d", &elem);

          if(elem <= 0 || elem > NUM_LINES){
            printf("\nIndice invalido\n");
            continue;
          }

          deleteBTreeKey(&tree, elem);
          printf("Pokemon deletado com sucesso!\n");
        }
    }
    while(op != 4);


free(parArray);
fclose(f);
    return 0;
}
