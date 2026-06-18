#ifndef __DYN_STR_H__
#define __DYN_STR_H__
#include <stddef.h>
#define uint unsigned int
#define OVERALLOC 10
typedef struct {
    uint sz, cpc; //size, capacity
    char content[];
} dynstr; //dynamic string

//to get C style string back, simply access
//dynstr->content; this will give [0]

//this will return a dynamical string object
dynstr *make(char * __restrict src);
//this will append to the end of a dynamic string
void append(dynstr * __restrict dst, char * __restrict add);
//this will clear the content of a dynamic string
void clear(dynstr * __restrict dst);
//this will replace the content with a new string
void push(dynstr * __restrict dst, char * __restrict push);
//this will free all memory associated with the current dynamic string
void del(dynstr * __restrict dst);


#endif
