#include <stdio.h>
#define FILE_NAME "../data/table.txt"
// tamanho de cada linha
#define SIZE_DATA_LINE 41

#define MAX_KEYS 5

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



Par* processaDados();

void printLineBtree(FILE *f, int line);

int printLineLinear(FILE *f, int id);


BTreeNode* createNode();
void splitChild(BTreeNode *parent, int index, BTreeNode *child);
void insertNonFull(BTreeNode *node, Par par);
void insertBTree(BTree *tree, Par par);
void printBTreeNode(BTreeNode *node);
void printBTree(BTree *tree);
BTreeNode* searchNode(BTreeNode *node, int value);
BTreeNode* searchBTree(BTree *tree, int value);
void procuraPokemon(BTree tree, int value, FILE *f);
