#include <stdlib.h>
#include <stdio.h>
#include "token.h"
#include "strutil.h"


tt wtype(char * __restrict c) {
    uint tlen = mlen(c);
    register char ch = c[0];
    if (tlen >= 2 && ch == c[1] && ch == '#') return MACRO;
    // else if (tlen == 1 && ch == '\n') return NEWLINE;
    else return WORD;
}


// static inline void scpy(char * __restrict dst, char * __restrict src) {
token* tcreate(char * __restrict p) {
    uint tlen = mlen(p);
    token *ret = malloc(sizeof(token));
    ret->type = wtype(p);
    ret->content = malloc(sizeof(char) * (tlen + 1));
    ret->next = NULL;
    ret->len = tlen;
    ret->meta = NULL; //
    scpy(ret->content, p);
    // if (ret->type == 1) {
    //     token *link = malloc(sizeof(token));
    //     link->type = 1;
    //     link->content = NULL; link->len = 0; link->meta = NULL;
    //     link->next = NULL;
    //     ret->meta = link;
    // }
    // else ret->meta = NULL;
    return ret;
}

void tfree(token * __restrict t) {
    if (!t) return;
    token *tn = t->next;
    free(t->content);
    // if (tn->type) tfree(tn->meta);
    tfree(t->meta); //only if it exists
    free(t);
    tfree(t = tn);
    // while (t) {
    //     token* tn = t->next;
    //     free(t->content);
    //     if (tn->type) tfree(tn->meta);
    //     free(t);
    //     t = tn;
    // }
}
const char *debug_str = "\nToken type: %d -- Content: %s -- Next Token Location: %p";
const char *macro_msg = "\nMacro value: %s -- Next macro at %p";


void tokprint(token * __restrict t) {
    if (!t) return;
    putchar('\n');
    printf("\nToken Types: 0 = WORD, 1 = MACRO");
    printf(debug_str, t->type, t->content, t->next);
    if (t->meta) { //print macro chain
        token *cache = t->meta;
        printf("\nDEBUG: Meta Token Type: %d", cache->type);
        printf(macro_msg, cache->content, cache->meta);
        tokprint(t->meta);
    }
    tokprint(t->next);
}
