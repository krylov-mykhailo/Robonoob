#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5  // розмір матриці N*N, константа

void printArray(int arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int original[N][N], rotated[N][N];

    srand(time(0));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            original[i][j] = rand() % 100;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            rotated[j][i] = original[i][j];
        }
    }

    printf("Original Array:\n");
    printArray(original);

    printf("\nRotated Array (Transposed):\n");
    printArray(rotated);

    return 0;
}
