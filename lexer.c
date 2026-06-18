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
//word is defined as not 1 literal word, but a unit of meaning
//a file name can be multiple 'words' long if the definition of a word is by spaces
//example:
//~/Desktop/tmp/dirty/"  detergent"
//do not stop parsing at the first space
//instead, stop at a newline
//do not abuse this behavior, if you screw up the syntax, do not expect correct behavior
//Assume most locations do not go over 30 chars, if they do, resize
static inline char *nextw(char * restrict src) {
    int i = 0;
    char ch;
    while ((ch = src[i]) && ch != '\n') i++;
    char *w = malloc(sizeof(char) * (i + 1)); //null termination
    scpy(w, src);
    return w;
}
#define errhand(a) \
    do {\
    perror(a);exit(EXIT_FAILURE);   \
    } while(0)

//write to file descriptor, r is the source
//


#define SBUFFER 512
//data release:
//this function shall release dirty pages back to the disk, writing to a file
//stdio FILE * shall not be used so as to not abstract disk read/write
static inline void drelease(char * __restrict b, int fd, uint bufflen) { //data release
    // int fd = open(fn, O_WRONLY);
    int i = 0;
    while (b[i]) {
        ssize_t bw = write(fd, b + i, bufflen - i);
        if (bw == -1) errhand("ERROR: FILE WRITE FAILED");
        if (!bw) break; //something wrong
        i += bw;
    }
    // close(fd);
}


//upon discovering !!, it will paste its contents, relying on drelease()
static inline int file_paste(int dst, char * __restrict src) {
    char *st = start(src);
    if (!st) return 1;
    drelease(st, dst, mlen(st));
    free(st);
    return 0;
}

void include(char * __restrict r, char * __restrict fn) {
    char buffer[SBUFFER];
    char ch, chn;
    int buffi = 0; //buffer index
    int fd = open(fn, O_WRONLY);
    while ((ch = *r)) {
        chn = *(r+1);
        if ((ch == chn) && ch == '!') { //inclusions must go!
            char *nxt = nextw(r);
            uint ll = mlen(nxt);
            int exit_value = file_paste(fd, nxt);
            if (exit_value == 1) { //try local search
                char temp[ll + 3];
                sprintf(temp, "./%s", nxt);
                if (file_paste(fd, temp) == 1) errhand("FATAL: THE FILE YOU HAVE TRIED TO INCLUDE DOES NOT EXIST -- TERMINATED");
            }
            free(nxt);
            r += ll - 1; //this brings it to the last character, r++ at the end of loop will go 1 more
            //easiest method:
            //try opening as if full path, if fail, check if in local path,
            //if it still doesn't work, give up and do not include

        // } else if (buffi < SBUFFER) { //append to buffer
            // buffer[buffi++] = ch;
        } else { //flush buffer
            if (buffi >= SBUFFER) {
                drelease(buffer, fd, buffi);
                buffi = 0;
            }
            buffer[buffi++] = ch;
            // drelease(buffer, fd, buffi);
            // buffer[0] = ch;
            // buffi = 1;
        }
        r++;
    }
    if (buffi) {drelease(buffer, fd, buffi);} //flush if buffer is still full
    close(fd);
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

char *start(char * __restrict fn) {
    int f = open(fn, O_RDONLY);
    // if (f == -1) errhand("FATAL: FILE OPEN FAILURE -- ABORTED");
    if (f == -1) {
        perror("FATAL: FILE OPEN FAILURE -- ABORTED");
        close(f);
        return NULL;
    }
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

//TODO: fix this later
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

