#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5  // розмір матриці
#define range 21 // чим наповнюємо [0..10]

void printArray(int arr[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", arr[i][j]);
        }
        printf("\n");
    }
}
// визначаємо які стовбці і рядки мають бути модифіковвані
void setZero(int arr[N][N]) {
    int rowZero[N] = {0};
    int colZero[N] = {0};

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (arr[i][j] == 0) {
                rowZero[i] = 1;
                colZero[j] = 1;
            }
        }
    }
    // модифікуємо рядки
    for (int i = 0; i < N; i++) {
        if (rowZero[i] == 1) {
            for (int j = 0; j < N; j++) {
                arr[i][j] = 0;
            }
        }
    }
    // модифікуємо стовбці
    for (int j = 0; j < N; j++) {
        if (colZero[j] == 1) {
            for (int i = 0; i < N; i++) {
                arr[i][j] = 0;
            }
        }
    }
}

int main() {
    int arr[N][N];

    srand(time(0));
// наповнюємо матрицю числами в заданному діапазоні
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = rand() % range;
        }
    }

    printf("Original:\n");
    printArray(arr);
//запускаємо наш алгоритм пошуку і модифікації
    setZero(arr);

    printf("\nModified:\n");
    printArray(arr);

    return 0;
}
