#include <stdlib.h>
#include "lexer.h"
#include "hasht.h"
#include <stdio.h>
#include "strutil.h"
#include "token.h"
#define MAXS 100
extern int isspace(int c); //pull this from ctype
token *test_stream(char * __restrict p) {
    char buff[MAXS];
    token *ret = NULL;
    token *prev = ret;
    token *origin = ret;
    int bread;
    while (sscanf(p, "%s%n", buff, &bread) == 1) {
        buff[MAXS - 1] = '\0';
        printf("I read the string %s\n", buff);
        ret = tcreate(buff);
        if (!origin) origin = ret;
        p += bread;
        if (prev) prev->next = ret;
        prev = ret;
    }
    return origin;
}


token* parser(char * __restrict r) {
    register char ll = *r;
    register unsigned char ind = 0;
    char rbuff[MAXS];
    char ervat = 0;
    token *ret = NULL; token *prev = NULL; token *origin = NULL; token *pmac = NULL; token *macor = NULL;
    char inmc = 0; //in a macro?
    while (ll) {
        // unsigned char newl = 0;
        if (!isspace(ll) && ll != '#') {
            build:
            rbuff[ind++] = ll;
        } else if (ll == '#' && *(r+1) == '#') {
            //add macro appending logic
            //remove peek
            rbuff[ind++] = '#';
            ll = *++r;
            inmc = 1;
            // ll = *++r;
            goto build;
        } else if (inmc && ll == '\n') {
            rbuff[ind] = '\0';
            ind = 0;
            token *app = tcreate(rbuff);
            pmac->meta = app;
            pmac = NULL;
            inmc = 0;
            if (prev) prev->next = macor;
            prev = macor;
            // macor = NULL;
        } else if (ind) {
            append:
                rbuff[ind] = '\0';
                // ret = malloc(sizeof(token));
                ret = tcreate(rbuff);
                if (!origin) origin = ret;
                if (inmc) {
                    // ret->type = 1; //this is the continuation of a macro chain
                    // if (!macor) macor = ret;
                    if (pmac) pmac->meta = ret;
                    else macor = ret;
                    pmac = ret;
                 } else {
                if (prev) prev->next = ret;
                prev = ret;
                }
                // rbuff[(ind = 0)] = '\0';
                ind = 0;
                if (ervat) break;
        }
        ll = *++r;
    }
    if (ind) {ervat = 1; goto append;}
    return origin;
}


//INCOMPLETE
token* stream(FILE * __restrict fp) {
    token *t = malloc(sizeof(token));
    token *origin = t;
    //construct
    return origin;
}

