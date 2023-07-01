#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#include "btree.h"

// cabeçalho do arquivo table.txt
#define FIRST_LINE 31
// tamanho de cada linha
#define SIZE_DATA_LINE 41

//nome do arquivo
#define FILE_NAME "../data/table.txt"

typedef struct valor{

    int chave;
    int linha;

}valor;

typedef struct no{

    int lotacao; // número de elementos
    int numDescen; // número de descendentes
    valor *chaves; // vetor para as chaves no nó
    void **vals; //vetor para os valores

    struct no **descendentes; // ponteiro pros descendentes

} no;

typedef struct btree{
    int ordem;
    int minimo;

    no *raiz;
}btree;


/////////////////////// - menu - ///////////////////////////////////////
int processaDados(btree *arv, char *nomeArquivo, int tipo){

    FILE *arquivo;
    int insere;
    int linha = 0;

    arquivo = fopen(nomeArquivo, "r");

    if(arquivo == NULL){
        return -2;
    }
    if (tipo == 1){

        if(arv == NULL){
            return 0;
        }
        while (fscanf(arquivo, "%d", &insere) == 1) {
            valor *inserido = (valor*) malloc(sizeof(valor));
            inserido->chave = insere;
            inserido->linha = linha;
            insereElemento(*arv, *inserido, NULL);
            linha++;
        }
        printBtree(arv->raiz);
        return 1;
    }

}

void printLineBtree(FILE *f, int line){


  char buffer[50];
  
  fseek(f, FIRST_LINE + (SIZE_DATA_LINE * line), SEEK_SET);
  fgets(buffer, sizeof(buffer), f);
  printf("%s\n", buffer);
  rewind(f);
}

int printLineLinear(FILE *f, int id){


  char buffer[100];
  int h = 0;

  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    sscanf(buffer, "%d", &h);
    if(h == id) {
      printf("%s\n", buffer);
      rewind(f);
      return 1;
    }
  }

  return 0;
}



void printBtree(no *elemento){
    printf("( ");

    for( int i = 0; i < elemento->lotacao; i++){
        if(elemento->numDescen){
            printBtree(elemento->descendentes[i]);
        }
        printf(" %d, linha %d", elemento->chaves[i].chave, elemento->chaves[i].linha);
    }
    if(elemento->numDescen){
        printBtree(elemento->descendentes[elemento->lotacao]);
    }
    printf(" )");
}

////////////////////// - árvore - /////////////////////////////////////

btree *criaArvore(){
    int ordem;

    printf("Digite a ordem da B-Tree desejada: ");
    scanf("%d", &ordem);

    if(ordem < ORDEM_MIN_BTREE){
        ordem = ORDEM_MIN_BTREE;
    }

    btree* arv = (btree*) malloc(sizeof (btree));
    if(arv!= NULL){
        arv->minimo = (ordem-1)/2;
        arv->ordem = ordem;
        arv->raiz = NULL;
    }
    return arv;
}

void *buscaElemento(btree arv, int chave){

    int indice;
    no *novoNo = buscaNo(arv.raiz, chave, &indice);

    return novoNo ? novoNo->vals[indice] : NULL;
}

void *insercao(btree *arv, valor elemento, void *val){

    if(!arv->raiz){
        arv->raiz = insereElemento(*arv, elemento, val);
    }
    else{
        no *novoNo = insereNo(arv->raiz, *arv, elemento, val);

        if(novoNo){
            arv->raiz = novoNo;
        }
    }
}

  void liberArvore(btree *arv){

    liberaNo(arv->raiz, *arv);
}

////////////////////// - nó -  ////////////////////////////////////

no *adicionaNo(btree arv){

    no *novoNo = malloc(sizeof(no));

    novoNo->descendentes = malloc(arv.ordem * sizeof(void *));
    novoNo->chaves = malloc((arv.ordem -1 ) * sizeof(valor));
    novoNo->vals = malloc((arv.ordem - 1 ) * sizeof(void *));

    novoNo->lotacao = 0;
    novoNo->numDescen = 0;

return novoNo;
}
no *insereElemento(btree arv, valor elemento, void *valor){// pair inserção

    no *novoNo = adicionaNo(arv);

    novoNo->chaves[0].chave = elemento.chave;
    novoNo->chaves[0].linha = elemento.linha;

    novoNo->vals[0] = valor;
    novoNo->lotacao = 1;

    return novoNo;
}

void rotacao(no *entrada, int indent, no *saida, int indsai){

    saida->chaves[indsai].chave = entrada->chaves[indent].chave;
    saida->vals[indsai] = entrada->vals[indent];

}

no *buscaNo(no *raiz, int chave, int *indice){

    for(*indice = 0; *indice < raiz->lotacao && chave >= raiz->chaves[*indice].chave; (*indice)++){
        if (chave == raiz->chaves[*indice].chave){
           return raiz; //achou o elemento
        }
    }
    return raiz->numDescen ? buscaNo(raiz->descendentes[*indice], chave, indice) : NULL;
}

