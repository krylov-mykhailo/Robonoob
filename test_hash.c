#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

void test_HashTablePutGet() {
    HashTablePtr ht = HashTableInit();

    HashTablePut(ht, "apple", (Item)(intptr_t)1);
    HashTablePut(ht, "banana", (Item)(intptr_t)2);

    Item apple = HashTableGet(ht, "apple");
    Item banana = HashTableGet(ht, "banana");

    assert(apple != NULL && (intptr_t)apple == 1);
    assert(banana != NULL && (intptr_t)banana == 2);

    printf("test_HashTablePutGet passed.\n");

    HashTableDestroy(ht);
}

void test_HashTableOverwriteValue() {
    HashTablePtr ht = HashTableInit();

    HashTablePut(ht, "apple", (Item)(intptr_t)1);
    HashTablePut(ht, "apple", (Item)(intptr_t)10);

    Item apple = HashTableGet(ht, "apple");

    assert(apple != NULL && (intptr_t)apple == 10);

    printf("test_HashTableOverwriteValue passed.\n");

    HashTableDestroy(ht);
}

void test_HashTableManyKeys() {
    HashTablePtr ht = HashTableInit();

    for (int i = 0; i < 100; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        HashTablePut(ht, key, (Item)(intptr_t)(i + 1));
    }

    for (int i = 0; i < 100; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        Item value = HashTableGet(ht, key);
        assert(value != NULL && (intptr_t)value == i + 1);
    }

    printf("test_HashTableManyKeys passed.\n");

    HashTableDestroy(ht);
}

void test_HashTableCaseSensitivity() {
    HashTablePtr ht = HashTableInit();

    HashTablePut(ht, "apple", (Item)(intptr_t)1);
    HashTablePut(ht, "APPLE", (Item)(intptr_t)2);

    Item apple_lower = HashTableGet(ht, "apple");
    Item apple_upper = HashTableGet(ht, "APPLE");

    assert(apple_lower != NULL && (intptr_t)apple_lower == 1);
    assert(apple_upper != NULL && (intptr_t)apple_upper == 2);

    printf("test_HashTableCaseSensitivity passed.\n");

    HashTableDestroy(ht);
}

void test_HashTableStressMemory() {
    HashTablePtr ht = HashTableInit();

    for (int i = 0; i < 10000; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        HashTablePut(ht, key, (Item)(intptr_t)(i + 1));
    }

    for (int i = 0; i < 10000; i++) {
        char key[10];
        sprintf(key, "key%d", i);
        Item value = HashTableGet(ht, key);
        assert(value != NULL && (intptr_t)value == i + 1);
    }

    printf("test_HashTableStressMemory passed.\n");

    HashTableDestroy(ht);
}

void run_all_tests() {
    printf("Running tests...\n");

    test_HashTablePutGet();

    test_HashTableOverwriteValue();

    test_HashTableManyKeys();

    test_HashTableCaseSensitivity();

    test_HashTableStressMemory();

    printf("All tests passed!\n");
}

int main(int argc, char *argv[]) {
    run_all_tests();
    return 0;
}