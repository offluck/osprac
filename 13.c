#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd;

    char path_name[1024] = "for_links/a.txt";
    if ((fd = open(path_name, O_CREAT | O_EXCL, 0666)) < 0) {
        printf("Can\'t create file\n");
        exit(-1);
    }

    int counter = 0;
    char prev_name[1024] = "a.txt";
    char new_name[1024] = "a0";
    char s[1024];
    do {
        strcpy(s, "for_links/");
        strcat(s, new_name);
        if (symlink(prev_name, s) < 0) {
            printf("Error while creating a link\n");
            exit(-1);
        }
        ++counter;
        size_t destination_size = sizeof(new_name);
        
        strncpy(prev_name, new_name, destination_size);
        prev_name[destination_size - 1] = '\0';
        // prev_name = new_name
        
        strcpy(new_name, "a");
        
        char buffer[4];
        sprintf(buffer, "%d", counter);
        strcat(new_name, buffer);
        new_name[sizeof(new_name) - 1] = '\0';
        // new_name увеличилось
        if (close(fd) < 0) {
            exit(-1);
        }
    } while ((fd = open(s, O_RDONLY, 0666)) >= 0);

    printf("Counter: %d\n", counter - 1);
    return 0;
}
