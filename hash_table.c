#include "hash_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned int hash(const char *key) {
    unsigned int hash_val = 0;
    while (*key) {
        hash_val = (hash_val << 5) + *key;
        key++;
    }
    return hash_val % M;
}

HashTablePtr HashTableInit() {
    HashTablePtr ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;
    for (int i = 0; i < M; i++) {
        ht->st[i] = NULL;
    }
    return ht;
}

bool HashTablePut(HashTablePtr ht, const char *key, const char *value) {
    unsigned int idx = hash(key);
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = ht->st[idx];
    ht->st[idx] = new_node;

    return true;
}

char* HashTableGet(HashTablePtr ht, const char *key) {
    unsigned int idx = hash(key);
    Node *current = ht->st[idx];
    while (current) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void HashTablePrint(const HashTablePtr ht, const char *type, bool print_empty) {
    for (int i = 0; i < M; i++) {
        Node *current = ht->st[i];
        if (current || print_empty) {
            printf("Index %d: ", i);
            while (current) {
                printf("(%s, %s) -> ", current->key, current->value);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
}

void HashTableDestroy(HashTablePtr ht) {
    for (int i = 0; i < M; i++) {
        Node *current = ht->st[i];
        while (current) {
            Node *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(ht);
}

// це наш пошук ключів за префіксом
Key **HashTablePrefixSearch(HashTablePtr ht, const char *prefix, int *result_size) {
    Key **results = malloc(sizeof(Key*) * M);
    *result_size = 0;

    for (int i = 0; i < M; i++) {
        Node *current = ht->st[i];
        while (current) {
            if (strncmp(current->key, prefix, strlen(prefix)) == 0) {
                results[*result_size] = strdup(current->key);
                (*result_size)++;
            }
            current = current->next;
        }
    }

    return results;
}