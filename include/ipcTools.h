/**
 * File containing all the functions and structure declarations to manage inter process communication.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
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

#define MESSAGE_BUFFER_SIZE 1024

union semun {
    int val;    /* Value for SETVAL */
    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

/**
 * Structure of a message.
*/
typedef struct message {
  long type; /* type of the message */
  char message[MESSAGE_BUFFER_SIZE]; /* message */
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

/**
 * Function to allocate message queue memory.
 * 
 * @param key the key of the message queue.
 * @return the ID of the message queue if the operation was a success, -1 otherwise.
*/
int msqalloc(key_t key);

/**
 * Function to free message queue memory.
 * 
 * @param msqid the ID of the message queue.
 * @return 0 if the operation was a success, -1 otherwise.
*/
int msqfree (int msqid);

/**
 * Function to send a message through a message queue.
 * 
 * @param msqid the ID of the message queue.
 * @return 0 if the operation was a success, -1 otherwise.
*/
int msqsend(int msqid, Message message);

/**
 * Function to receive a message through a message queue.
 * 
 * @param msqid the ID of the message queue.
 * @return 0 if the operation was a success, -1 otherwise.
*/
int msqrecv(int msqid, Message *message);

#endif