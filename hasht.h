#ifndef __HASH__T__
// #include "memreq.h"
#define __HASH__T__
#define SCHUNK 4096
#define ushort unsigned short
// #define DIST 4096 //2^12 can fit in ushort
// #define ushort unsigned short

// typedef struct {
//     char df : 1; //defined or not
//     char md : 1; //0 means sub, 1 means exp
//                  //md stands for mode
//     char *value; //if its a macro
// } mtd;
//

typedef struct elem {
    char *key;
    // mtd meta;
    // struct {
    unsigned char df : 1;
    unsigned char md : 1;
    char * value;
    // };
    struct elem *next; //if there is a collision
} elem;

#define tmd(a) ((a)->meta)

//description:
//hasht holds 2^12 chains
//each chain holds a pointer to an elem
// typedef struct {
//     char full;
//     elem *ls;
// } chain;

typedef elem hasht[SCHUNK];

#define dht ((*ht))


hasht *maket();

ushort hash16(char * __restrict p);

// chunk* chunkify(int fd); //must take a file and chunk it into SCHUNK pages

// void run(chunk * __restrict c); //call chunkify
                      //expand macros
                      //save to new file
//this can be private
// void expand(char * __restrict buff, hasht * __restrict);
//given a buffer that is 4096, expand within

#endif
