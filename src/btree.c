
#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 4
#define FILE_NAME "../data/table.txt"

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

Par* processaDados() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        return NULL;
    }

    int maxLines = 10000;  // Maximum number of lines
    Par *parArray = (Par *)malloc(maxLines * sizeof(Par));
    if (parArray == NULL) {
        fclose(file);
        return NULL;
    }

    int lineNumber = 0;
    char line[60];
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &(parArray[lineNumber].value));
        parArray[lineNumber].line = lineNumber;
        lineNumber++;
    }

    fclose(file);
    return parArray;
}


BTreeNode* createNode() {
    BTreeNode *newNode = (BTreeNode *)malloc(sizeof(BTreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->numKeys = 0;
    newNode->isLeaf = 1;

    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }

    return newNode;
}

void splitChild(BTreeNode *parent, int index, BTreeNode *child) {
    BTreeNode *newNode = createNode();
    newNode->isLeaf = child->isLeaf;
    newNode->numKeys = MAX_KEYS / 2;

    for (int i = 0; i < newNode->numKeys; i++) {
        newNode->keys[i] = child->keys[i + MAX_KEYS / 2];
    }

    if (!child->isLeaf) {
        for (int i = 0; i < (MAX_KEYS / 2) + 1; i++) {
            newNode->children[i] = child->children[i + MAX_KEYS / 2];
        }
    }

    child->numKeys = MAX_KEYS / 2;

    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[MAX_KEYS / 2 - 1];
    parent->numKeys++;
}

void insertNonFull(BTreeNode *node, Par par) {
    int i = node->numKeys - 1;

    if (node->isLeaf) {
        while (i >= 0 && par.value < node->keys[i].value) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = par;
        node->numKeys++;
    } else {
        while (i >= 0 && par.value < node->keys[i].value) {
            i--;
        }

        i++;

        if (node->children[i]->numKeys == MAX_KEYS) {
            splitChild(node, i, node->children[i]);

            if (par.value > node->keys[i].value) {
                i++;
            }
        }

        insertNonFull(node->children[i], par);
    }
}

void insertBTree(BTree *tree, Par par) {
    BTreeNode *root = tree->root;

    if (root->numKeys == MAX_KEYS) {
        BTreeNode *newNode = createNode();
        newNode->isLeaf = 0;
        newNode->children[0] = root;
        tree->root = newNode;
        splitChild(newNode, 0, root);
        insertNonFull(newNode, par);
    } else {
        insertNonFull(root, par);
    }
}

void printBTreeNode(BTreeNode *node) {
    for (int i = 0; i < node->numKeys; i++) {
        printf("Value: %d, Line: %d\n", node->keys[i].value, node->keys[i].line);
    }

    if (!node->isLeaf) {
        for (int i = 0; i <= node->numKeys; i++) {
            printBTreeNode(node->children[i]);
        }
    }
}

void printBTree(BTree *tree) {
    if (tree->root != NULL) {
        printBTreeNode(tree->root);
    }
}

int main() {
    BTree tree;
    tree.root = createNode();

    Par *parArray = processaDados();

    for(int i = 0; i < 10000; i++){
      insertBTree(&tree, parArray[i]);
    }

    printBTree(&tree);

    return 0;
}

