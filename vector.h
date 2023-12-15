#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>

#define CAPACITY_FACTOR 2

#define vector_create(type) _vector_create(sizeof(type))
#define foreach(it, vec) vecitr_t it = vector_begin(vec); \
                         for(; !vector_end(vec, &it); vecitr_next(&it)) 

struct Vector {
    void *data;
    int length;
    size_t capacity;
    size_t el_size;
};

typedef struct {
    void *current;
    size_t el_size;
} vecitr_t;

struct Vector *_vector_create(size_t el_size);
void vector_destroy(struct Vector *self);
void *vector_at(struct Vector *self, int idx);
void vector_append(struct Vector *self, const void *el);
void vector_pop(struct Vector *self, int idx);

vecitr_t vector_begin(struct Vector *self);
void vecitr_next(vecitr_t *self);
int vector_end(struct Vector *self, vecitr_t *iter);

#endif