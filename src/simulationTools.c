#include "../include/simulationTools.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"
#include "../include/libs.h"
#include "../include/structuresFunctions.h"

TeamList extractTeams(char* buffer) {
    TeamList teams;

    char* teamName = strtok(buffer, ";");
    // loop through the string to extract all other tokens
    while(teamName != NULL) {
       teams = addTeam(teams, teamName);
       teamName = strtok(NULL, ";");
    }

    return teams;
}

void runSimulation(char* inputPath, char* outputPath, bool manualScoring) {
    char buffer[MAX_MESSAGE_SIZE];
    readFile(inputPath, buffer);
    TeamList teams = extractTeams(buffer);

    //writeFile("./results.csv", "teams names");

    while (!isEmpty(teams)) {
        printf("%s\n", teams->team->name);
        teams = getNext(teams);
    }
}