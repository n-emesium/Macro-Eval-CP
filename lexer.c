#include "lexer.h"
#include <stdlib.h>
#include "hasht.h"
#include <stdio.h>
#define MAXS 100


tt wtype(char * __restrict c) {
    uint tlen = mlen(c);
    if (tlen == 1) return WHITESPACE;
    else if (c[0] == c[1] && c[0] == '#') return MACRO;
    else return WORD;
}

token *test_stream(char * __restrict p) {
    char buff[MAXS];
    token *ret = NULL;
    token *prev = ret;
    token *origin = ret;
    int bread;
    while (sscanf(p, "%s%n", buff, &bread) == 1) {
        buff[MAXS - 1] = '\0';
        printf("I read the string %s\n", buff);
        ret = malloc(sizeof(token));
        if (!origin) origin = ret;
        ret->type = wtype(buff);
        uint tlen = mlen(buff);
        p += bread;
        ret->content = malloc(sizeof(char) * (tlen + 1));
        scpy(ret->content, buff);
        ret->next = NULL;
        if (prev) prev->next = ret;
        prev = ret;
    }
    return origin;
}


//INCOMPLETE
token* stream(FILE * __restrict fp) {
    token *t = malloc(sizeof(token));
    token *origin = t;
    //construct
    return origin;
}


void tfree(token * __restrict t) {
    while (t) {
        token* tn = t->next;
        free(t->content);
        free(t);
        t = tn;
    }
}

const char *debug_str = "Token type: %d -- Content: %s -- Next Token Location: %p";


void tokprint(token * __restrict t) {

    while (t) {
        puts("Token types: 0 = WORD, 1 = MACRO, 2 = WHITESPACE");
        printf(debug_str, t->type, t->content, t->next);
        t = t->next;
    }
}
