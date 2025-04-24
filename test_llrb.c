#include "llrb.h"
#include <stdio.h>


void test_bst(Node* root) {
    printf("BST Check: %s\n", isBST(root) ? "[PASS]" : "[FAILED]");
}

void testAscendingInsertion() {
    Node* root = NULL;
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 3);
    root = insert(root, 4);
    root->color = BLACK;

    printf("Ascending Insertion:\n");
    printf("Properties %s\n", test_LLRBProperties(root) ? "[PASS]" : "[FAILED]");
    printf("Balanced %s\n", test_LLRBBalance(root) ? "[PASS]" : "[FAILED]");

    freeTree(root);
}

void testDescendingInsertion() {
    Node* root = NULL;
    root = insert(root, 4);
    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 1);
   //  root->left->key = 20; перевірка
    root->color = BLACK;

    printf("Descending Insertion:\n");
    printf("Properties %s\n", test_LLRBProperties(root) ? "[PASS]" : "[FAILED]");
    printf("Balanced %s\n", test_LLRBBalance(root) ? "[PASS]" : "[FAILED]");

    freeTree(root);
}

void testManualInsertion() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 1);
    root->color = BLACK;

    printf("Manual Insertion:\n");
    printf("Properties %s\n", test_LLRBProperties(root) ? "[PASS]" : "[FAILED]");
    printf("Balanced %s\n", test_LLRBBalance(root) ? "[PASS]" : "[FAILED]");

    freeTree(root);
}

int main() {
    testAscendingInsertion();
    testDescendingInsertion();
    testManualInsertion();
    return 0;
}