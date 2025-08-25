#include "array.h"

object_t *obj_alloc_init(void *value, type_t type)
{
    object_t *self = (object_t *)malloc(sizeof(object_t));
    if (self == NULL)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }

    self->value = value;
    self->type = type;
    return self;
}

void obj_free(object_t *self)
{
    if (!self)
        return;
    switch (self->type)
    {
    case TYPE_STRING:
    case TYPE_INT:
    case TYPE_LONG:
    case TYPE_FLOAT:
        free(self->value);
        break;
    default:
        break;
    }
    free(self);
}

void obj_print(object_t *self)
{
    if (self != NULL)
    {

        switch (self->type)
        {
        case TYPE_INT:
            printf("%d", *(int *)self->value);
            break;
        case TYPE_LONG:
            printf("%ld", *(long *)self->value);
            break;
        case TYPE_FLOAT:
            printf("%.2f", *(float *)self->value);
            break;
        case TYPE_STRING:
            printf("\"%s\"", (char *)self->value);
            break;
        default:
            printf("Desconhecido");
        }
    }
    else
    {
        printf("NULL");
    }
}

array_t *array_alloc_init(unsigned int capacity)
{
    struct array_t *array = (struct array_t *)malloc(sizeof(struct array_t));
    if (array == NULL)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }

    if (capacity > 0)
    {
        array->elements = (object_t **)calloc(capacity, sizeof(object_t *));
        if (!array->elements)
        {
            perror("Memory Error");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        array->elements = NULL;
    }

    array->capacity = capacity;
    array->size = 0;

    return array;
}

array_t *__array_realloc__(array_t *self)
{
    if (!self)
    {
        return NULL;
    }

    object_t **old = self->elements;
    unsigned int base = (self->capacity == 0) ? 1u : self->capacity;
    unsigned int new_capacity = base + (base >> 1); // ~1.5x
    if (new_capacity <= self->capacity)
        new_capacity = self->capacity + 1;

    object_t **new_elems = (object_t **)calloc(new_capacity, sizeof(object_t *));
    if (!new_elems)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < self->size; i++)
    {
        new_elems[i] = old ? old[i] : NULL;
    }

    self->elements = new_elems;
    self->capacity = new_capacity;
    if (old)
    {
        free(old);
    }
    return self;
}

void array_free(array_t *self)
{
    if (!self)
        return;
    if (self->elements)
    {
        for (size_t i = 0; i < self->size; i++)
        {
            if (self->elements[i])
                obj_free(self->elements[i]);
        }
        free(self->elements);
    }
    free(self);
}

void array_append(array_t *self, void *value, type_t type)
{
    object_t *obj = obj_alloc_init(value, type);
    if (self->capacity == 0)
    {
        __array_realloc__(self);
    }

    if (self->size >= self->capacity)
    {
        __array_realloc__(self);
    }

    self->elements[self->size] = obj;
    self->size = self->size + 1;
}

void array_insert(array_t *self, unsigned int position, void *value, type_t type)
{
    if (!self)
        return;

    if (self->size >= self->capacity)
    {
        __array_realloc__(self);
    }

    if (position > self->size)
    {
        array_append(self, value, type);
        return;
    }

    object_t *obj = obj_alloc_init(value, type);

    for (size_t i = self->size; i > position; i--)
    {
        self->elements[i] = self->elements[i - 1];
    }

    self->elements[position] = obj;
    self->size = self->size + 1;
}

unsigned int array_size(array_t *self)
{
    return self->size;
}

unsigned int array_capacity(array_t *self)
{
    return self->capacity;
}

object_t *array_at(array_t *self, unsigned int idx)
{
    if (!self || idx >= self->size)
        return NULL;
    return self->elements[idx];
}

void array_print(array_t *self)
{
    printf("[");
    for (size_t i = 0; i < self->size; i++)
    {
        obj_print(self->elements[i]);
        if (i < self->size - 1)
        {
            printf(", ");
        }
    }

    printf("] (size: %u, capacity: %u)\n", self->size, self->capacity);
}

