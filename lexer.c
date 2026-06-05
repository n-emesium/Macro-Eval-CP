#include "lexer.h"
#include <stdlib.h>
#include "hasht.h"
#include <stdio.h>
#define MAXS 100
extern int isalpha(int c); //pull this from ctype
tt wtype(char * __restrict c) {
    uint tlen = mlen(c);
    if (tlen >= 2 && c[0] == c[1] && c[0] == '#') return MACRO;
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


token* parser(char * __restrict r) {
    register char ll = *r;
    register unsigned char ind = 0;
    char rbuff[MAXS];
    token *ret = NULL; token *prev = NULL; token *origin = NULL;
    while (ll) {
        if (isalpha(ll)) {
            build:
            rbuff[ind++] = ll;
        } else if (ll == '#') {
            register unsigned char peek = *(r + 1);
            if (peek && peek == '#') {rbuff[ind++] = '#';goto build;}
        } else if (ind) {
            append:
                rbuff[ind] = '\0';
                ret = malloc(sizeof(token));
                if (!origin) origin = ret;
                ret->type = wtype(rbuff);
                uint tlen = mlen(rbuff);
                ret->content = malloc(sizeof(char) * (tlen + 1));
                // rbuff[tlen] = '\0';
                scpy(ret->content, rbuff);
                ret->next = NULL;
                if (prev) prev->next = ret;
                prev = ret;
                // rbuff[(ind = 0)] = '\0';
                ind = 0;
        }
        ll = *++r;
    }
    if (ind) goto append;
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

const char *debug_str = "\nToken type: %d -- Content: %s -- Next Token Location: %p";


void tokprint(token * __restrict t) {

    while (t) {
        putchar('\n');
        printf("\nToken types: 0 = WORD, 1 = MACRO");
        printf(debug_str, t->type, t->content, t->next);
        t = t->next;
    }
}
