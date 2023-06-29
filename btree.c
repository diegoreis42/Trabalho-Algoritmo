#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 4

// Structure representing a B-tree node
typedef struct BTreeNode {
    int *keys;
    struct BTreeNode **children;
    bool is_leaf;
    int num_keys;
} BTreeNode;

// Function to create a new B-tree node
BTreeNode *createNode(bool is_leaf) {
    BTreeNode *new_node = (BTreeNode *)malloc(sizeof(BTreeNode));
    new_node->keys = (int *)malloc((MAX_KEYS - 1) * sizeof(int));
    new_node->children = (BTreeNode **)malloc(MAX_KEYS * sizeof(BTreeNode *));
    new_node->is_leaf = is_leaf;
    new_node->num_keys = 0;

    for (int i = 0; i < MAX_KEYS; i++) {
        new_node->children[i] = NULL;
    }

    return new_node;
}

// Function to search for a key in the B-tree
BTreeNode *search(BTreeNode *root, int key) {
    int i = 0;
    while (i < root->num_keys && key > root->keys[i]) {
        i++;
    }

    if (i < root->num_keys && key == root->keys[i]) {
        return root;
    } else if (root->is_leaf) {
        return NULL;
    } else {
        return search(root->children[i], key);
    }
}

void splitChild(BTreeNode *parent, int index, BTreeNode *child) {
    BTreeNode *new_node = createNode(child->is_leaf);
    new_node->num_keys = MAX_KEYS / 2 - 1;

    for (int i = 0; i < new_node->num_keys; i++) {
        new_node->keys[i] = child->keys[i + MAX_KEYS / 2];
    }

    if (!child->is_leaf) {
        for (int i = 0; i < MAX_KEYS / 2; i++) {
            new_node->children[i] = child->children[i + MAX_KEYS / 2];
        }
    }

    child->num_keys = MAX_KEYS / 2 - 1;

    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = new_node;

    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[MAX_KEYS / 2 - 1];
    parent->num_keys++;
}

// Function to split a full child node during insertion
void insertNonFull(BTreeNode *node, int key) {
    int i = node->num_keys - 1;

    if (node->is_leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }

        i++;

        if (node->children[i]->num_keys == MAX_KEYS - 1) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }

        insertNonFull(node->children[i], key);
    }
}


// Function to insert a key into the B-tree
void insert(BTreeNode **root, int key) {
    BTreeNode *node = *root;
    if (node == NULL) {
        *root = createNode(true);
        (*root)->keys[0] = key;
        (*root)->num_keys = 1;
        return;
    }

    if (node->num_keys == MAX_KEYS - 1) {
        BTreeNode *new_node = createNode(false);
        new_node->children[0] = node;
        *root = new_node;
        splitChild(new_node, 0, node);
        insertNonFull(new_node, key);
    } else {
        insertNonFull(node, key);
    }
}

// Function to insert a key into a non-full node
// Function to print the B-tree in a depth-first manner
void printBTree(BTreeNode *root) {
    if (root != NULL) {
        for (int i = 0; i < root->num_keys; i++) {
            printf("%d ", root->keys[i]);
        }
        printf("\n");

        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                printBTree(root->children[i]);
            }
        }
    }
}

// Function to free the memory allocated for the B-tree
void freeBTree(BTreeNode *root) {
    if (root != NULL) {
        if (!root->is_leaf) {
            for (int i = 0; i <= root->num_keys; i++) {
                freeBTree(root->children[i]);
            }
        }
        free(root->keys);
        free(root->children);
        free(root);
    }
}

int main() {
    BTreeNode *root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 60);
    insert(&root, 70);
    insert(&root, 80);
    insert(&root, 90);
    insert(&root, 100);

    printBTree(root);

    freeBTree(root);

    return 0;
}
