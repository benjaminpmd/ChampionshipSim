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
    TeamItem teams = initTeamItem();

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
            teams = addTeam(teams, extractedString);
            counter++;
        }
        extractedString = strtok(NULL, ";");
    }

    while ((counter % 2) == 0) {
        counter /= 2;
    }
    if (counter != 1) {
        logCritical("Number of teams is not correct.");
        exit(EXIT_FAILURE);
    }

    return teams;
}

void updateOuputBuffer(char* buffer, char* firstTeamName, int firstTeamScore, char* secondTeamName, int secondTeamScore) {
    char result[BUFFER_SIZE];
    snprintf(result, BUFFER_SIZE, "%s;%d;%s;%d\n", firstTeamName, firstTeamScore, secondTeamName, secondTeamScore);
    strcat(buffer, result);
}

void simulateMatch(Team firstTeam, Team secondTeam, bool manualScoring, int bufferSemid, int scoringSemid, int matchDuration) {
    int firstTeamScore = 0;
    int secondTeamScore = 0;
    int clock = 0;
    struct timeval start, stop;
    long delta = 0;


    if (manualScoring) {
        printf("\nMatch %s - %s\n", firstTeam->name, secondTeam->name);
        printf("Please enter the score for the team %s: ", firstTeam->name);
        scanf(" %l[^\n]", &firstTeamScore);
        printf("Please enter the score for the team %s: ", secondTeam->name);
        scanf(" %l[^\n]", &firstTeamScore);
    }
    else {
        
        
        printf("Starting Match %s - %s\n", firstTeam->name, secondTeam->name);
        delta = random()%matchDuration;
        gettimeofday(&start, 0);
        while (clock < matchDuration) {
            usleep(delta);
            printf("Action in match %s - %s\n", firstTeam->name, secondTeam->name);
            gettimeofday(&stop, 0);
            clock += (stop.tv_usec - start.tv_usec+1000000.0 * (stop.tv_sec - start.tv_sec))/1000;
        }
    }
}

int runSimulation(char *inputPath, char *outputPath, bool manualScoring, bool graphical) {
    /* Creating teams list */
    TeamItem teams;
    /* Initiating match duration */
    int matchDuration;
    /* Initiating result buffer */
    char resultBuffer[BUFFER_SIZE] = "first_team_name;first_team_score;second_team_name;second_team_score\n";
    
    srandom(time(NULL));

    /* extract teams from file if path is not null */
    if (inputPath != NULL) {
        char buffer[BUFFER_SIZE];
        readFile(inputPath, buffer);
        teams = extractData(buffer, &matchDuration);
    }
    /* else use default values */
    else {
        char buffer[BUFFER_SIZE] = DEFAULT_VALUES;
        teams = extractData(buffer, &matchDuration);
    }

    /* Preparing semaphores */
    simKey = ftok("/tmp/match", 1);
    manKey;
    int simSemid = semalloc(simKey, 0);
    int manSemid;

    if (manualScoring) {
        logDebug("Init manual system sem");
        manKey = ftok("/tmp/input", 1);
        manSemid = semalloc(manKey, 1);
    }

    pid_t pids[getLength(teams)];
    int j = 0;
    printf("%d\n", getLength(teams));

    for (int i = 0; i < getLength(teams); i+=2) {
        pid_t pid = fork();

        if (pid == 0) {
            simulateMatch(getTeamAt(teams, i), getTeamAt(teams, i+1), manualScoring, simSemid, manSemid, matchDuration);
            return EXIT_SUCCESS;
        }
        else if (pid == -1) {
            logError("Could not fork the process for match simulation");
        }
        else {
            // IN THE MAIN PROCESS
            pids[j] = pid;
            j++;
        }
    }

    while((wpid = wait(&status)) > 0);

    /* write results into a file */
    writeFile(outputPath, resultBuffer);
}