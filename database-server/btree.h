#ifndef BTREE_H
#define BTREE_H

typedef struct BTreeNode {
    int key;
    struct BTreeNode *left;
    struct BTreeNode *right;
} BTreeNode;

BTreeNode* createNode(int key);
BTreeNode* insertNode(BTreeNode* root, int key);
BTreeNode* deleteNode(BTreeNode* root, int key);
BTreeNode* searchNode(BTreeNode* root, int key);
void freeTree(BTreeNode* root);

#endif // BTREE_H
