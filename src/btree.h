#include <stdio.h>
// arquivo de dados
#define FILE_NAME "../data/table.txt"

// tamanho de cada linha
#define SIZE_DATA_LINE 41
// chaves maximas e minimas da arvore
#define MAX_KEYS 8

#define MIN_KEYS 4

// numero de linhas no arquivo
#define NUM_LINES 10000

// structs
typedef struct {
    int value;
    int line;
} Par;

typedef struct BTreeNode {
    int numKeys;
    Par keys[MAX_KEYS];
    struct BTreeNode *children[MAX_KEYS + 1];
    int isLeaf;
} BTreeNode;

typedef struct {
    BTreeNode *root;
} BTree;


// IO
Par* processaDados();

void printLineBtree(FILE *f, int line);

int printLineLinear(FILE *f, int id);

void procuraPokemon(BTree tree, int value, FILE *f);

// Arvore
BTreeNode* createNode();

void insertBTree(BTree *tree, Par par);

void printBTree(BTree *tree);

BTreeNode* searchBTree(BTree *tree, int value);

// No
void splitChild(BTreeNode *parent, int index, BTreeNode *child);

void insertNonFull(BTreeNode *node, Par par);

void printBTreeNode(BTreeNode *node);

BTreeNode* searchNode(BTreeNode *node, int value);

void deleteBTreeKey(BTree *tree, int value);
