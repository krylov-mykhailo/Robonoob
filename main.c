#include <stdio.h>
#include <stdlib.h>
#include "dynamic_2d_array.h"

int main() {
    int size;
    printf("Enter the number of rows in the 2D array: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid input size.\n");
        return 1;
    }
    getchar(); // Consume newline left by scanf

    char** arr = allocate_2d_array(size);
    if (arr == NULL) {
        return 1;
    }

    if (fill_2d_array(arr, size) == -1) {
        return 1; // Memory cleanup already handled in fill_2d_array
    }

    printf("Original array:\n");
    print_2d_array((const char**)arr, size);

    sort_2d_array(arr, size);
    printf("Sorted characters in rows:\n");
    print_2d_array((const char**)arr, size);

    free_2d_array(arr, size); // Ensure all memory is freed
    return 0;
}


//cd /Users/mikhail/CLionProjects/7.1
//gcc -Wall -g -o 7.1 dynamic_2d_array.c main.c
// ./7.1
//valgrind --leak-check=full --track-origins=yes ./7.1
//valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./7.1

