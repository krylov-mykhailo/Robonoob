#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

void insert_words_from_file(HashTablePtr ht, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    char word[256];
    while (fscanf(file, "%s", word) != EOF) {
        if (HashTableGet(ht, word) == NULL) {
            HashTablePut(ht, word, word);
        }
    }

    fclose(file);
}

void perform_prefix_search(HashTablePtr ht, const char *prefix) {
    int result_size = 0;
    Key **results = HashTablePrefixSearch(ht, prefix, &result_size);

    if (result_size == 0) {
        printf("No matches found for prefix '%s'\n", prefix);
    } else {
        printf("Matching words for prefix '%s':\n", prefix);
        for (int i = 0; i < result_size; i++) {
            printf("  %s\n", results[i]);
            free(results[i]);
        }
    }

    free(results);
}

int main() {
    HashTablePtr ht = HashTableInit();
    //ось тут момєнтік що шлях до файлу прописаний повністю
    insert_words_from_file(ht, "/Users/mykhailo/CLionProjects/HT8_2/sample.txt");

    perform_prefix_search(ht, "");

    HashTablePrint(ht, "linear", true);

    HashTableDestroy(ht);

    return 0;
}