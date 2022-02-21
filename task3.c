#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    long long int ans = 0;
    int fd[2];
    size_t size = 1;
    char *resstring = malloc(sizeof(char));

    if (pipe(fd) < 0) {
        printf("Can\'t create pipe\n");
        exit(-1);
    }

    if (fcntl(fd[1], F_SETFL, fcntl(fd[1], F_GETFL) | O_NONBLOCK) == -1) {
        ans = -1;
    } else {
        while (size == 1) {
            size = write(fd[1], resstring, 1);
            ++ans;
        }
        --ans;
    }

    close(fd[0]);
    close(fd[1]);
    
    printf("The size of pipe is %lld bytes\n", ans);
    return 0;
}
