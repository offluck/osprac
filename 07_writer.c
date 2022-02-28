#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int shmid, shmid2;
    char pathname[] = "07_writer.c", pathname2[] = "07_reader.c";
    key_t key, key2;
    char *source_code;
    
    int size = 0;
    int *file_ptr, *file_ptr2;
    FILE *file;
    file = fopen(pathname, "r");
    
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);
    
    if ((key  = ftok(pathname, 0))  < 0 ||
        (key2 = ftok(pathname2, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    if ((shmid  = shmget(key,  sizeof(int),         0666|IPC_CREAT)) < 0 ||
        (shmid2 = shmget(key2, size * sizeof(char), 0666|IPC_CREAT)) < 0) {
        printf("Can\'t create shared memory\n");
        exit(-1);
    }
    if ((file_ptr  = (int*)shmat(shmid,  NULL, 0)) == (int*)(-1) ||
        (file_ptr2 = (int*)shmat(shmid2, NULL, 0)) == (int*)(-1)) {
        printf("Can't attach shared memory for size\n");
        exit(-1);
    }
    *file_ptr = size;
    source_code = (char*)file_ptr2;
    
    for (int i = 0; i < size; ++i) {
        source_code[i] = fgetc(file);
    }
    
    fclose(file);
    
    if (shmdt(file_ptr)  < 0 ||
        shmdt(file_ptr2) < 0) {
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    return 0;
}
