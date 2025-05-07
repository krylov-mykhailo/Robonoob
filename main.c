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
        HashTablePut(ht, word);
    }

    fclose(file);
}

void perform_prefix_search(HashTablePtr ht, const char *prefix) {
    int result_size = 0;
    char **results = HashTablePrefixSearch(ht, prefix, &result_size);

    if (results == NULL || result_size == 0) {
        printf("No matches found for prefix '%s'\n", prefix);
    } else {
        printf("Matching words for prefix '%s':\n", prefix);
        for (int i = 0; i < result_size; i++) {
            printf("  %s\n", results[i]);
            free(results[i]);
        }
        free(results);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <wordlist.txt>\n", argv[0]);
        return 1;
    }

    HashTablePtr ht = HashTableInit();
    insert_words_from_file(ht, argv[1]);

    char prefix[256];
    printf("Enter prefix to search: ");
    if (scanf("%255s", prefix) != 1) {
        fprintf(stderr, "Error reading prefix\n");
        HashTableDestroy(ht);
        return 1;
    }

    perform_prefix_search(ht, prefix);
    HashTableDestroy(ht);
    return 0;
}