#ifndef __TOKEN__H__
#define __TOKEN__H__
#define ushort unsigned short

typedef enum {
    WORD,
    MACRO,
} tt;

typedef struct token token;

// typedef struct {
//     char *val; //keep it string for now
//     ushort hash;
//
//     //metadata for macros
// } mtd;

#define uint unsigned int

typedef struct token {
    tt type;
    char *content;
    uint len;
    struct token *meta; //only for macros
    struct token *next;
} token;

token* tcreate(char * __restrict p);
void tfree(token * __restrict t);
void tokprint(token * __restrict t);

tt wtype(char * __restrict c);

#endif

