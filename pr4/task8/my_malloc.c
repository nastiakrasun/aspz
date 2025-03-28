#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>

#define PAGE_SIZE 4096  // Типовий розмір сторінки
#define MMAP_THRESHOLD (128 * 1024)  // Поріг для mmap (128 KB)

// Структура заголовка блоку пам'яті
typedef struct block_meta {
    size_t size;
    struct block_meta *next;
    int free;
} block_meta_t;

#define META_SIZE sizeof(block_meta_t)

static block_meta_t *global_base = NULL;  // Глобальний список вільних блоків

// Функція для пошуку вільного блоку
block_meta_t *find_free_block(size_t size) {
    block_meta_t *current = global_base;
    while (current) {
        if (current->free && current->size >= size) {
            current->free = 0;
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Функція для розширення сегмента даних (sbrk)
block_meta_t *request_memory(size_t size) {
    block_meta_t *block = sbrk(0);
    if (sbrk(size + META_SIZE) == (void *) -1) {
        return NULL;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    return block;
}

// Функція malloc
void *my_malloc(size_t size) {
    if (size == 0) return NULL;

    // Використовуємо mmap для великих виділень
    if (size >= MMAP_THRESHOLD) {
        void *ptr = mmap(NULL, size + META_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (ptr == MAP_FAILED) return NULL;
        ((block_meta_t *)ptr)->size = size;
        ((block_meta_t *)ptr)->free = 0;
        return (void *)((char *)ptr + META_SIZE);
    }

    // Шукаємо вільний блок
    block_meta_t *block = find_free_block(size);
    if (block) return (void *)((char *)block + META_SIZE);

    // Якщо не знайшли, виділяємо новий блок
    block = request_memory(size);
    if (!block) return NULL;

    if (!global_base) global_base = block;
    
    return (void *)((char *)block + META_SIZE);
}

// Функція для звільнення пам’яті
void my_free(void *ptr) {
    if (!ptr) return;

    block_meta_t *block = (block_meta_t *)((char *)ptr - META_SIZE);

    // Якщо це був mmap-виділений блок, звільняємо через munmap
    if (block->size >= MMAP_THRESHOLD) {
        munmap(block, block->size + META_SIZE);
        return;
    }

    // Позначаємо блок як вільний
    block->free = 1;
}

// Тестова функція
int main() {
    void *ptr1 = my_malloc(64);
    printf("Allocated 64 bytes at %p\n", ptr1);

    void *ptr2 = my_malloc(200000);
    printf("Allocated 200000 bytes (mmap) at %p\n", ptr2);

    my_free(ptr1);
    my_free(ptr2);

    return 0;
}
