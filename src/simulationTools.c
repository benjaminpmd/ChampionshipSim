#include "../include/simulationTools.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"
#include "../include/structuresFunctions.h"
#include "../include/config.h"
#include "../include/ipcTools.h"

/**
 * Global variables
*/
static sem_t manSemid;

key_t manKey;

int status = 0;
pid_t wpid;

TeamItem extractData(char *buffer, int *matchDuration) {
    
    logInfo("Extracting teams");

    /* init the team list */
    TeamItem list = initTeamItem();

    /* number of team to check if the number of teams is power of two */
    int counter = 0;

    /* start dividing the content of the file to extract teams */
    char *extractedString = strtok(buffer, ";");

    /* loop through the string to extract all other tokens */
    while (extractedString != NULL) {
        /* check if the string represent the duration of a match simulation */
        if (strncmp(extractedString, "time=", strlen("time=")) == 0) {

            memmove(extractedString, extractedString + 5, strlen(extractedString) - 5 + 1);

            (*matchDuration) = atoi(extractedString);
        }
        else {
            list = addTeam(list, extractedString);
            counter++;
        }
        extractedString = strtok(NULL, ";");
    }

    while ((counter % 2) == 0) {
        counter /= 2;
    }
    if (counter != 1) {
        logCritical("Number of list is not correct.");
        exit(EXIT_FAILURE);
    }

    logInfo("All the teams have been extracted");

    return list;
}

void updateOuputBuffer(char* buffer, char* result) {
    strcat(buffer, result);
}

void simulateMatch(Team firstTeam, Team secondTeam, int manSemid, int msqid, int matchDuration) {
    
    /* initiating scores */
    setScore(firstTeam, 0);
    setScore(secondTeam, 0);

    /* initiating values for time management */
    float elapsedTime = 0;
    double deltaTime = 0;
    struct timeval startTime, stopTime;
    
    /* creation of the random number sequences */
    srand(time(0) + getpid());

    /* convert match duration to microseconds */
    matchDuration *= 1000000;

    /* check if manual scoring is enabled */
    if (manSemid != -1) {
        while (P(manSemid) == -1);
        printf("\nMatch %s - %s\n", firstTeam->name, secondTeam->name);
        printf("Please enter the score for the team %s: ", firstTeam->name);
        scanf("%d", &(firstTeam->score));
        printf("Please enter the score for the team %s: ", secondTeam->name);
        scanf("%d", &(secondTeam->score));
    }
    else {
        /* announcing beginning of the match */
        printf("\033[32mMATCH START: %s - %s\33[0m\n", getName(firstTeam), getName(secondTeam));
        
        /* start counting time passed in the match */
        gettimeofday(&startTime, 0);
        
        /* this loop simulate a match */
        while (elapsedTime < matchDuration) {
            
            /* calculate random wait before next action */
            deltaTime = rand() % matchDuration;

            /* if the time is more than the requested simulation time,
            then reduce delta time to match the end of simulation sime */
            if ((elapsedTime + deltaTime) > matchDuration) {
                deltaTime = matchDuration - elapsedTime;
            }
            
            /* wait the random time (in micro seconds) */
            usleep(deltaTime);
            
            /* attribute point */
            switch((random()%2)+1) {
                case 1:
                    incrementScore(firstTeam);
                    printf("\033[34mACTION: match %s - %s: %s has new score: %d\33[0m\n", getName(firstTeam), getName(secondTeam), getName(firstTeam), getScore(firstTeam));
                    break;
                case 2:
                    incrementScore(secondTeam);
                    printf("\033[34mACTION: match %s - %s: %s has new score: %d\33[0m\n", getName(firstTeam), getName(secondTeam), getName(secondTeam), getScore(secondTeam));
                    break;
                default:
                    logWarning("Trying to assign point to unknown team");
            }

            /* get stop time */
            gettimeofday(&stopTime, 0);

            /* calculate elapsed time */
            elapsedTime += (stopTime.tv_usec - startTime.tv_usec+1000000.0 * (stopTime.tv_sec - startTime.tv_sec));
        }
    }

    /* in case of equal score, attribute random point, it act like extension */
    if (getScore(firstTeam) == getScore(secondTeam)) {
        switch((random()%2)+1) {
            case 1:
                incrementScore(firstTeam);
                printf("\033[34mACTION: match %s - %s: %s has new score: %d\33[0m\n", getName(firstTeam), getName(secondTeam), getName(firstTeam), getScore(firstTeam));
                break;
            case 2:
                incrementScore(secondTeam);
                printf("\033[34mACTION: match %s - %s: %s has new score: %d\33[0m\n", getName(firstTeam), getName(secondTeam), getName(secondTeam), getScore(secondTeam));
                break;
            default:
                logWarning("Trying to assign point to unknown team");
        }
    }
    /* Section of the procedure that manage the return data */
    
    /* creating message structure */
    Message message;
    
    /* setting message type*/
    message.type = MSG_TYPE;
    
    /* setting message content depending on which team is winning and printing result */
    if (getScore(firstTeam) > getScore(secondTeam)) {
        printf("\33[33mMATCH END: %s has won against %s ( %d - %d )\33[0m\n", getName(firstTeam), getName(secondTeam), getScore(firstTeam), getScore(secondTeam));
        snprintf(message.message, MESSAGE_BUFFER_SIZE, "%s;%d;%s;%d\n", getName(secondTeam), getScore(secondTeam), getName(firstTeam), getScore(firstTeam)); 
    }
    
    else {
        printf("\33[33mMATCH END: %s has won against %s ( %d - %d )\33[0m\n", getName(secondTeam), getName(firstTeam), getScore(secondTeam), getScore(firstTeam));
        snprintf(message.message, MESSAGE_BUFFER_SIZE, "%s;%d;%s;%d\n", getName(firstTeam), getScore(firstTeam), getName(secondTeam), getScore(secondTeam)); 
    }

    if (manSemid != -1) {
        V(manSemid);
    }
    
    /* send the message */
    msqsend(msqid, message);
}

