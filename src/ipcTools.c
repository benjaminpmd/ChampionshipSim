#include "../include/ipcTools.h"
#include "../include/logger.h"

int semalloc(key_t key, int valInit) {
    
    /* creates the semaphore */
    int semid = semget(key, 1, IPC_CREAT | 0666);
    
    if (semid < 0) {
        /* if the semaphore id is 0, print an error */
        logError("Error while creating the semaphore");
        return ERROR_CODE;
    }

    /* create the union argument */
    union semun arg;

    /* set the init value of the union */
    arg.val = valInit;

    if (semctl(semid, 0, SETVAL, arg) < 0) {
        /* print the error in the error output */
        logError("Semaphore initialization failed");
        /* return -1 */
        return ERROR_CODE;
    }

    /* return the ID of the semaphore */
    return semid;
}

int P(int semid) {

    /* create the struct for the buffer */
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1; /* operation to do on semaphore */
    op.sem_flg = IPC_NOWAIT; /* flag : how to handle interruption */

    int res = semop(semid, &op, 1);

    if (res < 0) {
        return ERROR_CODE;
    }
    return 0;
}

int V(int semid) {

    /* create the struct for the buffer */
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1; /* operation to do on semaphore */
    op.sem_flg = IPC_NOWAIT; /* flag : how to handle interruption */

    int res = semop(semid, &op, 1);

    if (res < 0) {
        return ERROR_CODE;
    }
    return 0;
}

int semfree(int semid) {

    /* Release the semaphore */
    if (semctl(semid, 0, IPC_RMID, 0) == -1) {
        logError("Error releasing semaphore");
        return ERROR_CODE;
    }
    return 0;
}

int msqalloc(key_t key) {
    int msqid;

    // Create the message queue with the given key
    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) {
        logError("Error creating message queue");
        return ERROR_CODE;
    }

    return msqid;
}

int msqfree(int msqid) {
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        logError("could not free message queue");
    }
}

int msqsend(int msqid, Message message) {
    if (msgsnd(msqid, &message, sizeof(Message), 0) == -1) {
        logError("Could not send message to the queue");
        return ERROR_CODE;
    }
    return 0;
}

int msqrecv(int msqid, Message *message) {
    if(msgrcv(msqid, message, sizeof(Message), MSG_TYPE, 0) == -1) {
        logError("Could not receive message");
        return ERROR_CODE;
    }
    return 0;
}
