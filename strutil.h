#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__
#define uint unsigned int

static inline uint mlen(char * __restrict p) {
    char * __restrict c = p;
    while (*p++);
    return p - c - 1;
}
static inline int mcmp(char * __restrict dst, char * __restrict src) {
    while (*dst && *src && (*dst == *src) && (dst++, src++));
    return *src - *dst;
}
static inline void scpy(char * __restrict dst, char * __restrict src) {
    while ((*dst++ = *src++));
}

#endif
