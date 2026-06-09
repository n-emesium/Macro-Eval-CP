#include "lexer.h"
#include <stdio.h>

int main() {
    token *(*fp)(char * __restrict r);
    //you can use test_stream as well
    fp = parser;
    // Cleaner syntax, explicitly preserves newlines, safe from indentation bugs
    char *buff = "##name ege\n"
                 "##age 20\n"
                 "##mood nice\n"
                 "##country United States of America\n"
                 "hey i am name, i am age years old\n"
                 "mood to meet you!\n"
                 "I am from country!\n"
                 "##something hamburger\n"
                 ;
    puts("Setting up tokens");
    token *tokens = fp(buff);
    puts("\n\nPrinting tokens");
    tokprint(tokens);
    puts("\n\nFreeing Tokens");
    tfree(tokens);
    return 0;
}
