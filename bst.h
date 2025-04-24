#ifndef BST_H
#define BST_H
#include <stdbool.h>

typedef int Key;
typedef int Value;

typedef struct Node {
    Key key;
    Value val;
    int count;
    struct Node *left, *right;
} Node;

typedef Node* NodePtr;

NodePtr create_node(Key key, Value val);
NodePtr BSTPut(NodePtr head, Key key, Value val);
int BSTSize(NodePtr head);

NodePtr BSTCeiling(NodePtr head, Key key);
int BSTRank(NodePtr head, Key key);
NodePtr BSTSelect(NodePtr head, int k);
Key BSTMin(NodePtr head);
Key BSTMax(NodePtr head);

NodePtr BSTDeleteMin(NodePtr head);
NodePtr BSTDeleteMax(NodePtr head);

void BSTPrintReverse(const NodePtr head);
void inorderNodes(NodePtr head, NodePtr *arr, int *index);
NodePtr *BSTNodes(NodePtr head, int *arraySize);

int less(Key a, Key b);
int greater(Key a, Key b);
int equal(Key a, Key b);
void freeBST(NodePtr head);

bool BSTIsBalanced(NodePtr root);

#endif