void array_remove_at(array_t *self, unsigned int idx)
{
    if (!self || self->size == 0 || idx >= self->size)
        return;

    if (self->elements[idx])
        obj_free(self->elements[idx]);
    for (size_t i = idx; i + 1 < self->size; i++)
        self->elements[i] = self->elements[i + 1];

    self->elements[self->size - 1] = NULL;
    self->size--;
}

void array_foreach(array_t *self, void (*callback)(object_t *obj))
{
    if (!self || !callback)
        return;
    for (size_t i = 0; i < self->size; i++)
    {
        callback(self->elements[i]);
    }
}

void array_foreach_ctx(array_t *self, void (*callback)(object_t *obj, void *ctx), void *ctx)
{
    if (!self || !callback)
        return;

    for (size_t i = 0; i < self->size; i++)
    {
        callback(self->elements[i], ctx);
    }
}

void print_cb(object_t *obj)
{
    obj_print(obj);
    printf("->");
}

int main(const int argc, char **argv)
{
    puts("===================================================================");
    struct array_t *array0 = array_alloc_init(0);
    array_print(array0);
    array_append(array0, int_alloc_init(10), TYPE_INT);
    array_print(array0);
    array_free(array0);
    puts("===================================================================");
    struct array_t *array1 = array_alloc_init(3);
    array_print(array1);
    array_append(array1, int_alloc_init(10), TYPE_INT);
    array_print(array1);
    array_append(array1, int_alloc_init(20), TYPE_INT);
    array_print(array1);
    array_append(array1, int_alloc_init(30), TYPE_INT);
    array_print(array1);
    array_insert(array1, 0, int_alloc_init(4), TYPE_INT);
    array_print(array1);
    array_insert(array1, 5, int_alloc_init(5), TYPE_INT);
    array_print(array1);
    puts("===================================================================");
    struct array_t *array2 = array_alloc_init(10);
    array_print(array2);
    array_insert(array2, 0, int_alloc_init(2), TYPE_INT);
    array_insert(array2, 0, int_alloc_init(1), TYPE_INT);
    array_insert(array2, 3, int_alloc_init(4), TYPE_INT);
    array_insert(array2, 1, int_alloc_init(6), TYPE_INT);
    array_print(array2);

    puts("===================================================================");
    struct array_t *array3 = array_alloc_init(10);
    array_print(array3);
    array_insert(array3, 0, int_alloc_init(1), TYPE_INT);
    array_insert(array3, 1, float_alloc_init(3.141597), TYPE_FLOAT);
    array_insert(array3, 2, long_alloc_init(24294967297), TYPE_LONG);
    array_insert(array3, 3, string_alloc_init("IFPI"), TYPE_STRING);
    array_print(array3);

    puts("===================================================================");
    int position = 0;
    object_t *num = array_at(array3, position);
    obj_print(num);
    putchar('\n');

    object_t *obj = obj_alloc_init("T", TYPE_STRING);
    obj_print(obj);
    putchar('\n');

    puts("===================================================================");
    array_foreach(array1, print_cb);
    putchar('\n');
    array_foreach(array2, print_cb);
    putchar('\n');
    array_foreach(array3, print_cb);
    putchar('\n');

    puts("===================================================================");
    struct array_t *array4 = array_alloc_init(10);
    array_remove_at(array4, 0);
    array_remove_at(array4, 1);
    array_print(array4);

    array_remove_at(array1, 0);
    array_remove_at(array1, 1);
    array_remove_at(array1, array1->size - 1);
    array_remove_at(array1, 6);
    array_remove_at(array1, 6);
    array_remove_at(array1, 0);
    array_remove_at(array1, 0);
    array_print(array1);

    puts("===================================================================");
    struct array_t *array5 = array_alloc_init(0);
    for (size_t i = 0; i < 100; i++)
    {
        array_append(array5, int_alloc_init(i), TYPE_INT);

        // array_print(array5);
        // printf("%d\n", array_capacity(array5));
    }

    array_free(array1);
    array_free(array2);
    array_free(array3);
    array_free(array4);
    array_free(array5);

    return EXIT_SUCCESS;
}