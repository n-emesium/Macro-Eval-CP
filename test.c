#include <stdio.h>
#include "memreq.h"

void crash() {
    while (1) {
        alloc(SCHUNK);
    }
}

int main() {
    // test for debugging
    // init();
    for (int i = 0; i < 10; i++) {
       // void *x = alloc(SCHUNK);
       // *(int *)x = i;
       // printf("%d\n", i);
       int *x = alloc(sizeof(int));
       *x = 6;
       int *y = alloc(sizeof(int));
       *y = 7;
       void *p = alloc(SCHUNK << 5);
        printf("x = %d, y = %d\n", *x, *y);
        printf("Addresses:\nAddr x: %p\nAddr y: %p\nAddr pointer: %p\n", x, y, p);
    }
    // afree();
    //uncomment the line under after debugging
    ffree();


    //remove after debugging:
    // crash();
    return -1;
}
