#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include <stdbool.h>
#define MAX_WORD 100

void demo_hash_table_string_string_pair() {
    HashTablePtr ht = HashTableInit();

    char *values[100];

    for (int i = 0; i < 100; ++i) {
        char key[10];
        sprintf(key, "%d", i);

        values[i] = malloc(20);
        sprintf(values[i], "value_%d", i);

        HashTablePut(ht, key, values[i]);
    }

    printf("Result: %s\n", (char *)HashTableGet(ht, "1"));

    HashTablePrint(ht, "string", false);

    HashTableDestroy(ht);

    for (int i = 0; i < 100; ++i) {
        free(values[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename.txt>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Failed to open file: %s\n", argv[1]);
        return 1;
    }

    HashTablePtr ht = HashTableInit();
    if (!ht) {
        fprintf(stderr, "Hash table initialization failed.\n");
        fclose(fp);
        return 1;
    }

    char word[MAX_WORD];
    while (fscanf(fp, "%99s", word) == 1) {
        Item count = HashTableGet(ht, word);
        if (count) {
            int updated = (int)(intptr_t)count + 1;
            HashTablePut(ht, word, (Item)(intptr_t)updated);
        } else {
            HashTablePut(ht, word, (Item)(intptr_t)1);
        }
    }

    fclose(fp);

    HashTablePrint(ht, "int", false);

    HashTableDestroy(ht);

    return 0;
}
