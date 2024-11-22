#include <stdio.h>

int main() {
    int N;

    printf("Введіть довжину сторони квадрата (N > 0): ");
    scanf("%d", &N);

    if (N <= 0) {
        printf("N має бути більше 0.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((i == 0 && (j == 0 || j == N-1)) ||
                (i == N-1 && (j == 0 || j == N-1)) ||
                (i == j) ||
                (i + j == N - 1)) {
                printf("*");
                } else {
                    printf("|");
                }
        }
        printf("\n");
    }
    return 0;
}