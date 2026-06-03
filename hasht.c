#include "hasht.h"
#include <ctype.h>
#define uint unsigned int
#define min(a, b) ((a) < (b) ? (a) : (b))
static const ushort lookup = (1 << 12) - 1;
static inline int mlen(char * __restrict p) {
    char * __restrict s = p;
    while (*p++);
    return p - s - 1;
}
ushort hash16(char * __restrict p) {
    ushort k = (ushort)0;
    char until = min(mlen(p), 16);
    for (char i = 0; i < until; i++) {
        k += tolower(p[i]) - 'a';
    }
    //DIST = 2^12
    return (((uint)k * until) ^ -1) & lookup;
}

