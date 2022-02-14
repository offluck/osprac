#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int fd[2], result;
    int fd_other[2];
    char resstring[14];
    char resstring_other[14];

    if (pipe(fd) < 0) {
        printf("Can\'t open pipe 1\n");
        exit(-1);
    }
    
    if (pipe(fd_other) < 0) {
        printf("Can\'t open pipe 2\n");
        exit(-1);
    }
    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {
        // Parent process.
        if (close(fd[0]) < 0) {
            printf("Parent: Can\'t close reading side of pipe №1\n");
            exit(-1);
        }
        write(fd[1], "Hello, world!", 14);
        printf("Parent wrote: %s\n", "Hello, world!");

        if (close(fd[1]) < 0) {
            printf("Parent: Can\'t close writing side of pipe №1\n");
            exit(-1);
        }
        printf("Parent exit\n");
    } else {
        // Child process.
        if (close(fd_other[0]) < 0) {
            printf("Child: Can\'t close reading side of pipe №2\n");
            exit(-1);
        }

        if (close(fd[1]) < 0) {
            printf("Child: Can\'t close writing side of pipe №1\n");
            exit(-1);
        }
        read(fd[0], resstring, 14);
        printf("Child read: %s\n", resstring);
        printf("Child exited resstring: %s\n", resstring);

        if (close(fd[0]) < 0) {
            printf("Child: Can\'t close reading side of pipe №1\n");
            exit(-1);
        }
        write(fd_other[1], "Bye-bye, end!", 14);
        printf("Child wrote: %s\n", "Bye-bye, end!");

        if (close(fd_other[1]) < 0) {
            printf("Child: Can\'t close writing side of pipe №2\n");
            exit(-1);
        }
    }
    sleep(1);
    if (result > 0) {
        if (close(fd_other[1]) < 0) {
            printf("Child: Can\'t close writing side of pipe №2\n");
            exit(-1);
        }
        read(fd_other[0], resstring_other, 14);
        printf("Parent reads string: %s\n", resstring_other);
        printf("Parent exit, resstring: %s\n", resstring_other);

        if (close(fd_other[0]) < 0) {
            printf("Parent: Can\'t close reading side of pipe №2\n");
            exit(-1);
        }
    }
    return 0;
}

