#include <stdio.h>
#include "bst.h"

int main() {
    NodePtr root = NULL;
    root = BSTPut(root, 10, 1);
    root = BSTPut(root, 5, 1);
    root = BSTPut(root, 15, 1);
    root = BSTPut(root, 3, 1);
    root = BSTPut(root, 7, 1);
    root = BSTPut(root, 12, 1);
    root = BSTPut(root, 20, 1);

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
    freeBST(root);
    return 0;
}
