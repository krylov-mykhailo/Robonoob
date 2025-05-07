#ifndef HASH_CODE_H
#define HASH_CODE_H

#include <stdbool.h>
#include <stdint.h>

typedef int32_t hash_t;

hash_t hashCodeInt(hash_t value);

hash_t hashCodeDouble(double value);

hash_t hashCodeBool(bool value);

hash_t hashCodeString(const char *str);

bool hashEqual(hash_t hash1, hash_t hash2);

#endif
