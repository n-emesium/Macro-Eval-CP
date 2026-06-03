#ifndef MEMREQ_H
#include <stddef.h>
#define MEMREQ_H
#define ushort unsigned short
#define uint unsigned int
#define SCHUNK 4096
#define cfree chunk_free
#define init() \
    do { \
     mem_arena = carve();       \
     origin = mem_arena;   \
    } while(0)

typedef struct chunk {
    ushort fill; //how full
    char buff[SCHUNK]; //this is the chunk
    uint nchunk; //which chunk is this
    struct chunk *prev; //previous chunk
    struct chunk *next; //next chunk
} chunk;

extern chunk* __restrict mem_arena;
extern chunk* __restrict origin;

chunk* carve();
void* alloc(size_t sz);
void cfree();
void afree(); //slow free
void ffree(); //fast free

#endif
