#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define MIN_KEY -256
#define MAX_KEY 256

char encrypt_char(char input, int key) {
    int normalized_key = key % 26;
    if (normalized_key < 0) {
        normalized_key += 26;
    }

    if (isalpha(input)) {
        char base = isupper(input) ? 'A' : 'a';
        return (input - base + normalized_key) % 26 + base;
    }
    return input;
}

int main() {
    int num_chars;
    int encryption_key;
    char input_char;

    srand(time(NULL));

    printf("Введіть кількість символів для шифрування: ");
    if (scanf("%d", &num_chars) != 1 || num_chars <= 0) {
        printf("Некоректна кількість символів. Завершення програми.\n");
        return 1;
    }

    encryption_key = (rand() % (MAX_KEY - MIN_KEY + 1)) + MIN_KEY;
    printf("Згенеровано ключ шифрування: %d\n", encryption_key);

    for (int i = 0; i < num_chars; i++) {
        while (1) {
            printf("Введіть символ %d/%d: ", i + 1, num_chars);
            scanf(" %c", &input_char);

            if (isalpha(input_char)) {
                char encrypted = encrypt_char(input_char, encryption_key);
                printf("Оригінал: %c, Зашифровано: %c\n", input_char, encrypted);
                break;
            } else {
                printf("Помилка: введений символ не є літерою. Спробуйте ще раз.\n");
            }
        }
    }

    printf("Процес шифрування завершено.\n");
    return 0;
}
