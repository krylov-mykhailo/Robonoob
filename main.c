#include <stdio.h>
#include "bst.h"

int main() {
    NodePtr root = NULL;
    root = BSTPut(root, 5, 0);
    root = BSTPut(root, 3, 0);
    root = BSTPut(root, 7, 0);
    root = BSTPut(root, 2, 0);
    root = BSTPut(root, 1, 0);

    printf("BST Reverse In-order:\n");
    BSTPrintReverse(root);
    printf("\n");

    printf("Min key: %d\n", BSTMin(root));
    printf("Max key: %d\n", BSTMax(root));

    NodePtr ceiling = BSTCeiling(root, 6);
    if (ceiling)
        printf("Ceiling of 6: %d\n", ceiling->key);

    printf("Rank of 12: %d\n", BSTRank(root, 12));

    NodePtr kth = BSTSelect(root, 3);
    if (kth)
        printf("3rd smallest key: %d\n", kth->key);

    root = BSTDeleteMax(root);
    printf("After deleting max, reverse in-order:\n");
    BSTPrintReverse(root);
    printf("\n");

// перевірка на збалансованість
    if (BSTIsBalanced(root)) {
        printf("BST is balanced\n");
    } else {
        printf("BST is not balanced\n");
    }
    freeBST(root);
    return 0;

}
