#include "../include/ipcTools.h"
#include "../include/logger.h"

int semalloc(key_t key, int valInit) {
    
    /* creates the semaphore */
    int semaphore = semget(key, 1, IPC_CREAT | 0666);
    
    if (semaphore < 0) {
        /* if the semaphore id is 0, print an error */
        logError("Error while creating the semaphore");
        exit(EXIT_FAILURE);
    }

    /* create the union argument */
    union semun arg;

    /* set the init value of the union */
    arg.val = valInit;

    if (semctl(semaphore, 0, SETVAL, arg) < 0) {
        /* print the error in the error output */
        logError("Semaphore initialization failed");
        /* return -1 */
        return SEM_ERROR_CODE;
    }

    /* return the ID of the semaphore */
    return semaphore;
}

void P(int semid) {

    /* create the struct for the buffer */
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1; /* operation to do on semaphore */
    op.sem_flg = IPC_NOWAIT; /* flag : how to handle interruption */

    if(semop(semid, &op, 1) < 0) {
        /* decrement semaphore */
        fprintf(stderr, "Error while decrementing the semaphore");
    }
}

void V(int semid) {
    // create the struct for the buffer
    struct sembuf op = {0,1,IPC_NOWAIT};
    if(semop(semid, &op, 1) < 0) {
        //decrement semaphore
        fprintf(stderr, "Error while incrementing the semaphore");
    }
}

