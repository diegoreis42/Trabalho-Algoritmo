#include <stdio.h>

#include "btree.h"

int main(){
    btree *arv;
    int op;
    char nomeArquivo[30];

    do{
        printf("\nMenu: ");
        printf("\n1 - Criar indice;"
               "\n2 - Procurar elementos;"
               "\n3 - Remover registro;"
               "\n4 - Sair.\n"
               "\nOpcao: ");
        scanf("%d", &op);

        if(op == 1){

            arv = criaArvore();
            processaDados(arv, FILE_NAME, 1);
        }
        if(op == 2){
            //scanf("%s", nomeArquivo);
            //processaDados(arv, nomeArquivo, 2);// 2 = busca buscaElemento();
            //
        }
        if(op == 3){
            //scanf("%s", nomeArquivo);
            //processaDados(arv, nomeArquivo, 3);// 3 = remove removeregistro()
        }
    }
    while(op != 4);
    liberArvore(arv);
    return 0;
}
