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

void updateOuputBuffer(char* buffer, MatchResult match) {
    char result[BUFFER_SIZE];
    
    if (match->firstTeamScore > match->secondTeamScore) {
        snprintf(result, BUFFER_SIZE, "%s;%d;%s;%d;%s\n", match->firstTeam->name, match->firstTeamScore, match->secondTeam->name, match->secondTeamScore, match->firstTeam->name);
    }
    else {
        snprintf(result, BUFFER_SIZE, "%s;%d;%s;%d;%s\n", match->firstTeam->name, match->firstTeamScore, match->secondTeam->name, match->secondTeamScore, match->secondTeam->name);    
    }

    strcat(buffer, result);
}

void simulateMatch(Team firstTeam, Team secondTeam, bool manualScoring, key_t msqKey, int matchDuration) {
    Message message;
    message.type = MSG_TYPE;
    message.match->firstTeam = firstTeam;
    message.match->secondTeam = secondTeam;
    message.match->firstTeamScore = 0;
    message.match->secondTeamScore = 0;

    float clock = 0;
    struct timeval start, stop;
    double delta = 0;

    srand(time(0) + getpid());

    matchDuration *= 1000000;

    if (manualScoring) {
        printf("\nMatch %s - %s\n", firstTeam->name, secondTeam->name);
        printf("Please enter the score for the team %s: ", firstTeam->name);
        scanf(" %l[^\n]", &(message.match->firstTeamScore));
        printf("Please enter the score for the team %s: ", secondTeam->name);
        scanf(" %l[^\n]", &(message.match->secondTeamScore));
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
                    message.match->firstTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, firstTeam->name, message.match->firstTeamScore);
                    break;
                case 2:
                    message.match->secondTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, secondTeam->name, message.match->secondTeamScore);
                    break;
                default:
                    logWarning("Trying to attribute point to unknow team");
            }
            /* get stop time */
            gettimeofday(&stop, 0);
            /* calculate elapsed time */
            clock += (stop.tv_usec - start.tv_usec+1000000.0 * (stop.tv_sec - start.tv_sec));
        }

        if ((message.match->firstTeamScore) == (message.match->secondTeamScore)) {
            switch((random()%2)+1) {
                case 1:
                    message.match->firstTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, firstTeam->name, message.match->firstTeamScore);
                    break;
                case 2:
                    message.match->secondTeamScore++;
                    printf("Action in match %s - %s: %s new score: %d\n", firstTeam->name, secondTeam->name, secondTeam->name, message.match->secondTeamScore);
                    break;
                default:
                    logWarning("Trying to attribute point to unknow team");
            }
        }
        printf("Match end: %s %d - %d %s\n", firstTeam->name, message.match->firstTeamScore, message.match->secondTeamScore, secondTeam->name);

        msqsend(msqKey, message);
    }
}

int runSimulation(char *inputPath, char *outputPath, bool manualScoring, bool graphical) {
    /* Creating list list */
    TeamItem list;
    /* Initiating match duration */
    int matchDuration;
    /* Initiating result buffer */
    char resultBuffer[BUFFER_SIZE] = "first_team_name;first_team_score;second_team_name;second_team_score;winner\n";

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
    simKey = ftok("/tmp/match", 1);
    manKey;
    int simSemid = semalloc(simKey, 0);
    int manSemid;
    int clock = 0;
    struct timeval start, stop;

    if (manualScoring) {
        logDebug("Init manual system sem");
        manKey = ftok("/tmp/input", 1);
        manSemid = semalloc(manKey, 1);
    }

    /* start counting time passed in the match */
    gettimeofday(&start, NULL);

    /* Start the championship simulation */
    while (getActiveTeams(list) > 1) {
    
        for (int i = 0; i < getLength(list); i+=2) {

            char keyPath[10];
            snprintf(keyPath, 10, "/tmp/%d", i);

            printf("%s\n", keyPath);
            
            key_t msqKey = ftok("/tmp/", 'a');

            if (msqKey == -1) {
                logError("could not create key");
            }
            
            int msqid = msqalloc(msqKey);

            pid_t pid = fork();

            if (pid == 0) {
                simulateMatch(getTeamAt(list, i), getTeamAt(list, i+1), manualScoring, msqKey, matchDuration);
                return EXIT_SUCCESS;
            }
            else if (pid == -1) {
                logError("Could not fork the process for match simulation");
            }
            else {
                // IN THE MAIN PROCESS
                Message message;
                msqrecv(msqid, &message);

                updateOuputBuffer(resultBuffer, message.match);
            }
        }
        
        while((wpid = wait(&status)) > 0);
    }

    gettimeofday(&stop, NULL);
    /* calculate elapsed time */
    clock += (stop.tv_usec - start.tv_usec+1000000.0 * (stop.tv_sec - start.tv_sec))/1000;
    printf("Championship simulation completed in %d seconds.\n", clock/1000);

    /* write results into a file */
    writeFile(outputPath, resultBuffer);
}