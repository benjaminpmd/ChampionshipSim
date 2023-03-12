#include "../include/simulationTools.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"
#include "../include/structuresFunctions.h"
#include "../include/config.h"

TeamList extractData(char *buffer, int *matchDuration)
{
    TeamList teams = initTeamList();

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

void simulateMatch(Team firstTeam, Team secondTeam, bool manualScoring, int bufferSemid, int scoringSemid)
{
    int firstTeamScore = 0;
    int secondTeamScore = 0;

    if (manualScoring)
    {
        printf("Match %s - %s\n", firstTeam->name, secondTeam->name);
        printf("Please enter the score for the team %s: ", firstTeam->name);
        scanf("%d", &firstTeamScore);
        printf("Please enter the score for the team %s: ", secondTeam->name);
        scanf("%d", &firstTeamScore);
    }
    else
    {
        // TODO: automatic match generation
    }
}

void runSimulation(char *inputPath, char *outputPath, bool manualScoring, bool graphical) {
    TeamList teams;
    int matchDuration;
    char resultBuffer[BUFFER_SIZE] = "first_team_name;first_team_score;second_team_name;second_team_score\n";

    if (inputPath != NULL) {
        char buffer[BUFFER_SIZE];
        readFile(inputPath, buffer);
        teams = extractData(buffer, &matchDuration);
    }
    else {
        char buffer[BUFFER_SIZE] = DEFAULT_VALUES;
        teams = extractData(buffer, &matchDuration);
    }

    TeamList t = teams;

    while (!isEmpty(teams)) {
        printf("%s\n", teams->team->name);
        teams = getNext(teams);
    }

    updateOuputBuffer(resultBuffer, t->team->name, 2, getNext(t)->team->name, 4);

    writeFile(outputPath, resultBuffer);
}