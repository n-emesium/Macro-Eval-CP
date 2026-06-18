#include <stdlib.h>
#include "lexer.h"
#include <stdio.h>
#include <fcntl.h>


void cstream_test() { //character stream test
puts("Starting character stream test:");
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

}


void fstream_test(char * __restrict fn) {
    char *st = start(fn);
    int fd = open(fn, O_WRONLY);
    include(st, fd);
    free(st);
}

int main() {
        puts("CHARACTER STREAM TEST FOR TOKENIZATION");
        cstream_test();
        for (int i = 0; i < 15; i++) putchar('\n');
        puts("FILE STREAM TEST FOR INCLUSION");
        fstream_test("test.txt");
        return 0;
}
