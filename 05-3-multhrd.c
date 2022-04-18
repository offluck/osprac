
  
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>

void reverse(char* str, size_t size) {
    for (int i = 0; i < size / 2; ++i) {
        char c = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = c;
    }
}

int main() {
    int    N;
    int    fd[2], result;

    size_t size;
    char   resstring[14];

    char   pathname[] = "05-3-multhrd.c";
    key_t  key;
    int    semid;
    struct sembuf sem_set = {0, 2, 0};
    struct sembuf sem_while = {0, 0, 0};
    struct sembuf sem_unset = {0, -1, 0};
    
    scanf("%d", &N);

    if (pipe(fd) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((semid = semget(key, 1, 0666)) < 0) {
        printf("Semaphore not found\n");
        if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
            printf("Can\'t create semaphore\n");
            exit(-1);
        }
        printf("Create successful!\n");
    }

    result = fork();

    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) {
        // процесс родителя
        for (int i = 0; i < N; ++i) {
            size = write(fd[1], "Hello, world!", 14);

            if (size != 14) {
                printf("Can\'t write all string\n");
                exit(-1);
            } else {
                printf("Parent wrote his message\n");
            }

            semop(semid, &sem_set, 1); // ребёнок запускается
            semop(semid, &sem_while, 1); // ждём, пока ребёнок напишет

            size = read(fd[0], resstring, 14);
            if (size < 0) {
                printf("Can\'t read string\n");
                exit(-1);
            }

            printf("Parent read: %s\n", resstring);
        }
        if (close(fd[1]) < 0) {
            exit(-1);
        }
        printf("Parent exit\n");
    } else {
        // процесс ребёнка
        for (int i = 0; i < N; ++i) {
            semop(semid, &sem_unset, 1);
            
            size = read(fd[0], resstring, 14);
            if (size < 0) {
                printf("Can\'t read string\n");
                exit(-1);
            }
            printf("Child read: %s\n", resstring);

            reverse(resstring, 13);
            size = write(fd[1], resstring, 14);
            
            if (size != 14) {
                printf("Can\'t write all string\n");
                exit(-1);
            } else {
                printf("Child wrote his message.\n");
            }
            
            semop(semid, &sem_unset, 1); // родитель читает
        }
        if (close(fd[0]) < 0) {
            exit(-1);
        }
        printf("Child exit\n");
    }

    return 0;
}
