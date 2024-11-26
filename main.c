#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000    // розмір нашого масива
#define range 10  // чим наповнюємо [1..10]

void sort (int occurrences[], int numbers[]) {
    for (int i = 0; i < range - 1; i++) {
        for (int j = i + 1; j < range; j++) {
            if (occurrences[i] < occurrences[j]) {

                int temp_occurrence = occurrences[i];
                occurrences[i] = occurrences[j];
                occurrences[j] = temp_occurrence;

                int temp_number = numbers[i];
                numbers[i] = numbers[j];
                numbers[j] = temp_number;
            }
        }
    }
}

int main() {
    int array[N];
    int occurrences[range] = {0};
    int numbers[range];

    for (int i = 0; i < range; i++) {
        numbers[i] = i + 1;
    }

    srand(time(0));

    for (int i = 0; i < N; i++) {
        array[i] = (rand() % 10) + 1;
    }

    for (int i = 0; i < N; i++) {
        occurrences[array[i] - 1]++;
    }

    sort(occurrences, numbers);

    printf("Number of occurrences in descending order:\n");
    for (int i = 0; i < range; i++) {
        printf("Number %d: %d times\n", numbers[i], occurrences[i]);
    }

    return 0;
}
