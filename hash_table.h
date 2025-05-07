#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

#define M 100

typedef struct HashTableEntry {
    char *key;
} HashTableEntry;

typedef struct HashTable {
    HashTableEntry **st;
    HashTableEntry **prefix_st;
    int capacity;
} HashTable;

typedef HashTable* HashTablePtr;

HashTablePtr HashTableInit();

void HashTablePut(HashTablePtr ht, const char *key);

char **HashTablePrefixSearch(HashTablePtr ht, const char *prefix, int *result_size);

void HashTableDestroy(HashTablePtr ht);

#endif