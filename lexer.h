#ifndef __LEXER_H__
#define __LEXER_H__
#define ushort unsigned short
#define REG 0
#define MAC 1
struct mac;
typedef struct token {
    char tt;
    char *key;
    struct mac* maci; //macro if
    struct token* next;
} token;
typedef struct mac { //metadata
    ushort hash;
    char *val;
} mac;
#endif
