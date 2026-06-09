#include <stdlib.h>
#include "hasht.h"
#include <time.h>
#include <stdio.h>
#define BLEN 30



/*
 * unsigned int bucket[SCHUNK] = {0};
    srand(time(NULL));
    int d = 100;
    // cangetz();
    // return 0;
    for (int j = 0; j < d; j++) {
        int len = (rand() & 15) + 2;
        char buff[len];
        for (int i = 0; i < len - 1; i++) {
            buff[i] = (rand() & 1 ? 'a' : 'A') + (rand() % 26);
        }
        buff[len - 1] = '\0';
        printf("Selected string is: %s\n", buff);
        unsigned short h16 = hash16(buff);
        printf("Corresponding hash is %hu\n", h16);
        bucket[h16]++;
    }
    // return 0;
    uint uniq = 0;
    for (int i = 0; i < SCHUNK; i++) {
        if (bucket[i]) printf("Bucket index %d got rolled %u times.\n", i, bucket[i]), uniq++;
    }
    printf("%u many unique values.\n", uniq);
    return 0;
 *
 * */


void populate(char * restrict p) {
    for (int i = 0; i < BLEN - 1; i++) {
        p[i] = (rand() & 1 ? 'a' : 'A') + (rand() % 26);
    }
}


void test() {
    srand(time(NULL));
    hasht* ht = maket();
    // int d = 100;
    int d = 5;
    for (int j = 0; j < d; j++) {
        printf("Iteration %d\n", j + 1);
        int len = (rand() & 15) + 2;
        char buff[len];
        for (int i = 0; i < len - 1; i++) {
            buff[i] = (rand() & 1 ? 'a' : 'A') + (rand() % 26);
        }
        buff[len - 1] = '\0';
        printf("String chosen is %s, hash is %hu\n", buff, h16(buff));
        char wrt[BLEN] = {'\0'};
        populate(wrt);
        // sprintf(wrt, "|| string number %d  ", j);
        printf("does the string work? it should be %s\n", wrt);
        inject(buff, wrt, ht);
        //
        puts("Printing table");
        ptable(ht);
        puts("Ended printing table");
        printf("Fetched value is %s\n\n", fetch(buff, ht));
    }
    // ptable(ht);
    ftable(ht);
}


int main() {
    test();
    return 0;
}
