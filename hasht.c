#include <stdlib.h>
#include "hasht.h"
#include <stdio.h>
#include "strutil.h"
#define min(a, b) ((a) < (b) ? (a) : (b))

// static inline int mlen(char * __restrict c) {
//     char * __restrict p = c;
//     while (*c++);
//     return c - p - 1;
// }

ush h16(char * __restrict c) {
    int k = 0;
    char until = min(mlen(c), 16);
    unsigned char coef = 37;
    for (char i = 0; i < until; i++) {
        k += (c[i] - 'a') * coef++;
    }
    return ((~((k + until) + coef))) & lookup;
}

hasht* maket() {
    hasht* ht = malloc(sizeof(mem *) * BMAX);
    for (ush i = 0; i < BMAX; i++) {
        dht[i] = NULL;
        // mem *addr = dht[i];
        // addr->f = 0;
        // addr->val = "\0";
        // addr->next = NULL;
    }
    return ht;
}

void ftable(hasht *ht) {
    for (ush i = 0; i < BMAX; i++) {
        mem *addr = dht[i];
        while (addr) {
            free(addr->val);
            free(addr->key);
            mem *store = addr->next;
            free(addr);
            addr = store;
        }
    }
    free(ht);
}

// static inline void scpy(char * restrict dst, char * restrict src) {
//     while ((*dst++ = *src++));
// }

ush inject(char * __restrict c, char * __restrict reg, hasht *ht) {
    ush hashed = h16(c);
    mem* insert = malloc(sizeof(mem));
    insert->f = 1;
    insert->next = NULL;
    uint tlen = mlen(reg);
    insert->val = malloc(sizeof(char) * (tlen + 1));
    scpy(insert->val, reg);
    tlen = mlen(c);
    insert->key = malloc(sizeof(char) * (tlen + 1));
    scpy(insert->key, c);
    mem* it = dht[hashed];
    mem* follow = it;
    char start = 0;
    while (it) {follow = it; it = it->next; start = 1;}
    if (start) follow->next = insert;
    else dht[hashed] = insert;
    return hashed;
}

// static inline int mcmp(char * restrict dst, char * restrict src) {
//     while (*dst && *src && (*dst == *src) && (dst++, src++));
//     return *src - *dst;
// }

char *fetch(char * __restrict c, hasht *ht) {
    ush hashed = h16(c);
    mem *it = (dht[hashed]);
    while (it && mcmp(c, it->key)) {
        printf("occupation: %d, value: %s, next addr %p\n", it->f, it->val, it->next);
        it = it->next;
    }
    // printf("the string i got seems to be %s\n", it->val);
    return (it ? it->val : NULL);
}


void ptable(hasht *ht) {
    for (ush i = 0; i < BMAX; i++) {
        mem *it = dht[i];
        if (it) {
            while (it->next) {
                printf("%s ", it->val);
                it = it->next;
            }
            printf("%s \n", it->val);
        }
    }
    // putchar('\n');
}
