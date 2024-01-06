#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int msqid;

    char pathname[] = "11-3server.c";

    key_t key;

    int len, maxlen;

    struct clientmsgbuf {
        long mtype;
        struct {
            pid_t pid;
            float message;
        } info;
    } clientbuf;

    struct servermsgbuf {
        long mtype;
        struct {
            float message;
        } info;
    } serverbuf;

    if ((key = ftok(pathname, 0)) < 0) {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) < 0) {
        printf("Can\'t get msqid\n");
        exit(-1);
    }

    clientbuf.mtype = 1;
    clientbuf.info.pid = getpid();

    printf("Enter float number:\n");
    scanf("%f", &clientbuf.info.message);
    printf("%.3f\n", clientbuf.info.message);
    len = sizeof(clientbuf.info);

    printf("Client %d sends message %.3f\n", clientbuf.info.pid, clientbuf.info.message);
    if (msgsnd(msqid, (struct clientmsgbuf *) &clientbuf, len, 0) < 0) {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }
    printf("Waiting for response...\n");

    maxlen = sizeof(serverbuf.info);
    if (len = msgrcv(msqid, &serverbuf, maxlen, getpid(), 0) < 0) {
        printf("Can\'t receive message from queue\n");
        exit(-1);
    }

    printf("Server: %.3f\n", serverbuf.info.message);
    return 0;
}
