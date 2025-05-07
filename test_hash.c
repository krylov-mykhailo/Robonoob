#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

int main() {
    HashTablePtr ht = HashTableInit();

    HashTablePut(ht, "hello");
    HashTablePut(ht, "helium");
    HashTablePut(ht, "help");
    HashTablePut(ht, "hermit");
    HashTablePut(ht, "helgo");
    HashTablePut(ht, "helium");
    HashTablePut(ht, "help");
    HashTablePut(ht, "hermit");
    HashTablePut(ht, "hello");
    HashTablePut(ht, "helium");
    HashTablePut(ht, "help");
    HashTablePut(ht, "hl");
    const char *prefix = "hel";
    int result_size;

    char **results = HashTablePrefixSearch(ht, prefix, &result_size);

    if (results == NULL || result_size == 0) {
        printf("No results found for prefix '%s'.\n", prefix);
    } else {
        printf("Found %d results for prefix '%s':\n", result_size, prefix);
        for (int i = 0; i < result_size; i++) {
            printf("  %s\n", results[i]);
            free(results[i]);
        }
        free(results);
    }

    // Знищення хеш-таблиці
    HashTableDestroy(ht);

    return 0;
}