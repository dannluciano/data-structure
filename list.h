#if !defined(LIST_T)
#define LIST_T

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int *int_alloc_init(int valor);
static inline long *long_alloc_init(long valor);
static inline float *float_alloc_init(float valor);
static inline char *string_alloc_init(const char *str);

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

typedef struct node_t
{
    object_t *object;
    struct node_t *next;
} node_t;

node_t *node_alloc_init(void *value, type_t type);
void node_free(node_t *node);
void node_print(node_t *node);

typedef struct list_t
{
    node_t *head;
    unsigned int size;
} list_t;

list_t *list_alloc_init();
void list_free(list_t *self);
void list_append(list_t *self, void *value, type_t type);
void list_insert(list_t *self, unsigned int position, void *value, type_t type);
unsigned int list_size(list_t *self);
object_t *list_at(list_t *self, int idx);
void list_print(list_t *self);
void list_remove_at(list_t *self, unsigned int idx);
void list_remove(list_t *self, object_t *obj);
void list_sort(list_t *self, int (*cmp)(object_t *, object_t *));
list_t *list_clone(list_t *self);
bool list_equals(list_t *a, list_t *b);
void list_foreach(list_t *self, void (*callback)(object_t *obj));
void list_foreach_ctx(list_t *self, void (*callback)(object_t *obj, void *ctx), void *ctx);

#define LIST_APPEND_INT(list, val) list_append((list), int_alloc_init(val), TYPE_INT)
#define LIST_APPEND_LONG(list, val) list_append((list), long_alloc_init(val), TYPE_LONG)
#define LIST_APPEND_FLOAT(list, val) list_append((list), float_alloc_init(val), TYPE_FLOAT)
#define LIST_APPEND_STRING(list, val) list_append((list), string_alloc_init(val), TYPE_STRING)

#endif // LIST_T
