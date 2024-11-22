#include <stdio.h>
#include <stdint.h>

    float invert(float number) {
        uint32_t *pointer = (uint32_t *)&number;
        *pointer ^= (1<<31);
        return number;
    }

    int main() {
        float number;
        printf("Введіть число з плаваючою комою: ");
        scanf("%f", &number);
        float inverted = invert(number);
        printf("Число з інвертованим знаком: %.3f\n", inverted);
        return 0;
    }