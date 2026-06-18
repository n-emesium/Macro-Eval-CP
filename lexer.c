#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
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

//helper function to painlessly get next word
char *nextw(char * restrict src) {
    int c = 50;
}


void include(char ** __restrict r) {
    // char *resized = NULL;
    char ch, chn;
    char *read = *r;
    while (*read) {
        ch = *read, chn = *(read + 1);
        if (ch && chn && (ch == chn) && (ch == '!')) { //the only condition for inclusion

        }
    }
    // return resized;
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

#define errhand(a) \
    do {\
    perror(a);exit(EXIT_FAILURE);   \
    } while(0)


char *start(char * __restrict fn) {
    int f = open(fn, O_RDONLY);
    if (f == -1) errhand("FATAL: FILE OPEN FAILURE -- ABORTED");
    struct stat st; //os will answer, i am on linux
    if (fstat(f, &st) == -1) errhand("FATAL: FILE STATUS NOT RECEIVED -- ABORTED");
    size_t fs = st.st_size;
    char *fb = malloc(sizeof(char) * (fs + 1));
    if (!fb) errhand("FATAL: FILE BUFFER COULD NOT BE ALLOCATED -- ABORTED");
    size_t br = 0;
    while (br < fs) {
        ssize_t res = read(f, fb + br, fs - br);
        if (res == -1) {
            free(fb);
            errhand("ERROR: FILE READ FAILED");
        }
        if (!res) break; //EOF was found earlier
        br += res;
    }
    fb[br] = '\0';
    close(f);
    return fb;
}

void expand(char * __restrict fn) {
    char *st = start(fn);
    include(&st);
    token *ts = parser(st);
    //now implement the expansion using the hash table
}


//INCOMPLETE, NEVER USE
// token* stream(FILE * __restrict fp) {
//     token *t = malloc(sizeof(token));
//     token *origin = t;
//     //construct
//     return origin;
// }

