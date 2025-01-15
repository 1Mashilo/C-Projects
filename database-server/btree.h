#ifndef BTREE_H
#define BTREE_H

#include <stdio.h> // Include stdio.h for FILE type

// B-tree node structure
typedef struct BTreeNode {
    int key;                // Key value
    struct BTreeNode *left; // Pointer to the left child
    struct BTreeNode *right; // Pointer to the right child
} BTreeNode;

// Function prototypes
BTreeNode* createNode(int key);
BTreeNode* insertNode(BTreeNode* root, int key);
BTreeNode* searchNode(BTreeNode* root, int key);
BTreeNode* deleteNode(BTreeNode* root, int key);
BTreeNode* minValueNode(BTreeNode* node);
void saveTree(BTreeNode* root, FILE* file);
BTreeNode* loadTree(FILE* file);
void freeTree(BTreeNode* root);

#endif // BTREE_H
