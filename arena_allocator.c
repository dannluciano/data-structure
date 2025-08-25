/*
 * arena_allocator.c - Exemplo completo de Arena Allocator em C
 *
 * Demonstra:
 * - Inicialização de arena
 * - Alocação segura com alinhamento
 * - Reset e liberação
 * - Comparação com malloc para pequenos objetos
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define ARENA_DEFAULT_CAPACITY (1024 * 1024) // 1MB
#define ALIGNMENT 8

typedef struct
{
    char *buffer;
    size_t capacity;
    size_t offset;
} Arena;

size_t align_up(size_t size, size_t alignment)
{
    return (size + (alignment - 1)) & ~(alignment - 1);
}

Arena arena_init(size_t capacity)
{
    Arena arena;
    arena.buffer = malloc(capacity);
    if (!arena.buffer)
    {
        fprintf(stderr, "Erro ao alocar arena.\n");
        exit(1);
    }
    arena.capacity = capacity;
    arena.offset = 0;
    return arena;
}

void *arena_alloc(Arena *arena, size_t size)
{
    size = align_up(size, ALIGNMENT);
    if (arena->offset + size > arena->capacity)
    {
        fprintf(stderr, "Arena sem espaço suficiente para alocar %zu bytes.\n", size);
        return NULL;
    }
    void *ptr = arena->buffer + arena->offset;
    arena->offset += size;
    return ptr;
}

void arena_reset(Arena *arena)
{
    arena->offset = 0;
}

void arena_free(Arena *arena)
{
    free(arena->buffer);
    arena->buffer = NULL;
    arena->capacity = 0;
    arena->offset = 0;
}

void test_arena_vs_malloc()
{
    const size_t NUM_OBJECTS = 1000000;

    printf("Testando malloc...\n");
    clock_t start = clock();
    for (size_t i = 0; i < NUM_OBJECTS; i++)
    {
        int *x = malloc(sizeof(int));
        *x = i;
        free(x);
    }
    clock_t end = clock();
    printf("malloc: %.4f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    printf("Testando arena...\n");
    Arena arena = arena_init(ARENA_DEFAULT_CAPACITY * 16);
    start = clock();
    for (size_t i = 0; i < NUM_OBJECTS; i++)
    {
        int *x = (int *)arena_alloc(&arena, sizeof(int));
        if (!x)
        {
            fprintf(stderr, "Arena cheia, resetando.\n");
            arena_reset(&arena);
            x = (int *)arena_alloc(&arena, sizeof(int));
        }
        *x = i;
    }
    end = clock();
    printf("arena: %.4f segundos\n", (double)(end - start) / CLOCKS_PER_SEC);

    arena_free(&arena);
}

int main(void)
{
    Arena myArena = arena_init(1024 * 16); // 16 KB

    int *a = (int *)arena_alloc(&myArena, sizeof(int));
    *a = 42;
    printf("Valor alocado: %d\n", *a);

    char *msg = (char *)arena_alloc(&myArena, 64);
    strcpy(msg, "Arena allocator funcionando corretamente.");
    printf("Mensagem: %s\n", msg);

    printf("Resetando arena...\n");
    arena_reset(&myArena);

    char *msg2 = (char *)arena_alloc(&myArena, 32);
    strcpy(msg2, "Depois do reset.");
    printf("Mensagem pós-reset: %s\n", msg2);

    arena_free(&myArena);

    printf("\nRodando benchmark com malloc vs arena...\n");
    test_arena_vs_malloc();

    return 0;
}
