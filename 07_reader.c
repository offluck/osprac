#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *array;
    int shmid, shmid2;
    char pathname[] = "07_writer.c", pathname2[] = "07_reader.c";
    key_t key, key2;
    char *code;
    
    int size = 0;
    int *file_ptr, *file_ptr2;
    
    if ((key  = ftok(pathname, 0))  < 0 ||
        (key2 = ftok(pathname2, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if ((shmid = shmget(key, sizeof(int), 0)) < 0) {
        printf("Can\'t create shared memory for size\n");
        exit(-1);
    }
    if ((file_ptr = (int*)shmat(shmid, NULL, 0)) == (int*)(-1)) {
        printf("Can't attach shared memory for size\n");
        exit(-1);
    }
    size = *file_ptr;
    
    if ((shmid2 = shmget(key2, size * sizeof(char), 0)) < 0) {
        printf("Can\'t create shared memory for array\n");
        exit(-1);
    }
    if ((file_ptr2 = (int*)shmat(shmid2, NULL, 0)) == (int*)(-1)) {
        printf("Can't attach shared memory for array\n");
        exit(-1);
    }
    code = (char*)file_ptr2;
    puts(code);
    
    if (shmdt(file_ptr)  < 0 ||
        shmdt(file_ptr2) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    
    if (shmctl(shmid,  IPC_RMID, NULL) < 0 ||
        shmctl(shmid2, IPC_RMID, NULL) < 0) {
        printf("Can't delete shared memory\n");
        exit(-1);
    }
    return 0;
}
