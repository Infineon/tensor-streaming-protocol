#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Util to track all memory allocations
// To enable compile with -Dprotocol_realloc=__protocol_realloc -Dprotocol_free=__protocol_free

void* __protocol_realloc(void* ptr, size_t size);
void __protocol_free(void* ptr);

typedef struct {
    void* key;
    size_t size;
} memseg_t;

static int mem_count = 0;
static size_t mem_sum = 0;
static memseg_t mem_list[1000];

void* __protocol_realloc(void* ptr, size_t size) {
    if (ptr == NULL) {
        ptr = realloc(NULL, size);
        mem_list[mem_count].key = ptr;
        mem_list[mem_count].size = size;
        mem_count++;
        mem_sum += size;
        printf("malloc size=%ld ret=%p (total: %ld)\n", size, ptr, mem_sum);
        return ptr;
    }
    else {
        for (int i = 0; i < mem_count; i++) {
            memseg_t* seg = &mem_list[i];
            if (seg->key == ptr) {
                mem_sum += size;
                mem_sum -= seg->size;
                ptr = realloc(ptr, size);
                printf("realloc size=%ld->%ld ptr=%p (total: %ld)\n", seg->size, size, ptr, mem_sum);

                seg->size = size;
                seg->key = ptr;

                return ptr;
            }
        }

        printf("FAILED realloc size=%ld ptr_in=%p\n", size, ptr);
        return NULL;
    }
}

void __protocol_free(void* ptr) {
    if (ptr == NULL)
        return;

    for (int i = 0; i < mem_count; i++) {
        memseg_t* seg = &mem_list[i];
        if (seg->key == ptr) {
            mem_sum -= seg->size;
            printf("free size=%ld ptr=%p (total: %ld)\n", seg->size, ptr, mem_sum);
            seg->key = NULL;
            seg->size = 0;
            free(ptr);
            return;
        }
    }

    printf("FAILED free %p\n", ptr);
}
