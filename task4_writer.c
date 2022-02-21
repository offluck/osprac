#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd, result;
    size_t size;
    char resstring[14];
    char name[] = "test.fifo";
    (void) umask(0);

    if (mknod(name, S_IFIFO | 0666, 0) < 0) {
        printf("Can\'t create FIFO\n");
        exit(-1);
    }

    printf("Started writing to FIFO\n");
    if ((fd = open(name, O_WRONLY)) < 0) {
        printf("Can\'t open FIFO for writing\n");
        exit(-1);
    }

    size = write(fd, "Hello, world!", 14);
    printf("Ended writing to FIFO\n");

    if (size != 14) {
        printf("Problems with writing the string to FIFO\n");
        exit(-1);
    }
    
    close(fd);
    printf("Writer exited\n");
    return 0;
}
