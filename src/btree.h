/* projeto desenvolvido para a disciplina de Algoritmos
 * e Estrutura de Dados II*/

#include <stdio.h>

#define ORDEM_MIN_BTREE 2

#define FILE_NAME "../data/table.txt"

typedef struct valor valor;

typedef struct no no;

typedef struct btree btree;




/////////////////////// - menu - ///////////////////////////////////////

int processaDados(btree *arv, char *nomeArquivo, int tipo);

void printBtree(no *elemento);

void printLineBtree(FILE *f, int line);

int printLineLinear(FILE *f, int id);

////////////////////// - árvore - /////////////////////////////////////

btree *criaArvore();

void *buscaElemento(btree arv, int chave);

void *insercao(btree *arv, valor elemento, void *val);

void liberArvore(btree *arv);

////////////////////// - nó -  ////////////////////////////////////

no *adicionaNo(btree arv);

no *insereElemento(btree arv, valor chave, void *valor);

void rotacao(no *entrada, int indent, no *saida, int indsai);

no *buscaNo(no *raiz, int chave, int *indice);

void *split(no *raiz, btree arv, no *novoNo, int i);

no *insereNo(no *raiz, btree arv, valor chave, void * val);

void liberaNo(no *raiz, btree arv);


