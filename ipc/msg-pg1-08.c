//the producer

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

    // Create or open the message queue
    msqid = msgget(MESSAGE_KEY, IPC_CREAT | 0666);
    if (msqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Prepare the message
    msg.type = MESSAGE_TYPE;
    snprintf(msg.text, MESSAGE_SIZE, "Hello from the producer!");

    // Send the message to the message queue
    if (msgsnd(msqid, &msg, sizeof(msg.text), 0) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Producer: Message sent successfully.\n");

    return 0;
}

