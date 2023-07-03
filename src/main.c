#include "btree.h"

#include <stdio.h>
#include <stdlib.h>



int main(){

    int op = 0, elem;
    BTree tree;
    tree.root = createNode();
    FILE *f = fopen(FILE_NAME, "r");

            Par *parArray = processaDados();
            for(int i = 0; i < 10000; i++) {
              insertBTree(&tree, parArray[i]);
            }
    do{
        printf("\nMenu: ");
        printf("\n1 - Criar indice;"
               "\n2 - Procurar elementos;"
               "\n3 - Remover registro;"
               "\n4 - Sair.\n"
               "\nOpcao: ");
        scanf("%d",&op);

        if(op == 1){
        }
        if(op == 2){
            scanf("%d", &elem);
            printLineBtree(f, searchBTree(&tree, elem));
        }
        if(op == 3){
            //scanf("%s", nomeArquivo);
            //processaDados(arv, nomeArquivo, 3);// 3 = remove removeregistro()
        }
    }
    while(op != 4);
    return 0;
}
