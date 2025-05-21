// List with insert on position 0;

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
    if (node->next != NULL)
    {
        node_print(node->next);
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

void list_append(list_t *self, void *value)
{
    node_t *node = node_alloc_init(value);
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

void list_insert(list_t *self, unsigned int position, void *value)
{
    node_t *node = node_alloc_init(value);

    if (position == 0)
    {
        node_t *aux = self->head;
        self->head = node;
        node->next = aux;
    }

    self->size = self->size + 1;
}

unsigned int list_size(list_t *self)
{
    return self->size;
}

void list_print(list_t *self)
{
    putchar('[');
    node_print(self->head);
    putchar(']');
    printf(" size: %u", self->size);
    putchar('\n');
}

int main(const int argc, char **argv)
{
    struct list_t *list1 = list_alloc_init();
    list_print(list1);
    list_append(list1, (void *)10);
    list_append(list1, (void *)20);
    list_append(list1, (void *)30);
    list_insert(list1, 0, (void *)4);
    list_print(list1);

    struct list_t *list2 = list_alloc_init();
    list_print(list2);
    list_insert(list2, 0, (void *)2);
    list_insert(list2, 0, (void *)1);
    list_print(list2);

    return EXIT_SUCCESS;
}