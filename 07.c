#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy) {
    pthread_t mythid = pthread_self();
    a += 1;
    printf("Thread: %u\nResult: %d\n", mythid, a);
    return NULL;
}

int main() {
    pthread_t thid[2], mythid;
    int       result;

    for (int i = 0; i < 2; ++i) {
        result = pthread_create (&thid[i], (pthread_attr_t *) NULL, mythread, NULL);
        if (result != 0) {
            printf ("Error on thread create, return value = %d\n", result);
            exit(-1);
        }
        printf("Thread %d created, thid = %u\n", i + 1, thid[0]);
    }

    mythid = pthread_self();
    a += 1;
    printf("Thread: %u\nResult: %d\n", mythid, a);
    
    for (int i = 0; i < 2; ++i) {
        pthread_join(thid[i], (void **) NULL);
    }
    return 0;
}

