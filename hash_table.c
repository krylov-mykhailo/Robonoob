#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

HashTablePtr HashTableInit() {
    HashTablePtr ht = (HashTablePtr)malloc(sizeof(HashTable));
    ht->capacity = M;
    ht->st = (HashTableEntry **)malloc(sizeof(HashTableEntry *) * ht->capacity);
    ht->prefix_st = (HashTableEntry **)malloc(sizeof(HashTableEntry *) * ht->capacity);

    for (int i = 0; i < ht->capacity; i++) {
        ht->st[i] = NULL;
        ht->prefix_st[i] = NULL;
    }

    return ht;
}

unsigned int hash(const char *key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value << 5) + *key++;
    }
    return hash_value % M;
}

void HashTablePut(HashTablePtr ht, const char *key) {
    unsigned int index = hash(key);

    while (ht->st[index] != NULL) {
        if (strcmp(ht->st[index]->key, key) == 0) {
            return;
        }
        index = (index + 1) % ht->capacity;
    }

    HashTableEntry *new_entry = (HashTableEntry *)malloc(sizeof(HashTableEntry));
    new_entry->key = strdup(key);
    ht->st[index] = new_entry;

    for (int len = 1; len <= strlen(key); len++) {
        char *prefix = strndup(key, len);
        unsigned int prefix_index = hash(prefix);
        int exists = 0;

        while (ht->prefix_st[prefix_index] != NULL) {
            if (strcmp(ht->prefix_st[prefix_index]->key, prefix) == 0) {
                exists = 1;
                break;
            }
            prefix_index = (prefix_index + 1) % ht->capacity;
        }

        if (!exists) {
            HashTableEntry *prefix_entry = (HashTableEntry *)malloc(sizeof(HashTableEntry));
            prefix_entry->key = prefix;
            ht->prefix_st[prefix_index] = prefix_entry;
        } else {
            free(prefix);
        }
    }
}
char **HashTablePrefixSearch(HashTablePtr ht, const char *prefix, int *result_size) {
    char **results = (char **)malloc(sizeof(char *) * ht->capacity);
    *result_size = 0;

    for (int i = 0; i < ht->capacity; i++) {
        if (ht->prefix_st[i] != NULL && strncmp(ht->prefix_st[i]->key, prefix, strlen(prefix)) == 0) {
            results[*result_size] = strdup(ht->prefix_st[i]->key);
            (*result_size)++;
        }
    }

    return results;
}

void HashTableDestroy(HashTablePtr ht) {
    for (int i = 0; i < ht->capacity; i++) {
        if (ht->st[i] != NULL) {
            free(ht->st[i]->key);
            free(ht->st[i]);
        }
        if (ht->prefix_st[i] != NULL) {
            free(ht->prefix_st[i]->key);
            free(ht->prefix_st[i]);
        }
    }
    free(ht->st);
    free(ht->prefix_st);
    free(ht);
}