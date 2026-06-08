#ifndef HASHMAP
#define HASHMAP
#define BMAX 4096
#define lookup 4095
#define SMAX 256
#define ush unsigned short
#undef uint
#define uint unsigned int
#define dht (*ht)
typedef struct mem {
    char f; //occupied or not
    char *key;
    char *val;
    struct mem* next;
} mem;

typedef mem* hasht[BMAX];

ush h16(char * __restrict c);
hasht* maket();
void ftable(hasht *);
ush inject(char * __restrict c,char * __restrict reg, hasht *);
char *fetch(char * __restrict c, hasht *);
void ptable(hasht *);


#endif
