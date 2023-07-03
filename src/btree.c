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
        return node;
    }

    if (node->isLeaf) {
        return NULL;
    }

    return searchNode(node->children[i], value);
}

void procuraPokemon(BTree tree, int value, FILE *f){

  BTreeNode *achou = searchNode(tree.root, value);

  if (achou != NULL) {
    for (int i = 0; i < achou->numKeys; i++) {
      if(achou->keys[i].value == value) {
        Par *par = &(achou->keys[i]);
        printLineBtree(f, par->line);
        break;
      }
    }

  } else {
      printf("404 - Not found\n");
    }

}

Par mergeNodes(BTreeNode *node, int mergeChildIndex) {
    BTreeNode *leftChild = node->children[mergeChildIndex];
    BTreeNode *rightChild = node->children[mergeChildIndex + 1];

    // Move the key from the parent to the left child
    leftChild->keys[leftChild->numKeys] = node->keys[mergeChildIndex];
    leftChild->numKeys++;

    // Move the keys from the right child to the left child
    for (int i = 0; i < rightChild->numKeys; i++) {
        leftChild->keys[leftChild->numKeys + i] = rightChild->keys[i];
    }

    // Move the child pointers from the right child to the left child (if applicable)
    if (!leftChild->isLeaf) {
        for (int i = 0; i <= rightChild->numKeys; i++) {
            leftChild->children[leftChild->numKeys + i] = rightChild->children[i];
        }
    }

    // Adjust the parent node keys and child pointers
    for (int i = mergeChildIndex; i < node->numKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
        node->children[i + 1] = node->children[i + 2];
    }

    node->numKeys--;

    // Deallocate memory for the right child node
    free(rightChild);

    // Return the key that was moved from the parent to the left child
    return node->keys[mergeChildIndex];
}

void adjustChild(BTreeNode *node, int childIndex) {
    BTreeNode *leftChild = node->children[childIndex - 1];
    BTreeNode *rightChild = node->children[childIndex + 1];

    if (childIndex > 0 && leftChild->numKeys > MIN_KEYS) {
        // Borrow a key from the left sibling
        BTreeNode *child = node->children[childIndex];
        for (int i = child->numKeys; i > 0; i--) {
            child->keys[i] = child->keys[i - 1];
        }
        child->keys[0] = node->keys[childIndex - 1];
        node->keys[childIndex - 1] = leftChild->keys[leftChild->numKeys - 1];

        if (!child->isLeaf) {
            for (int i = child->numKeys + 1; i > 0; i--) {
                child->children[i] = child->children[i - 1];
            }
            child->children[0] = leftChild->children[leftChild->numKeys];
        }

        leftChild->numKeys--;
        child->numKeys++;
    } else if (childIndex < node->numKeys && rightChild->numKeys > MIN_KEYS) {
        // Borrow a key from the right sibling
        BTreeNode *child = node->children[childIndex];
        child->keys[child->numKeys] = node->keys[childIndex];
        node->keys[childIndex] = rightChild->keys[0];

        if (!child->isLeaf) {
            child->children[child->numKeys + 1] = rightChild->children[0];
        }

        for (int i = 0; i < rightChild->numKeys - 1; i++) {
            rightChild->keys[i] = rightChild->keys[i + 1];
        }

        if (!rightChild->isLeaf) {
            for (int i = 0; i < rightChild->numKeys; i++) {
                rightChild->children[i] = rightChild->children[i + 1];
            }
        }

        rightChild->numKeys--;
        child->numKeys++;
    } else {
        // Merge the child node with its adjacent sibling
        if (childIndex > 0) {
            // Merge with the left sibling
            mergeNodes(node, childIndex - 1);
        } else {
            // Merge with the right sibling
            mergeNodes(node, childIndex);
        }
    }
}



void deleteKeyFromNode(BTreeNode *node, int value);

void deleteBTreeKey(BTree *tree, int value) {
    if (tree->root == NULL) {
        printf("B-tree is empty.\n");
        return;
    }

    deleteKeyFromNode(tree->root, value);

    // If the root becomes empty, replace it with its only child
    if (tree->root->numKeys == 0) {
        BTreeNode *oldRoot = tree->root;
        tree->root = tree->root->children[0];
        free(oldRoot);
    }
}

void deleteKeyFromNode(BTreeNode *node, int value) {
    int i = 0;

    while (i < node->numKeys && value > node->keys[i].value) {
        i++;
    }

    if (i < node->numKeys && value == node->keys[i].value) {
        // Key found in the current node

        if (node->isLeaf) {
            // Key found in a leaf node, remove it
            for (int j = i; j < node->numKeys - 1; j++) {
                node->keys[j] = node->keys[j + 1];
            }
            node->numKeys--;
        } else {
            // Key found in an internal node
            BTreeNode *leftChild = node->children[i];
            BTreeNode *rightChild = node->children[i + 1];

            if (leftChild->numKeys >= MIN_KEYS) {
                // Find the predecessor and replace the key with it
                BTreeNode *predecessor = leftChild;
                while (!predecessor->isLeaf) {
                    predecessor = predecessor->children[predecessor->numKeys];
                }
                node->keys[i] = predecessor->keys[predecessor->numKeys - 1];

                // Recursively delete the predecessor from the left child
                deleteKeyFromNode(leftChild, predecessor->keys[predecessor->numKeys - 1].value);
            } else if (rightChild->numKeys >= MIN_KEYS) {
                // Find the successor and replace the key with it
                BTreeNode *successor = rightChild;
                while (!successor->isLeaf) {
                    successor = successor->children[0];
                }
                node->keys[i] = successor->keys[0];

                // Recursively delete the successor from the right child
                deleteKeyFromNode(rightChild, successor->keys[0].value);
            } else {
                // Merge the key and its right sibling into one node
                node->keys[i] = mergeNodes(node, i);

                // Recursively delete the key from the merged node
                deleteKeyFromNode(node->children[i], value);
            }
        }
    } else {
        // Key not found in the current node, go to the appropriate child node
        BTreeNode *child = node->children[i];

        if (child->numKeys == MIN_KEYS) {
            // Perform necessary adjustments before going to the child node
            adjustChild(node, i);
        }

        deleteKeyFromNode(child, value);
    }
}
