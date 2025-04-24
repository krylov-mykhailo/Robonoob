#include "llrb.h"
#include <limits.h>

bool isBSTUtil(Node* root, int min, int max) {
    if (!root) return true;
    if (root->key <= min || root->key >= max) return false;
    return isBSTUtil(root->left, min, root->key) &&
           isBSTUtil(root->right, root->key, max);
}

bool isBST(Node* root) {
    return isBSTUtil(root, INT_MIN, INT_MAX);
}