#ifndef __HASH__T__
#include "memreq.h"
#define __HASH__T__
#define DIST 4096 //2^12 can fit in ushort
// #define ushort unsigned short

typedef struct {

} mtd;

typedef struct elem {
    char *key;
    mtd meta;
    struct elem *next; //if there is a collision
} elem;

typedef elem hasht[DIST];

static inline hasht *maket() {
    return (hasht *)alloc(sizeof(hasht));
}
ushort hash16(char * __restrict p);

#endif
