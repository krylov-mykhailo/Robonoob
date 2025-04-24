#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bst.h"

NodePtr create_node(Key key, Value val) {
    NodePtr node = (NodePtr)malloc(sizeof(Node));
    node->key = key;
    node->val = val;
    node->count = 1;
    node->left = node->right = NULL;
    return node;
}

int less(Key a, Key b) { return a < b; }
int greater(Key a, Key b) { return a > b; }
int equal(Key a, Key b) { return a == b; }

int BSTSize(NodePtr head) {
    return (head != NULL) ? head->count : 0;
}

NodePtr BSTPut(NodePtr head, Key key, Value val) {
    if (head == NULL) return create_node(key, val);
    if (less(key, head->key)) {
        head->left = BSTPut(head->left, key, val);
    } else if (greater(key, head->key)) {
        head->right = BSTPut(head->right, key, val);
    } else {
        head->val = val;
    }
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTCeiling(NodePtr head, Key key) {
    if (head == NULL) return NULL;
    if (equal(key, head->key)) return head;
    if (greater(key, head->key)) return BSTCeiling(head->right, key);
    NodePtr t = BSTCeiling(head->left, key);
    return (t != NULL) ? t : head;
}

int BSTRank(NodePtr head, Key key) {
    if (head == NULL) return 0;
    if (less(key, head->key)) return BSTRank(head->left, key);
    else if (greater(key, head->key))
        return 1 + BSTSize(head->left) + BSTRank(head->right, key);
    else return BSTSize(head->left);
}

NodePtr BSTSelect(NodePtr head, int k) {
    if (head == NULL) return NULL;
    int leftSize = BSTSize(head->left);
    if (k < leftSize) return BSTSelect(head->left, k);
    else if (k > leftSize) return BSTSelect(head->right, k - leftSize - 1);
    else return head;
}

Key BSTMin(NodePtr head) {
    if (head == NULL) exit(1);
    while (head->left != NULL) head = head->left;
    return head->key;
}

Key BSTMax(NodePtr head) {
    if (head == NULL) exit(1);
    while (head->right != NULL) head = head->right;
    return head->key;
}

static NodePtr deleteMin(NodePtr head) {
    if (head->left == NULL) {
        NodePtr rightSubtree = head->right;
        free(head);
        return rightSubtree;
    }
    head->left = deleteMin(head->left);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

NodePtr BSTDeleteMin(NodePtr head) {
    if (head == NULL) return NULL;
    return deleteMin(head);
}

NodePtr BSTDeleteMax(NodePtr head) {
    if (head == NULL) return NULL;
    if (head->right == NULL) {
        NodePtr leftSubtree = head->left;
        free(head);
        return leftSubtree;
    }
    head->right = BSTDeleteMax(head->right);
    head->count = 1 + BSTSize(head->left) + BSTSize(head->right);
    return head;
}

void BSTPrintReverse(const NodePtr head) {
    if (head != NULL) {
        BSTPrintReverse(head->right);
        printf("%d ", head->key);
        BSTPrintReverse(head->left);
    }
}

void inorderNodes(NodePtr head, NodePtr *arr, int *index) {
    if (head != NULL) {
        inorderNodes(head->left, arr, index);
        arr[(*index)++] = head;
        inorderNodes(head->right, arr, index);
    }
}

NodePtr *BSTNodes(NodePtr head, int *arraySize) {
    if (head == NULL) {
        *arraySize = 0;
        return NULL;
    }
    *arraySize = head->count;
    NodePtr *nodesArray = (NodePtr*)malloc((*arraySize) * sizeof(NodePtr));
    int size = 0;
    inorderNodes(head, nodesArray, &size);
    return nodesArray;
}

void freeBST(NodePtr head) {
    if (head != NULL) {
        freeBST(head->left);
        freeBST(head->right);
        free(head);
    }
}
// перевірка на збалансованість
int checkBalance(NodePtr root, bool *isBalanced) {
    if (root == NULL) return 0;

    int leftHeight = checkBalance(root->left, isBalanced);
    int rightHeight = checkBalance(root->right, isBalanced);

    if (abs(leftHeight - rightHeight) > 1)
        *isBalanced = false;

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

bool BSTIsBalanced(NodePtr root) {
    bool isBalanced = true;
    checkBalance(root, &isBalanced);
    return isBalanced;
}