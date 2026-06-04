#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int awrite(int fd, char *buff);
int main(int argc, char *argv[]) {
    if (argc == 1) return -1;
    char * restrict p = argv[1];
    int fd = open(p, O_CREAT | O_RDWR, 0644);
    return 0;
}

int awrite(int fd, char *buff) {
    ssize_t read = 0;
    do {

    } while (read > 0);

}
