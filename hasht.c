#include "hasht.h"
#define uint unsigned int
#define min(a, b) ((a) < (b) ? (a) : (b))
#define lookup 4095
static inline int mlen(char * __restrict p) {
    char * __restrict s = p;
    while (*p++);
    return p - s - 1;
}
ushort hash16(char * __restrict p) {
    int k = 0;
    char until = min(mlen(p), 16);
    unsigned char coef = 37;
    for (char i = 0; i < until; i++) {
        k += (p[i] - 'a') * coef++;
    }
    return ((~((k + until) + coef))) & lookup;
}

void run(chunk * __restrict c) {
    chunk *next = NULL;
    while (c) {

    }
}


hasht *maket() {
    hasht *ht = alloc(sizeof(chain) * SCHUNK);
    for (ushort i = 0; i < SCHUNK; i++) {
        ht[i]->full = 0;
    }
    return ht;
}

static inline void cpy(char * restrict src, char * restrict dest, int st, int ed) {
    for (int i = st; i <= ed; i++) {
        *dest = *src;
    }
    dest[ed+1] = '\0';
}

//algorithm:
//easy approach
//2 pass, 1 for population
//second pass for evaluation

void expand(char * __restrict buff, hasht * __restrict ht) {
#define dht (*ht)
    ushort i = 0;
    //schunk = 2^12
    char prev = '\0';
    char cur = buff[i];
    while (i < SCHUNK) {
        if (prev == '#' && cur == '#') { //macroseen
            char r = i;
            while (buff[r] && buff[r] != ' ')r++;
            char macro[r - i + 1];
            cpy(buff, macro, i, r);
            ushort hashed = hash16(macro);
            chain get = dht[hashed];
            if (get.full) { //collision

            } else { //not colliding

            }
        }
        prev = cur;
        cur = buff[++i];
    }
#undef dht
}

// chunk* chunkify(int fd) {
//     while () {
//
//     }
//     return origin;
// }
