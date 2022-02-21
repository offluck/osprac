#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int fd, result;
    size_t size;
    char resstring[14];
    char name[] = "test.fifo";
    (void) umask(0);

    printf("Reading data from FIFO\n");

    if ((fd = open(name, O_RDONLY)) < 0) {
        printf("Can\'t open FIFO for reading\n");
        exit(-1);
    }

    size = read(fd, resstring, 14);
    printf("End of reading from FIFO\n");

    if (size < 0) {
        printf("Can\'t read string\n");
        exit(-1);
    }

    printf("Read from FIFO: %s\n", resstring);
    close(fd);
    printf("Reader exited\n");
    return 0;
}
