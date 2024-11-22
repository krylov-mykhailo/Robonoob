#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_2d_array.h"

char** allocate_2d_array(int size) {
    char** arr = (char**)malloc(size * sizeof(char*));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed for 2D array.\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        arr[i] = NULL; // Initialize pointers to NULL to avoid dangling references
    }
    return arr;
}

int fill_2d_array(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter string for row %d: ", i + 1);
        char* line = NULL;
        size_t len = 0;

        if (getline(&line, &len, stdin) == -1) {
            fprintf(stderr, "Failed to read input.\n");

            // Free already allocated rows in case of an error
            for (int j = 0; j < i; j++) {
                free(arr[j]);
            }
            free(arr);
            return -1;
        }

        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        arr[i] = line; // Assign the read line to the array
    }
    return 0;
}

void print_2d_array(const char** arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", arr[i]);
    }
}

void sort_2d_array(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == NULL) continue; // Skip null rows
        size_t len = strlen(arr[i]);
        for (size_t j = 0; j < len - 1; j++) {
            for (size_t k = j + 1; k < len; k++) {
                if (arr[i][j] > arr[i][k]) {
                    char temp = arr[i][j];
                    arr[i][j] = arr[i][k];
                    arr[i][k] = temp;
                }
            }
        }
    }
}

int compare_rows(const void* a, const void* b) {
    const char* str1 = *(const char**)a;
    const char* str2 = *(const char**)b;
    return strcmp(str1, str2);
}

void sort_rows(char** arr, int size) {
    qsort(arr, size, sizeof(char*), compare_rows);
}

void free_2d_array(char** arr, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] != NULL) {
            free(arr[i]); // Free each row
        }
    }
    free(arr); // Free the main array
}
