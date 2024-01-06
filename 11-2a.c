#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int msqid;

    char pathname[] = "11-2a.c";

    key_t key;

    int len, maxlen;

    struct mymsgbuf {
        long mtype;
    } mybuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    printf("Program 1 started sending messages to 2.\n");
    for (int i = 0; i < 5; ++i) {
        mybuf.mtype = 1;
        len = 0;

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0) {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    printf("Program 1 finished sending messages to 2.\n");
    printf("Program 1 started receiving messages from 2.\n");

    for (int i = 0; i < 5; ++i) {
        maxlen = 0;
        if (len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0) < 0) {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        printf("Program 1 receives message with type = %ld.\n", mybuf.mtype);
    }

    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

    printf("Program 1 finished receiving messages from 2.\n");

    return 0;
}
