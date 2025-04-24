#include "llrb.h"
#include <stdlib.h>
#include <stdio.h>

Node* createNode(int key, int color) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->color = color;
    node->left = node->right = NULL;
    return node;
}

bool isRed(Node* node) {
    if (node == NULL) return false;
    return node->color == RED;
}

Node* rotateLeft(Node* h) {
    Node* x = h->right;
    h->right = x->left;
    x->left = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

Node* rotateRight(Node* h) {
    Node* x = h->left;
    h->left = x->right;
    x->right = h;
    x->color = h->color;
    h->color = RED;
    return x;
}

void flipColors(Node* h) {
    h->color = RED;
    if (h->left) h->left->color = BLACK;
    if (h->right) h->right->color = BLACK;
}

Node* insert(Node* h, int key) {
    if (h == NULL) return createNode(key, RED);

    if (key < h->key)
        h->left = insert(h->left, key);
    else if (key > h->key)
        h->right = insert(h->right, key);
    else
        ; // duplicate keys not inserted

    if (isRed(h->right) && !isRed(h->left)) h = rotateLeft(h);
    if (isRed(h->left) && isRed(h->left->left)) h = rotateRight(h);
    if (isRed(h->left) && isRed(h->right)) flipColors(h);

    return h;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

bool noDoubleRed(Node* root) {
    if (!root) return true;
    if (isRed(root) && (isRed(root->left) || isRed(root->right))) return false;
    return noDoubleRed(root->left) && noDoubleRed(root->right);
}

bool redLinksLeanLeft(Node* root) {
    if (!root) return true;
    if (isRed(root->right)) return false;
    return redLinksLeanLeft(root->left) && redLinksLeanLeft(root->right);
}

bool isBalanced(Node* root, int* blackHeight) {
    if (root == NULL) {
        *blackHeight = 1;
        return true;
    }
    int leftBlackHeight, rightBlackHeight;
    if (!isBalanced(root->left, &leftBlackHeight)) return false;
    if (!isBalanced(root->right, &rightBlackHeight)) return false;
    if (leftBlackHeight != rightBlackHeight) return false;

    *blackHeight = leftBlackHeight + (root->color == BLACK ? 1 : 0);
    return true;
}

bool test_LLRBProperties(Node* root) {
    int dummy;
    return noDoubleRed(root) && redLinksLeanLeft(root) && isBalanced(root, &dummy);
}

bool test_LLRBBalance(Node* root) {
    int dummy;
    return isBST(root) && isBalanced(root, &dummy);
}