#include "../include/simulationTools.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"
#include "../include/structuresFunctions.h"
#include "../include/config.h"
#include "../include/ipcTools.h"

/**
 * Global variables
*/
static sem_t simSemid;
static sem_t manSemid;

key_t simKey;
key_t manKey;

int status = 0;
pid_t wpid;

TeamItem extractData(char *buffer, int *matchDuration)
{
    TeamItem list = initTeamItem();

    char durationTimeBuffer[10];

    int counter = 0;

    char *extractedString = strtok(buffer, ";");
    // loop through the string to extract all other tokens
    while (extractedString != NULL) {
        if (strncmp(extractedString, "time=", strlen("time=")) == 0) {

            memmove(extractedString, extractedString + 5, strlen(extractedString) - 5 + 1);

            (*matchDuration) = atoi(extractedString);
        }
        else
        {
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

    return list;
}

void updateOuputBuffer(char* buffer, char* result) {
    strcat(buffer, result);
}

void simulateMatch(Team firstTeam, Team secondTeam, bool manualScoring, int msqid, int matchDuration) {
    
    /* initiating scores */
    int firstTeamScore = 0;
    int secondTeamScore = 0;

    /* initiating values for time management */
    float clock = 0;
    double delta = 0;
    struct timeval start, stop;
    
    /* creation of the random number sequences */
    srand(time(0) + getpid());

    /* convert match duration to microseconds */
    matchDuration *= 1000000;

    /* check if manual scoring is enabled */
    if (manualScoring) {
        printf("\nMatch %s - %s\n", firstTeam->name, secondTeam->name);
        printf("Please enter the score for the team %s: ", firstTeam->name);
        scanf(" %l[^\n]", &firstTeamScore);
        printf("Please enter the score for the team %s: ", secondTeam->name);
        scanf(" %l[^\n]", &secondTeamScore);
    }

    else {
        /* announcing beginning of the match */
        printf("Starting Match %s - %s\n", firstTeam->name, secondTeam->name);
        /* start counting time passed in the match */
        gettimeofday(&start, 0);
        /* this loop simulate a match */
        while (clock < matchDuration) {
            /* calculate random wait before next action */
            delta = rand()%matchDuration;
            if (clock+delta > matchDuration) {
                delta = matchDuration - clock;
            }
            /* wait the random time (in micro seconds) */
            usleep(delta);
            /* attribute point */
            switch((random()%2)+1) {
                case 1:
                    firstTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, firstTeam->name, firstTeamScore);
                    break;
                case 2:
                    secondTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, secondTeam->name, secondTeamScore);
                    break;
                default:
                    logWarning("Trying to attribute point to unknow team");
            }
            /* get stop time */
            gettimeofday(&stop, 0);
            /* calculate elapsed time */
            clock += (stop.tv_usec - start.tv_usec+1000000.0 * (stop.tv_sec - start.tv_sec));
        }

        if (firstTeamScore == secondTeamScore) {
            switch((random()%2)+1) {
                case 1:
                    firstTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, firstTeam->name, firstTeamScore);
                    break;
                case 2:
                    secondTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, secondTeam->name, secondTeamScore);
                    break;
                default:
                    logWarning("Trying to attribute point to unknow team");
            }
        }
        printf("Match end: %s %d - %d %s\n", firstTeam->name, firstTeamScore, secondTeamScore, secondTeam->name);

        /* Section of the procedure that manage the return data */
        /* creating message structure */

        Message message;

        /* setting message type*/
        message.type = MSG_TYPE;

        /* setting message content depending on which team is winning */
        if (firstTeamScore > secondTeamScore) {
            snprintf(message.message, MESSAGE_BUFFER_SIZE, "%s;%s;%d;%s;%d\n", secondTeam->name, firstTeam->name, firstTeamScore, secondTeam->name, secondTeamScore);
        }
        else {
            snprintf(message.message, MESSAGE_BUFFER_SIZE, "%s;%s;%d;%s;%d\n", firstTeam->name, firstTeam->name, firstTeamScore, secondTeam->name, secondTeamScore); 
        }

        /* send the message */
        msgsnd(msqid, &message, sizeof(struct message), 0);
    }
}

int runSimulation(char *inputPath, char *outputPath, bool manualScoring, bool graphical) {
    
    /* Creating list for extraction and sharing */
    TeamItem list;
    
    /* Initiating match duration */
    int matchDuration;
    
    /* Initiating result buffer */
    char resultBuffer[BUFFER_SIZE] = "looser;first_team_name;first_team_score;second_team_name;second_team_score\n";

    /* extract list from file if path is not null */
    if (inputPath != NULL) {
        char buffer[BUFFER_SIZE];
        readFile(inputPath, buffer);
        list = extractData(buffer, &matchDuration);
    }
    /* else use default values */
    else {
        char buffer[BUFFER_SIZE] = DEFAULT_VALUES;
        list = extractData(buffer, &matchDuration);
    }

    /* Preparing semaphores */
    simKey = ftok("/tmp/result", 1);
    int simSemid = semalloc(simKey, 0);

    int manSemid;
    
    /* init values to check time */
    int clock = 0;
    int j = 0;
    struct timeval start, stop;

    if (manualScoring) {
        logDebug("Init manual system sem");
        manKey = ftok("/tmp/input", 1);
        manSemid = semalloc(manKey, 1);
    }

    /* preparing message queue */
    key_t msqKey = ftok(".", 65);

    if (msqKey == -1) {
        logError("could not create key");
        exit(EXIT_FAILURE);
    }

    int msqid = msgget(msqKey, 0666 | IPC_CREAT);

    /* start counting time passed in the match */
    gettimeofday(&start, NULL);

    printf("%d\n", getLength(list));

    /* Start the championship simulation */
    while (getLength(list) > 1) {


        j=0;
    
        for (int i = 0; i < getLength(list); i+=2) {
            
            pid_t pid = fork();

            if (pid == 0) {
                simulateMatch(getTeamAt(list, i), getTeamAt(list, i+1), manualScoring, msqid, matchDuration);
                return EXIT_SUCCESS;
            }
            else if (pid == -1) {
                logError("Could not fork the process for match simulation");
            }
            else {
                j++;
            }
        }
        
        while((wpid = wait(&status)) > 0);

        for(int i = 0; i < j; i++) {
            
            
            Message message = {0};


            msgrcv(msqid, &message, sizeof(struct message), MSG_TYPE, IPC_NOWAIT);

            TeamItem iterator = list;
            TeamItem previous = list;

            logDebug(message.message);

            while(hasNext(iterator)) {

                if (strncmp(getTeamName(getTeam(iterator)), message.message, strlen(getTeamName(getTeam(iterator)))) == 0) {
                    list = removeTeamItem(list, iterator);
                    break;
                    // CHECK THE NEXT ITEM
                }
                else {
                    previous = iterator;
                }
                iterator = getNext(iterator);
            }

            updateOuputBuffer(resultBuffer, message.message);
            
        }
        printTeamItem(list);
        printf("%d\n", getLength(list));
    }

    msqfree(msqid);
    gettimeofday(&stop, NULL);
    /* calculate elapsed time */
    clock += (stop.tv_usec - start.tv_usec+1000000.0 * (stop.tv_sec - start.tv_sec))/1000;
    printf("Championship simulation completed in %d seconds.\n", clock/1000);

    /* write results into a file */
    writeFile(outputPath, resultBuffer);
}