#ifndef DICT_H
#define DICT_H

#include <stdio.h>

#include "vector.h"

#define dict_create(type) _dict_create(sizeof(type))
#define len(dict) dict->keys->length

#define MAX_KEY_LEN 32

struct Dict {
    struct Vector *keys;
    struct Vector *values;
};

struct Dict *_dict_create(size_t el_size);
void dict_destroy(struct Dict *self);
void *dict_at(struct Dict *self, const char *key);
void dict_append(struct Dict *self, const char *key, const void *value);

#endif