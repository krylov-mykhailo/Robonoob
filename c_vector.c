#include "c_vector.h"
#include <stdio.h>
#include <stdlib.h>

//create array
int* create(int size) {
    if (size < 0) {
        fprintf(stderr, "Size cannot be negative\n");
        return NULL;
    }

    int* arr = (int*)malloc(size * sizeof(int));
    if (!arr) {
        perror("Failed to allocate memory");
        return NULL;
    }
    return arr;
}
//add new elements
void push_back(int** ptr, int* size, int value) {
    int new_size = *size + 1;
    int* new_ptr = (int*)realloc(*ptr, new_size * sizeof(int));
    if (!new_ptr) {
        perror("Failed to allocate memory");
        return;
    }

    new_ptr[*size] = value;
    *ptr = new_ptr;
    *size = new_size;
}
//print arrays
void print(const int* ptr, int size) {
    if (!ptr || size <= 0) {
        printf("Array is empty or invalid\n");
        return;
    }

    printf("Array contents: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", ptr[i]);
    }
    printf("\n");
}
//frees allocated memory
void destroy(int* ptr) {
    free(ptr);
}
