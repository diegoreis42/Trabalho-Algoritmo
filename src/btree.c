#include <stdio.h>
#include <stdlib.h>
#include "btree.h"


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
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%d", &(parArray[lineNumber].value));
        parArray[lineNumber].line = lineNumber;

        printf("Linha: %d Valor: %d\n", parArray[lineNumber].line, parArray[lineNumber].value);
        lineNumber++;
    }

    fclose(file);
    return parArray;
}

void printLineBtree(FILE *f, int line) {
  char buffer[50];

  fseek(f, (SIZE_DATA_LINE * line), SEEK_SET);
  fgets(buffer, sizeof(buffer), f);
  printf("%s\n", buffer);
  rewind(f);
}

int printLineLinear(FILE *f, int id) {
  char buffer[50];
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




BTreeNode* searchNode(BTreeNode* node, int value) {
    int i = 0;

    while (i < node->numKeys && value > node->keys[i].value) {
        i++;
    }

    if (i < node->numKeys && value == node->keys[i].value) {
      printf("erro aqui\n");
        return node;
    }

    if (node->isLeaf) {
        return NULL;
    }

    return searchNode(node->children[i], value);
}


int main (int argc, char *argv[])
{
  Par *parArray = processaDados();
  int value = 6184;

  BTree tree;
    tree.root = createNode();

 for(int i = 0; i < 10000; i++) {
        printf("Linha Entrada BTree: %d Valor: %d\n", parArray[i].line, parArray[i].value);
              insertBTree(&tree, parArray[i]);
            }
  BTreeNode *achou = searchNode(tree.root, value);

  if (achou != NULL) {
    for (int i = 0; i < achou->numKeys; i++) {
      if(achou->keys[i].value == value) {
        Par *par = &(achou->keys[i]);
        printf("Found Par: value=%d, line=%d\n", par->value, par->line);             
        break;
      }
    }

  } else {
      printf("F\n");
    }





  free(parArray);
  free(achou);
  return 0;
}
