#include "hash_code.h"
#include <stddef.h>
#include <string.h>

hash_t hashCodeInt(hash_t value) { return value; }

hash_t hashCodeBool(bool value) { return value ? 1231 : 1237; }

hash_t hashCodeDouble(double value) {
    uint64_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return (hash_t)(bits ^ (bits >> 32));
}

hash_t hashCodeString(const char *str) {
    if (str == NULL)
        return 0;
    hash_t hash = 0;
    while (*str) {
        hash = 31 * hash + (unsigned char)(*str);
        str++;
    }
    return hash;
}

bool hashEqual(hash_t hash1, hash_t hash2) { return hash1 == hash2; }
