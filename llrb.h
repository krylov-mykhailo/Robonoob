#ifndef LLRB_H
#define LLRB_H

#include <stdbool.h>

#define RED 1
#define BLACK 0

typedef struct Node {
    int key;
    int color;
    struct Node *left, *right;
} Node;

// Core LLRB functions
Node* insert(Node* h, int key);
void freeTree(Node* root);

// Testing functions
bool test_LLRBProperties(Node* root);
bool test_LLRBBalance(Node* root);

// Helper
bool isBST(Node* root);
bool isBalanced(Node* root, int* blackHeight);
bool noDoubleRed(Node* root);
bool redLinksLeanLeft(Node* root);
bool isBST(Node* root);
#endif