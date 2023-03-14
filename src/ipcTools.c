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

    if(semop(semid, &op, 1) < 0) {
        /* decrement semaphore */
        logError("Error while decrementing the semaphore");
        return ERROR_CODE;
    }
    return 0;
}

int V(int semid) {

    /* create the struct for the buffer */
    struct sembuf op = {0,1,IPC_NOWAIT};

    if(semop(semid, &op, 1) < 0) {
        //decrement semaphore
        logError("Error while incrementing the semaphore");
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

void* shmalloc(key_t key, int size) {
    int shmid;
    void* shmaddr;

    shmid = shmget(key, size | SHM_SIZE, IPC_CREAT | 0666);

    printf("%d\n", shmid);

    if (shmid == -1) {
        logError("Could not create shared memory");
        return 0;
    }

    shmaddr = shmat(shmid, NULL, 0);
    if (shmaddr == (void*) -1) {
        logError("Could not attach shared memory segment");
        return 0;
    }
    return shmaddr;
}

int shmfree(key_t key) {
    int shmid;

    shmid = shmget(key, 0, IPC_CREAT | 0666);

    printf("%d\n", shmid);

    if (shmid == -1) {
        logError("Error getting shared memory segment ID");
        return ERROR_CODE;
    }
    if(shmctl(shmid, IPC_RMID, 0) == -1) {
        logError("Error removing shared memory segment");
        return ERROR_CODE;
    }
    return 0;
}

int msgalloc(key_t key) {
    int msgid;

    // Create the message queue with the given key
    msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        logError("Error creating message queue");
        return 0;
    }

    return msgid;
}

int msgfree(int msgqid);

int msgsend(int msqid, char* msg, int msgSize);

int msgrecv(int msqid, char* msg, int msgSize);
