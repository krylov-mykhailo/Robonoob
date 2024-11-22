#include <stdio.h>
#include <stdlib.h>
#include "rotation.h"

void init_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(arr + i * n + j) = rand() % 100;
        }
    }
}

void print_array(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d\t", *(arr + i * n + j));
        }
        printf("\n");
    }
}

void rotate_array(int *arr, int *rotated, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            *(rotated + j * n + i) = *(arr + i * n + j);
        }
    }
}