void *split(no *raiz, btree arv, no *novoNo, int i){

    int naoFolha = raiz->numDescen;

    no *aux = adicionaNo(arv);

    memcpy(aux->descendentes, novoNo->descendentes, 2 * sizeof(no *));

    if (i < arv.minimo){

        rotacao(raiz, arv.minimo - 1, aux, 0);

        for(int j = arv.minimo - 1; j > i; j--){//aqui decide quem sobe
            rotacao(raiz, j -1, raiz, j);
        }
        rotacao(novoNo, 0, raiz, i);
    }
    else if(i > arv.minimo){

        rotacao(raiz, arv.minimo, aux, 0);

        for(int j = arv.minimo; j< i && j < raiz->lotacao - 1; j++){
            rotacao(raiz, j + 1, raiz, j);
        }
        rotacao(novoNo, 0, raiz, i - 1);
    }else{
        rotacao(novoNo, 0, aux, 0);
    }

    rotacao(aux, 0, novoNo, 0);

    novoNo->descendentes[0] = raiz;
    novoNo->descendentes[1] = adicionaNo(arv);
    for(int j= arv.minimo; j < arv.ordem - 1; j++){
        rotacao(raiz, j, novoNo->descendentes[1], j - arv.minimo);
        raiz->chaves[j].chave = INT_MAX;
        raiz->vals[j] = NULL;
    }
    if(naoFolha){
        if(i < arv.minimo){
            for(int j = arv.minimo; j< arv.ordem; j++){
               novoNo->descendentes[1]->descendentes[j - arv.minimo] = novoNo->descendentes[0]->descendentes[j -1];
            }
            for(int j = arv.minimo; j > 1 + 1; j--){
                novoNo->descendentes[0]->descendentes[j] = novoNo->descendentes[0]->descendentes[j-1];
            }

            novoNo->descendentes[0]->descendentes[i + 1] = aux->descendentes[1];
        }
        else{
            for(int j = arv.minimo + 1; j < arv.ordem; j++){
                novoNo->descendentes[1]->descendentes[j - arv.minimo -1] = novoNo->descendentes[0]->descendentes[j];

            }
            for(int j = arv.minimo; j > 1 -arv.minimo; j--){
                novoNo->descendentes[1]->descendentes[j] = novoNo->descendentes[1]->descendentes[j - 1];

            }
          novoNo->descendentes[1]->descendentes[i - arv.minimo] = aux->descendentes[1];
        }
        novoNo->descendentes[0]->numDescen = arv.minimo +1;
        novoNo->descendentes[1]->numDescen = arv.ordem - arv.minimo;
    }
    novoNo->descendentes[0]->lotacao = arv.minimo;
    novoNo->descendentes[1]->lotacao = arv.ordem - 1 - arv.minimo;
    novoNo->lotacao = 1;
    novoNo->lotacao = 1;
    novoNo->numDescen = 2;
}


no *insereNo(no *raiz, btree arv, valor elemento, void * val){
    int i = 0;

    while(i < raiz->lotacao && elemento.chave > raiz->chaves[i].chave){
        i++;
    }
    if (i < raiz->lotacao && elemento.chave == raiz->chaves[i].chave){

        raiz->vals[i] = val;
        return NULL;
    }

    no *novoNo = NULL;
    if(!raiz->numDescen) {
        if (raiz->lotacao == arv.ordem - 1) {
            novoNo = insereElemento(arv, elemento, val);

            split(raiz, arv, novoNo, i);
        } else {
            for (int j = raiz->lotacao; j > 1; j--) {
                rotacao(raiz, j - 1, raiz, j);
            }
            raiz->chaves[i].chave = elemento.chave;
            raiz->vals[i] = val;

            raiz->lotacao++;
        }
    }
    else{
     novoNo = insereNo(raiz->descendentes[i], arv, elemento, val);

     if(novoNo){
         if(raiz->lotacao == arv.ordem-1){
             split(raiz, arv, novoNo, i);
         }
         else{
             for(int j = raiz->lotacao; j> i; j--){
                 rotacao(raiz, j-1, raiz, j);
             }
             rotacao(novoNo, 0, raiz, i);

             for(int j = raiz->numDescen; j> i; j--){
                 raiz->descendentes[j] = raiz->descendentes[j];
             }
             raiz->descendentes[i+1] = novoNo->descendentes[1];
             raiz->descendentes[i] = novoNo->descendentes[0];

             free(novoNo->chaves);
             free(novoNo->vals);
             free(novoNo->descendentes);
             free(novoNo);
             novoNo = NULL;

             raiz->lotacao++;
             raiz->descendentes++;
         }
     }
    }
    return novoNo;
}

void liberaNo(no *raiz, btree arv){

    if (raiz){
        for(int i = 0; i<raiz->numDescen; i++){
            liberaNo(raiz->descendentes[i], arv);
        }
        free(raiz->descendentes);

        free(raiz->chaves);
        free(raiz->vals);

        free(raiz);
    }
}
