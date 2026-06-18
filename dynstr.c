#include "stdlib.h"
#include "dynstr.h"
#include "strutil.h"
dynstr *make(char * __restrict src) {
    // dynstr *d = malloc(sizeof(dynstr));
    uint ll = mlen(src);
    uint gcpc = ll + OVERALLOC;
    dynstr *d = malloc(sizeof(dynstr) + (gcpc));
    d->sz = ll;
    d->cpc = gcpc; //up to 10 extra
    scpy(d->content, src);
    return d;
}

void append(dynstr * __restrict dst, char * __restrict add) {

}

void clear(dynstr * __restrict dst) {

}

void del(dynstr * __restrict dst) {

}
