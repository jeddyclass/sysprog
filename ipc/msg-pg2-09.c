// the consumer
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MESSAGE_SIZE 128
#define MESSAGE_TYPE 1
#define MESSAGE_KEY 1234

struct message {
    long type;
    char text[MESSAGE_SIZE];
};

int main() {
    int msqid;
    struct message msg;

    // Open the message queue
    msqid = msgget(MESSAGE_KEY, 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Receive the message from the message queue
    if (msgrcv(msqid, &msg, sizeof(msg.text), MESSAGE_TYPE, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Consumer: Received message: %s\n", msg.text);

    return 0;
}


