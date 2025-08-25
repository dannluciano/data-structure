#include "list.h"

static inline int *int_alloc_init(int valor)
{
    int *p = malloc(sizeof(int));
    *p = valor;
    return p;
}

static inline long *long_alloc_init(long valor)
{
    long *p = malloc(sizeof(long));
    *p = valor;
    return p;
}

static inline float *float_alloc_init(float valor)
{
    float *p = malloc(sizeof(float));
    *p = valor;
    return p;
}

static inline char *string_alloc_init(const char *str)
{
    if (!str)
        return NULL;
    char *p = malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}

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

node_t *node_alloc_init(void *value, type_t type)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }

    object_t *object = obj_alloc_init(value, type);
    node->object = object;
    node->next = NULL;

    return node;
}

void node_free(node_t *node)
{
    obj_free(node->object);
    free(node);
}

void node_print(node_t *node)
{
    if (node == NULL)
    {
        return;
    }

    obj_print(node->object);
}

list_t *list_alloc_init()
{
    struct list_t *list = (struct list_t *)malloc(sizeof(struct list_t));
    if (list == NULL)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }

    list->head = NULL;
    list->size = 0;

    return list;
}

void list_free(list_t *self)
{
    node_t *current = self->head;
    while (current != NULL)
    {
        node_t *next = current->next;
        node_free(current);
        current = next;
    }
    free(self);
}

void list_append(list_t *self, void *value, type_t type)
{
    node_t *node = node_alloc_init(value, type);
    if (self->size == 0)
    {
        self->head = node;
    }
    if (self->size > 0)
    {
        node_t *current = self->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }
    self->size = self->size + 1;
}

void list_insert(list_t *self, unsigned int position, void *value, type_t type)
{
    if (!self)
        return;
    node_t *node = node_alloc_init(value, type);

    if (position == 0 || self->head == NULL)
    {
        node->next = self->head;
        self->head = node;
    }
    else
    {
        node_t *current = self->head;
        for (unsigned int i = 1; i < position && current->next; i++)
        {
            current = current->next;
        }
        node->next = current->next;
        current->next = node;
    }

    self->size++;
}

unsigned int list_size(list_t *self)
{
    return self->size;
}

object_t *list_at(list_t *self, int idx)
{
    if (!self || idx < 0 || idx >= (int)self->size)
        return NULL;
    node_t *current = self->head;
    for (size_t i = 0; i < idx; i++)
    {
        current = current->next;
    }
    return current->object;
}

void list_print(list_t *self)
{
    printf("[");
    node_t *current = self->head;
    while (current != NULL)
    {
        node_print(current);
        if (current->next != NULL)
        {
            printf(", ");
        }
        current = current->next;
    }
    printf("] (size: %u)\n", self->size);
}

void list_remove_at(list_t *self, unsigned int idx)
{
    if (!self || self->size == 0 || idx >= self->size)
        return;
    if (idx == 0)
    {
        node_t *current = self->head;
        self->head = current->next;
        node_free(current);
    }
    else
    {
        node_t *current = self->head->next;
        node_t *prev = self->head;
        for (size_t i = 1; i < idx; i++)
        {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        node_free(current);
    }
    self->size -= 1;
}

void list_foreach(list_t *self, void (*callback)(object_t *obj))
{
    if (!self || !callback)
        return;

    node_t *current = self->head;
    while (current)
    {
        callback(current->object);
        current = current->next;
    }
}

void list_foreach_ctx(list_t *self, void (*callback)(object_t *obj, void *ctx), void *ctx)
{
    if (!self || !callback)
        return;

    node_t *current = self->head;
    while (current)
    {
        callback(current->object, ctx);
        current = current->next;
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
    struct list_t *list1 = list_alloc_init();
    list_print(list1);
    list_append(list1, int_alloc_init(10), TYPE_INT);
    list_append(list1, int_alloc_init(20), TYPE_INT);
    list_append(list1, int_alloc_init(30), TYPE_INT);
    list_insert(list1, 0, int_alloc_init(4), TYPE_INT);
    list_insert(list1, 5, int_alloc_init(5), TYPE_INT);
    list_print(list1);

    puts("===================================================================");
    struct list_t *list2 = list_alloc_init();
    list_print(list2);
    list_insert(list2, 0, int_alloc_init(2), TYPE_INT);
    list_insert(list2, 0, int_alloc_init(1), TYPE_INT);
    list_insert(list2, 3, int_alloc_init(4), TYPE_INT);
    list_insert(list2, 1, int_alloc_init(6), TYPE_INT);
    list_print(list2);

    puts("===================================================================");
    struct list_t *list3 = list_alloc_init();
    list_print(list3);
    list_insert(list3, 0, int_alloc_init(1), TYPE_INT);
    list_insert(list3, 1, float_alloc_init(3.141597), TYPE_FLOAT);
    list_insert(list3, 2, long_alloc_init(24294967297), TYPE_LONG);
    list_insert(list3, 3, string_alloc_init("IFPI"), TYPE_STRING);
    list_print(list3);

    puts("===================================================================");
    int position = 0;
    object_t *num = list_at(list3, position);
    obj_print(num);
    putchar('\n');

    object_t *obj = obj_alloc_init("T", TYPE_STRING);
    obj_print(obj);
    putchar('\n');

    puts("===================================================================");
    list_foreach(list1, print_cb);
    putchar('\n');
    list_foreach(list2, print_cb);
    putchar('\n');
    list_foreach(list3, print_cb);
    putchar('\n');

    puts("===================================================================");
    struct list_t *list4 = list_alloc_init();
    list_remove_at(list4, 0);
    list_remove_at(list4, 1);
    list_print(list4);

    list_remove_at(list1, 0);
    list_remove_at(list1, 1);
    list_remove_at(list1, list1->size - 1);
    list_remove_at(list1, 6);
    list_remove_at(list1, 6);
    list_remove_at(list1, 0);
    list_remove_at(list1, 0);
    list_print(list1);

    list_free(list1);
    list_free(list2);
    list_free(list3);
    list_free(list4);

    return EXIT_SUCCESS;
}