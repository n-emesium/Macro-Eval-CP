#include <stdio.h>
#include <stdlib.h>
#include "hasht.h"
#include <time.h>

void cangetz() {
    while (1) {
        char c = (rand() & 1 ? 'a' : 'A') + (rand() % 26);
        if (c == 'z' || c == 'Z') {
            puts("Letter Z was reached");
            return;
        }
    }
}


int main() {
    unsigned int bucket[SCHUNK] = {0};
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
}
