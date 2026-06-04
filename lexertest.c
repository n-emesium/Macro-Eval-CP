#include "lexer.h"
#include <stdio.h>

int main() {
    // Cleaner syntax, explicitly preserves newlines, safe from indentation bugs
    char *buff = "##name ege\n"
                 "##age 20\n"
                 "##mood nice\n"
                 "hey i am name, i am age years old\n"
                 "mood to meet you!\n";
    puts("Setting up tokens");
    token *tokens = test_stream(buff);
    puts("\n\nPrinting tokens");
    tokprint(tokens);
    puts("\n\nFreeing Tokens");
    tfree(tokens);
    return 0;
}
