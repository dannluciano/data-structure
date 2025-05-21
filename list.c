// List with append ;
#include <stdio.h>
#include <stdlib.h>

typedef struct node_t
{
    void *value;
    struct node_t *next;
} node_t;

node_t *node_alloc_init(void *value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (node == NULL)
    {
        perror("Memory Error");
        exit(EXIT_FAILURE);
    }

    node->value = value;
    node->next = NULL;

    return node;
}

void node_print(node_t *node)
{
    if (node == NULL)
    {
        return;
    }

    printf("%d, ", (int)node->value);
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

void list_append(list_t *self, void *value)
{
    node_t *node = node_alloc_init(value);
    if (self->size == 0)
    {
        self->head = node;
        self->size = self->size + 1;
    }
}

void list_print(struct list_t *list)
{
    putchar('[');
    node_print(list->head);
    putchar(']');
    putchar('\n');
}

int main(const int argc, char **argv)
{
    struct list_t *list = list_alloc_init();
    list_print(list);
    list_append(list, (void *)10);
    list_print(list);
    return EXIT_SUCCESS;
}