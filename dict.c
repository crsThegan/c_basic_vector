#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dict.h"
#include "vector.h"

struct Dict *_dict_create(size_t el_size) {
    struct Dict *ret = malloc(sizeof(struct Dict));
    ret->keys = _vector_create(MAX_KEY_LEN);
    ret->values = _vector_create(el_size);
    return ret;
}

void dict_destroy(struct Dict *self) {
    vector_destroy(self->keys);
    vector_destroy(self->values);
    free(self);
}

void *dict_at(struct Dict *self, const char *key) {
    for (int i = 0; i < len(self); i++) {
        if (!strcmp((char *)vector_at(self->keys, i), key))
            return vector_at(self->values, i);
    }
    fprintf(stderr, "Error: couldn't find the key in the dictionary");
    dict_destroy(self);
    exit(1);
}

void dict_append(struct Dict *self, const char *key, const void *value) {
    for (int i = 0; i < len(self); i++) {
        if (!strcmp((char *)vector_at(self->keys, i), key)) {
            fprintf(stderr, "Error: such a key has already been defined in this dictionary");
            dict_destroy(self);
            exit(1);
        }
    }
    vector_append(self->keys, key);
    vector_append(self->values, value);
}