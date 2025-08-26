#if !defined(ARRAY_T)
#define ARRAY_T

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int *int_alloc_init(int value)
{
    int *p = (int *)malloc(sizeof(int));
    if (!p)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }
    *p = value;
    return p;
}

static inline long *long_alloc_init(long value)
{
    long *p = (long *)malloc(sizeof(long));
    if (!p)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }
    *p = value;
    return p;
}

static inline float *float_alloc_init(float value)
{
    float *p = (float *)malloc(sizeof(float));
    if (!p)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }
    *p = value;
    return p;
}

static inline char *string_alloc_init(const char *value)
{
    if (!value)
        return NULL;
    size_t n = strlen(value) + 1;
    char *p = (char *)malloc(n);
    if (!p)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }
    memcpy(p, value, n);
    return p;
}

typedef enum
{
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_STRING,
} type_t;

typedef struct object_t
{
    void *value;
    type_t type;
} object_t;

object_t *obj_alloc_init(void *value, type_t type);
void obj_free(object_t *self);
void obj_print(object_t *self);
bool obj_equals(object_t *a, object_t *b);

typedef struct array_t
{
    object_t **elements;
    unsigned int size;
    unsigned int capacity;
} array_t;

array_t *array_alloc_init(unsigned int capacity);
void array_free(array_t *self);
void array_append(array_t *self, void *value, type_t type);
void array_insert(array_t *self, unsigned int position, void *value, type_t type);
unsigned int array_size(array_t *self);
unsigned int array_capacity(array_t *self);
object_t *array_at(array_t *self, unsigned int idx);
void array_print(array_t *self);
void array_remove_at(array_t *self, unsigned int idx);
void array_remove(array_t *self, object_t *obj);
void array_sort(array_t *self, int (*cmp)(object_t *, object_t *));
array_t *array_clone(array_t *self);
bool array_equals(array_t *a, array_t *b);
void array_foreach(array_t *self, void (*callback)(object_t *obj));
void array_foreach_ctx(array_t *self, void (*callback)(object_t *obj, void *ctx), void *ctx);

#define ARRAY_APPEND_INT(array, val) array_append((array), int_alloc_init(val), TYPE_INT)
#define ARRAY_APPEND_LONG(array, val) array_append((array), long_alloc_init(val), TYPE_LONG)
#define ARRAY_APPEND_FLOAT(array, val) array_append((array), float_alloc_init(val), TYPE_FLOAT)
#define ARRAY_APPEND_STRING(array, val) array_append((array), string_alloc_init(val), TYPE_STRING)

#endif // ARRAY_T
