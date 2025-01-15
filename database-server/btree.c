// btree.c
#include "btree.h"
#include "database.h"
#include <stdlib.h>
#include <stdio.h>

// Function to create a new node
BTreeNode* createNode(int key) {
    BTreeNode* newNode = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (!newNode) {
        fprintf(stderr, "Failed to allocate memory for new node\n");
        return NULL;
    }
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the binary tree
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

// Function to search for a key in the binary tree
BTreeNode* searchNode(BTreeNode* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (key < root->key) {
        return searchNode(root->left, key);
    }
    return searchNode(root->right, key);
}

// Function to delete a key from the binary tree
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

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        BTreeNode* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Function to find the minimum value node in a binary tree
BTreeNode* minValueNode(BTreeNode* node) {
    BTreeNode* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Function to save the binary tree to a file
void saveTree(BTreeNode* root, FILE* file) {
    if (root == NULL) {
        return;
    }
    fprintf(file, "%d\n", root->key);
    saveTree(root->left, file);
    saveTree(root->right, file);
}

// Function to load the binary tree from a file
BTreeNode* loadTree(FILE* file) {
    int key;
    BTreeNode* root = NULL;
    while (fscanf(file, "%d", &key) != EOF) {
        root = insertNode(root, key);
    }
    return root;
}

// Function to free the entire binary tree
void freeTree(BTreeNode* root) {
    if (root == NULL) {
        return;
    }
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
