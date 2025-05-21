// List with at;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *int_alloc_init(int valor)
{
    int *p = malloc(sizeof(int));
    *p = valor;
    return p;
}

long *long_alloc_init(long valor)
{
    long *p = malloc(sizeof(long));
    *p = valor;
    return p;
}

float *float_alloc_init(float valor)
{
    float *p = malloc(sizeof(float));
    *p = valor;
    return p;
}

char *string_alloc_init(const char *str)
{
    char *p = malloc(strlen(str) + 1);
    strcpy(p, str);
    return p;
}

typedef enum
{
    TYPE_INT,
    TYPE_LONG,
    TYPE_FLOAT,
    TYPE_STRING,
} type_t;

typedef struct node_t
{
    void *value;
    type_t type;
    struct node_t *next;
} node_t;

node_t *node_alloc_init(void *value, type_t type)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->type = type;
    node->next = NULL;

    return node;
}

void node_free(node_t *node)
{
    switch (node->type)
    {
    case TYPE_STRING:
    case TYPE_INT:
    case TYPE_LONG:
    case TYPE_FLOAT:
        free(node->value);
        break;
    default:
        break;
    }
    free(node);
}

void node_print(node_t *node)
{
    if (node == NULL)
    {
        return;
    }

    switch (node->type)
    {
    case TYPE_INT:
        printf("%d", *(int *)node->value);
        break;
    case TYPE_LONG:
        printf("%ld", *(long *)node->value);
        break;
    case TYPE_FLOAT:
        printf("%.2f", *(float *)node->value);
        break;
    case TYPE_STRING:
        printf("\"%s\"", (char *)node->value);
        break;
    default:
        printf("Desconhecido");
    }
}

typedef struct list_t
{
    node_t *head;
    unsigned int size;
} list_t;

list_t *
list_alloc_init()
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

void list_free(list_t *list)
{
    node_t *current = list->head;
    while (current != NULL)
    {
        node_t *next = current->next;
        node_free(current);
        current = next;
    }
    free(list);
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
    node_t *node = node_alloc_init(value, type);

    if (position == 0)
    {
        node_t *aux = self->head;
        self->head = node;
        node->next = aux;
        self->size = self->size + 1;
    }
    if (position > 0 && position < self->size)
    {
        node_t *current = self->head;
        for (size_t i = 1; i < position; i++)
        {
            current = current->next;
        }
        node_t *aux = current->next;
        current->next = node;
        node->next = aux;
        self->size = self->size + 1;
    }
    if (position >= self->size)
    {
        node_t *current = self->head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
        self->size = self->size + 1;
    }
}

unsigned int list_size(list_t *self)
{
    return self->size;
}

void *list_at(list_t *self, int idx)
{
    node_t *current = self->head;
    for (size_t i = 0; i < idx; i++)
    {
        current = current->next;
    }
    return current->value;
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

int main(const int argc, char **argv)
{
    struct list_t *list1 = list_alloc_init();
    list_print(list1);
    list_append(list1, int_alloc_init(10), TYPE_INT);
    list_append(list1, int_alloc_init(20), TYPE_INT);
    list_append(list1, int_alloc_init(30), TYPE_INT);
    list_insert(list1, 0, int_alloc_init(4), TYPE_INT);
    list_insert(list1, 5, int_alloc_init(5), TYPE_INT);
    list_print(list1);

    puts("======================================");
    struct list_t *list2 = list_alloc_init();
    list_print(list2);
    list_insert(list2, 0, int_alloc_init(2), TYPE_INT);
    list_insert(list2, 0, int_alloc_init(1), TYPE_INT);
    list_insert(list2, 3, int_alloc_init(4), TYPE_INT);
    list_insert(list2, 1, int_alloc_init(6), TYPE_INT);
    list_print(list2);

    puts("======================================");
    struct list_t *list3 = list_alloc_init();
    list_print(list3);
    list_insert(list3, 0, int_alloc_init(1), TYPE_INT);
    list_insert(list3, 1, float_alloc_init(3.141597), TYPE_FLOAT);
    list_insert(list3, 2, long_alloc_init(24294967297), TYPE_LONG);
    list_insert(list3, 3, string_alloc_init("IFPI"), TYPE_STRING);
    list_print(list3);

    int position = 0;
    int *num = (int *)list_at(list3, position);
    printf("Value: %d at position: %d\n", *num, position);

    return EXIT_SUCCESS;
}