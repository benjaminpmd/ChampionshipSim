#include "../include/simulationTools.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"
#include "../include/libs.h"
#include "../include/structuresFunctions.h"
#include "../include/config.h"

TeamList extractTeams(char* buffer) {
    TeamList teams = initTeamList();

    char* teamName = strtok(buffer, ";");
    // loop through the string to extract all other tokens
    while(teamName != NULL) {
       teams = addTeam(teams, teamName);
       teamName = strtok(NULL, ";");
    }

    return teams;
}

void saveResult(char* firstTeam, int scoreFirstTeam, char* secondTeam, int scoreSecondTeam) {
    
  char writeBuffer[BUFFER_SIZE];

  snprintf(writeBuffer, BUFFER_SIZE, "%s;%d;%s;%d\n", firstTeam, scoreFirstTeam, secondTeam, scoreSecondTeam);

  appendFile("./results/results.csv", writeBuffer);
}



void runSimulation(char* inputPath, char* outputPath, bool manualScoring, bool graphical) {
    TeamList teams;

    if (inputPath != NULL) {
        char buffer[BUFFER_SIZE];
        readFile(inputPath, buffer);
        teams = extractTeams(buffer);
    }
    else {
        char buffer[BUFFER_SIZE] = DEFAULT_VALUES;
        teams = extractTeams(buffer);
    }

    writeFile("./results/results.csv", "team_1;score_team_1;team_2;score_team_2");

    while (!isEmpty(teams)) {
        printf("%s\n", teams->team->name);
        saveResult(teams->team->name, 1, teams->team->name, 2);
        teams = getNext(teams);
    }
}