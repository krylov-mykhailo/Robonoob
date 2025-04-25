#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

#define M 10
typedef char* Key;

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

typedef struct HashTable {
    Node* st[M];
} HashTable;

typedef HashTable* HashTablePtr;

HashTablePtr HashTableInit();
bool HashTablePut(HashTablePtr ht, const char *key, const char *value);
char* HashTableGet(HashTablePtr ht, const char *key);
void HashTablePrint(const HashTablePtr ht, const char *type, bool print_empty);
void HashTableDestroy(HashTablePtr ht);
Key **HashTablePrefixSearch(HashTablePtr ht, const char *prefix, int *result_size);

#endif