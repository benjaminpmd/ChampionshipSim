#ifndef __IPCTOOLS__
#define __IPCTOOLS__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <sys/time.h>
#include "structures.h"

#define ERROR_CODE -1

#define MSG_TYPE 1

#define SHM_SIZE 1024

union semun {
    int val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

typedef struct message {
  long type;
  MatchResult match;
} Message;

/**
 * Creates a semaphore and returns -1 in case of errors, 0 else.
 * 
 * @param key the semaphore key.
 * @param valInit the init val.
 * @return an integer, 0 if no errors.
 */
int semalloc(key_t key, int valInit);


/*implémentent les deux opérations principales vues en cours sur les sémaphores.*/

/**
 * Decrements semaphore if strictly positive value.
 *
 * @param semid the semaphore id.
 */
int P(int semid);

/**
 * Increments semaphore.
 *
 * @param semid the semaphore id.
 */
int V(int semid);

/**
 * Frees the semaphore passed in parameter.
 * Returns -1 if it's already been freed, 0 else.
 *
 * @param semid the semaphore id.
 * @return an integer which is -1 if it's already been freed, 0 otherwise.
 */
int semfree(int semid);

void* shmalloc(key_t key, int size);

int shmfree(key_t key);

int msqalloc(key_t key);

int msqfree (int msgqid);

int msqsend(int msqid, Message message);

int msqrecv(int msqid, Message *message);

#endif