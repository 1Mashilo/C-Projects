#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

BTreeNode* createNode(int key) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BTreeNode* insertNode(BTreeNode* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key);
    }
    return root;
}

BTreeNode* searchNode(BTreeNode* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}

BTreeNode* minValueNode(BTreeNode* node) {
    BTreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

BTreeNode* deleteNode(BTreeNode* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (root->left == NULL) {
            BTreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BTreeNode* temp = root->left;
            free(root);
            return temp;
        }
        BTreeNode* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void freeTree(BTreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
