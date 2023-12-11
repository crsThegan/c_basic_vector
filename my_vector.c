#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY_FACTOR 2

#define vector_create(type) _vector_create(sizeof(type))

struct Vector {
    void *data;
    int length;
    size_t capacity;
    size_t el_size;
};

struct Vector *_vector_create(size_t el_size) {
    struct Vector *ret = malloc(sizeof(struct Vector));
    ret->data = malloc(el_size);
    ret->length = 0;
    ret->capacity = el_size;
    ret->el_size = el_size;
    return ret;
}

void vector_destroy(struct Vector *self) {
    free(self->data);
    self->data = NULL;
    free(self);
}

void *vector_at(const struct Vector *self, int idx) {
    if (idx >= self->length) {
        fprintf(stderr, "error: index is out of range");
        vector_destroy(self);
        exit(1);
    }
    return self->data + idx * self->el_size;
}

void vector_append(struct Vector *self, void *el) {
    if (self->capacity < self->el_size * ++self->length) {
        self->capacity *= CAPACITY_FACTOR;
        void *temp = realloc(self->data, self->capacity);
        if (!temp) {
            fprintf(stderr, "error: failed to reallocate memory");
            vector_destroy(self);
            exit(1);
        } else self->data = temp;
    }
    memcpy(vector_at(self, self->length - 1), el, self->el_size);
}

void vector_pop(struct Vector *self, int idx) {
    memmove(vector_at(self, idx), vector_at(self, idx + 1), (self->length - idx - 1) * self->el_size);
    if (self->capacity / CAPACITY_FACTOR / 2 > self->el_size * --self->length) {
        self->capacity /= CAPACITY_FACTOR;
        void *temp = realloc(self->data, self->capacity);
        if (!temp) {
            fprintf(stderr, "error: failed to reallocate memory");
            vector_destroy(self);
            exit(1);
        } else self->data = temp;
    }
}
