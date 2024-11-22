#include "c_vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int initial_size;

    printf("Enter size of the array: ");
    if (scanf("%d", &initial_size) != 1 || initial_size < 0) {
        fprintf(stderr, "Invalid size.\n");
        return EXIT_FAILURE;
    }
//create array
    int* array = create(initial_size);
    if (!array) {
        return EXIT_FAILURE;
    }
//fill array with random numbs
    srand(time(NULL));
    for (int i = 0; i < initial_size; i++) {
        array[i] = rand() % 201 - 100;
    }

    print(array, initial_size);
//add new random elements
    int additional_elements = 3;
    for (int i = 0; i < additional_elements; i++) {
        push_back(&array, &initial_size, rand() % 201 - 100);
    }

    print(array, initial_size);
//cleaning
    destroy(array);

    return EXIT_SUCCESS;
}

//valgrind --leak-check=full --track-origins=yes ./7.2
//cd /Users/mikhail/CLionProjects/7.2
// ./7.2
//gcc -Wall -g -o 7.2 c_vector.c main.c