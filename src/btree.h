/* projeto desenvolvido para a disciplina de Algoritmos
 * e Estrutura de Dados II*/
#include <stdio.h>

#ifndef BTREE_H
#define BTREE_H


#define ORDEM_MIN_BTREE 2

#define FILE_NAME "../data/table.txt"



typedef struct par{
    int chave;
    int linha;

}Par;

typedef struct no{
    int n;
    int qtdFilhos;
    
    Par *chaves;
    void **valores;
    struct no **filhos;
    
}No;

typedef struct btree{
    int ordem;
    int min;

    No *raiz; 
}Btree;

Par* processaDados();

void insere(Btree *arv, Par *parArray);
/* B-Tree */
Btree criar_btree(int ordem);

void *pesquisar_btree(Btree arv, int chave);

void inserir_btree(Btree *arv, Par chave, void *valor);

void liberar_btree(Btree *arv);

/* Nó B-Tree */
No *novo_noBtree(Btree arv);
No *novoItem_noBtree(Btree arv, Par chave, void *valor);

void mover_noBtree(No *entrada, int indiceEntrada, No *saida, int indiceSaida);

No *pesquisar_noBtree(No *raiz, int chave, int *indice);

void split_noBtree(No *raiz, Btree arv, No *novoNo, int i);

No *inserir_noBtree(No *raiz, Btree arv, Par chave, void *valor);

void liberar_noBtree(No *raiz, Btree arv);

void printBtree(No *elemento);

void liberar_um_noBtree(No *no);

#endif
