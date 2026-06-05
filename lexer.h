#ifndef __LEXER_H__
#define __LEXER_H__
#include <stdio.h>

typedef enum {
    WORD,
    MACRO,
    // WHITESPACE
} tt; //token type

typedef struct token {
    tt type;
    char *content;
    struct token *next;
} token;

token* stream(FILE * __restrict fp);

token* test_stream(char * __restrict);

void tfree(token * __restrict t);

void tokprint(token * __restrict t);

token* parser(char * __restrict r);

#endif