void runSimulation(char *inputPath, char *outputPath, bool manualScoring) {
    
    /* Creating list for extraction and sharing */
    TeamItem list;
    
    /* Initializing match duration */
    int matchDuration;
    
    /* Initializing result buffer */
    char resultBuffer[BUFFER_SIZE] = "team_that_lost;score_that_lost;team_that_won;score_that_won\n";

    /* Initializing semaphore */
    int manSemid = -1;

    /* Initializing values to check time */
    int elapsedTime = 0;
    int messageCounter = 0;
    struct timeval startTime, stopTime;

    /* extract list from file if path is not null */
    if (inputPath != NULL) {
        char readBuffer[BUFFER_SIZE];
        readFile(inputPath, readBuffer);
        list = extractData(readBuffer, &matchDuration);
    }
    /* else use default values */
    else {
        char readBuffer[BUFFER_SIZE] = DEFAULT_VALUES;
        list = extractData(readBuffer, &matchDuration);
    }

    /* creating semaphore in case of manual input */
    if (manualScoring) {
        manKey = ftok("/tmp/input", 1);
        manSemid = semalloc(manKey, 1);
    }

    /* preparing message queue */
    key_t msqkey = ftok(".", 65);

    /* check if message key have been created */
    if (msqkey == ERROR_CODE) {
        logError("could not create key");
        exit(EXIT_FAILURE);
    }

    int msqid = msgget(msqkey, 0666 | IPC_CREAT);
    if (msqid == ERROR_CODE) {
        logError("could not create message queue");
        exit(EXIT_FAILURE);
    }

    /* start counting time passed in the match */
    gettimeofday(&startTime, NULL);

    /* Start the championship simulation */
    while (getLength(list) > 1) {

        /* init the counter of process that will return a message */
        messageCounter = 0;

        /* count two by two to each time get two teams to create a match */
        for (int i = 0; i < getLength(list); i+=2) {
            
            /* fork the process */
            pid_t pid = fork();

            /* if the pid is 0 (this is the child), then simulate a match and exit */
            if (pid == 0) {
                /* call the function dedicated to the match simulation */
                simulateMatch(getTeamAt(list, i), getTeamAt(list, i+1), manSemid, msqid, matchDuration);
                /* exit the process once completed */
                exit(EXIT_SUCCESS);
            }
            else if (pid == -1) {
                /* in the case where pid is -1, then the fork failed */
                logError("Could not fork the process for match simulation");
                exit(EXIT_FAILURE);
            }
            else {
                /* else, we are in the parent process, then we increase the counter */
                messageCounter++;
            }
        }
        
        /* wait for all the process to complete */
        while((wpid = wait(&status)) > 0);

        /* for in in range 0 to messageCounter */
        for(int i = 0; i < messageCounter; i++) {
            /* create the message to retrieve */
            Message message = {0};

            /* read message in the queue */
            int success = msqrecv(msqid, &message);
            
            /* if the message is successfully read */
            if (success != ERROR_CODE) {
                
                /* create an iterator */
                TeamItem iterator = list;

                /* loop in the linked list to check if the team is the right one to remove or not */
                while(!isEmpty(iterator)) {
                    
                    /* compare the name of the team with the one to remove */
                    if (strncmp(getName(getTeam(iterator)), message.message, strlen(getName(getTeam(iterator)))) == 0) {
                        TeamItem tmp = iterator;
                        /* get the next team*/
                        iterator = getNext(iterator);
                        /* if this is the right team, remove it */
                        list = removeTeamItem(list, tmp);
                        /* exit the loop */

                    }
                    else {
                        /* get the next team*/
                        iterator = getNext(iterator);
                    }
                }
                /* update the buffer with the new data */
                updateOuputBuffer(resultBuffer, message.message);

            }
        }
    }

    printf("\n\033[1mRESULT: %s has won the championship ! Congrats !\33[0m\n\n", getName(getTeam(list)));

    /* get the time of the stop */
    gettimeofday(&stopTime, NULL);

    /* free the message queue */
    msqfree(msqid);

    /* free the semaphore is it have been used */
    if (manSemid != -1) {
        semfree(manSemid);
    }

    /* write results into a file */
    writeFile(outputPath, resultBuffer);
    
    /* calculate elapsed time */
    elapsedTime += (stopTime.tv_usec - startTime.tv_usec+1000000.0 * (stopTime.tv_sec - startTime.tv_sec))/1000;
    printf("✅ Championship simulation completed in %d seconds.\n", elapsedTime/1000);
}