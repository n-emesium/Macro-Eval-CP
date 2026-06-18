#ifndef __LEXER_H__
#define __LEXER_H__
#include <stdio.h>
#include "token.h"

// typedef enum {
//     WORD,
//     MACRO
//     // WHITESPACE
// } tt; //token type

// typedef struct token {
//     tt type;
//     char *content;
//     struct token *next;
// } token;

/*
 * NOTES:
 * This function seems to be redundant, for stdio FILE * is not necessary. Instead the logic is handled via integer file descriptors as per the POSIX standard. token *stream should therefore not be used, it should instead be called to a char * with the start() function as described below.
 *
 * */
// token* stream(FILE * __restrict fp);

token* test_stream(char * __restrict);

// void tfree(token * __restrict t);

/*
 * The syntax for an inclusion command is !!, this was chosen for no particular reason, seeing as how ## was already used for definition, and keywords are unnecessary, use !! for an inclusion of a file. The OS itself will resolve the filenames, as in putting paths should be allowed, but the idea is that even for basic local file paths full file specification should not be necessary.
 * The behavior should behave depending on whether a full path is given or not.
 *
 * */
void include(char * __restrict r, char * __restrict fn); //potentially resized

token* parser(char * __restrict r);



char *start(char * __restrict fn); //given a file descriptor fd, it will return a pointer to the start of it



/*
 * The main function that expands everything and writes back to the file.
 * The idea is that after tokenization, it expands properly, and writes the new results to the file in one go, thus not requiring multiple dirty writes for 1 file. There should be 1 call for this.
 *
 * */
void expand(char * __restrict fn);



#endif
