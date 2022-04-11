#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    int   *array;
    int    shmid;
    int    new = 1;
    char   pathname[] = "07-3a.c";
    key_t  key;
    int    semid;
    struct sembuf sem_unset = {0, -1, 0};
    struct sembuf sem_set = {0, 1, 0};

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((shmid = shmget(key, 3 * sizeof(int), 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
        if (errno != EEXIST) {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } else {
            if ((shmid = shmget(key, 3 * sizeof(int), 0)) < 0) {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }

    if ((array = (int *) shmat(shmid, NULL, 0)) == (int *) (-1)) {
        printf("Can\'t attach shared memory\n");
        exit(-1);
    }

    if ((semid = semget(key, 1, 0666)) < 0) {
        printf("Semaphore not found\n");
        if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0) {
            printf("Can\'t create semaphore\n");
            exit(-1);
        }
        printf("Create successful!\n");
        semop(semid, &sem_set, 1);
    }

    printf("hello");
    if (new) {
        semop(semid, &sem_unset, 1);
        array[0] = 0;
        array[1] = 1;
        array[2] = 1;
        semop(semid, &sem_set, 1);
    } else {
        semop(semid, &sem_unset, 1);
        array[1] += 1;
        for (long i = 0; i < 2000000000L; ++i);
        array[2] += 1;
        semop(semid, &sem_set, 1);
    }

    semop(semid, &sem_unset, 1);
    printf
    ("Program 1 was spawn %d times, program 2 - %d times, total - %d times\n",
     array[0], array[1], array[2]);
    semop(semid, &sem_set, 1);

    if (shmdt(array) < 0) {
        printf("Can\'t detach shared memory\n");
        exit(-1);
    }

    return 0;
}
