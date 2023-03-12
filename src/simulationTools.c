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

    if (inputPath != NULL) {
        char buffer[BUFFER_SIZE];
        readFile(inputPath, buffer);
        teams = extractData(buffer, &matchDuration);
    }
    else {
        char buffer[BUFFER_SIZE] = DEFAULT_VALUES;
        teams = extractData(buffer, &matchDuration);
    }

    while (!isEmpty(teams)) {
        printf("%s\n", teams->team->name);
        teams = getNext(teams);
    }

    char *b = "team_1;score_team_1;team_2;score_team_2\nÉvreux;1;Cognac;2\nMont De Marsan;2;Orange;3\n";

    writeFile(outputPath, b);
}