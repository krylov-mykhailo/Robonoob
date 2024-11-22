#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rotation.h"

#define N 4

int main() {
    int original[N][N], rotated[N][N];

    srand(time(0));

    init_array((int *)original, N);
    printf("original Array:\n");
    print_array((int *)original, N);

    rotate_array((int *)original, (int *)rotated, N);
    printf("\nrotated Array (Transposed):\n");
    print_array((int *)rotated, N);

    return 0;
}