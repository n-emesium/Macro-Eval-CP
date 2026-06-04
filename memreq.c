#include "memreq.h"
#include <sys/mman.h>
chunk * __restrict mem_arena = NULL; //singleton
chunk * __restrict origin = NULL;


chunk* carve() {
    static uint nch = 0;
    chunk* slab = (chunk*)mmap(NULL, sizeof(chunk), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    slab->fill = 0;
    slab->nchunk = nch++;
    slab->next = slab->prev = NULL;
    return slab;
}

void* alloc(size_t sz) {
    if (!mem_arena) init();
    else if (sz > SCHUNK) return NULL; //refuse
    else if (mem_arena->fill + sz > SCHUNK) { //chain
        mem_arena->next = carve();
        mem_arena->next->prev = mem_arena;
        mem_arena = mem_arena->next;
    }
    void *ret = &mem_arena->buff[mem_arena->fill];
    mem_arena->fill += sz;
    return ret;
}

void cfree() { //clear starting from r

    while (mem_arena->next) {
        chunk *cont = mem_arena->next;
        munmap((void*)mem_arena, sizeof(chunk));
        mem_arena = cont;
    }
    munmap((void *)mem_arena, sizeof(chunk));
}

void afree() {
    while (mem_arena->prev) mem_arena = mem_arena->prev;
    cfree();
}

void ffree() {
    mem_arena = origin;
    cfree();
}
