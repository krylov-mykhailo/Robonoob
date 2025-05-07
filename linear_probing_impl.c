#include "hash_table.h"
#include "hash_code.h"
#include "item.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define INIT_CAPACITY 97

struct HashTable {
    Key *keys;
    Item *values;
    int capacity;
    int size;
};

static int hashIndex(Key key, int capacity) {
    return (hashCodeString(key) & 0x7fffffff) % capacity;
}

HashTablePtr HashTableInit() {
    HashTablePtr ht = malloc(sizeof(*ht));
    if (!ht) return NULL;

    ht->capacity = INIT_CAPACITY;
    ht->size = 0;
    ht->keys = calloc(ht->capacity, sizeof(Key));
    ht->values = calloc(ht->capacity, sizeof(Item));
    if (!ht->keys || !ht->values) {
        free(ht->keys);
        free(ht->values);
        free(ht);
        return NULL;
    }
    return ht;
}

static void resize(HashTablePtr ht, int new_capacity) {
    HashTablePtr temp = malloc(sizeof(*temp));
    temp->capacity = new_capacity;
    temp->size = 0;
    temp->keys = calloc(new_capacity, sizeof(Key));
    temp->values = calloc(new_capacity, sizeof(Item));

    for (int i = 0; i < ht->capacity; i++) {
        if (ht->keys[i]) {
            int j = hashIndex(ht->keys[i], new_capacity);
            while (temp->keys[j]) {
                j = (j + 1) % new_capacity;
            }
            temp->keys[j] = ht->keys[i];
            temp->values[j] = ht->values[i];
            temp->size++;
        }
    }

    free(ht->keys);
    free(ht->values);

    ht->keys = temp->keys;
    ht->values = temp->values;
    ht->capacity = temp->capacity;
    ht->size = temp->size;

    free(temp);
}

bool HashTablePut(HashTablePtr ht, Key key, Item value) {
    if (!ht || !key || !value) return false;

    if (ht->size >= ht->capacity / 2) {
        resize(ht, ht->capacity * 2);
    }

    int i = hashIndex(key, ht->capacity);
    while (ht->keys[i]) {
        if (equal(key, ht->keys[i])) {
            ht->values[i] = value;
            return true;
        }
        i = (i + 1) % ht->capacity;
    }

    Key key_copy = strdup(key);
    if (!key_copy) return false;

    ht->keys[i] = key_copy;
    ht->values[i] = value;
    ht->size++;
    return true;
}

Item HashTableGet(HashTablePtr ht, Key key) {
    if (!ht || !key) return NULL;

    int i = hashIndex(key, ht->capacity);
    while (ht->keys[i]) {
        if (equal(key, ht->keys[i])) {
            return ht->values[i];
        }
        i = (i + 1) % ht->capacity;
    }
    return NULL;
}

void HashTableDestroy(HashTablePtr ht) {
    if (!ht) return;

    for (int i = 0; i < ht->capacity; i++) {
        free(ht->keys[i]);
    }
    free(ht->keys);
    free(ht->values);
    free(ht);
}

void HashTablePrint(const HashTablePtr ht, const char *type, bool print_empty) {
    for (int i = 0; i < ht->capacity; i++) {
        if (ht->keys[i]) {
            printf("%d: \"%s\": ", i, ht->keys[i]);
            if (strcmp(type, "int") == 0) {
                printf("%d", (int)(intptr_t)ht->values[i]);
            } else if (strcmp(type, "string") == 0) {
                printf("\"%s\"", (char *)ht->values[i]);
            } else {
                printf("UNKNOWN_TYPE");
            }
            printf("\n");
        } else if (print_empty) {
            printf("%d: NULL\n", i);
        }
    }
}