#include "../include/simulationManagement.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"
#include "../include/libs.h"

Team* extractTeams(char* buffer) {
    printf("%s\n", buffer);
    Team* teams;
    return teams;
}

void runSimulation(char* inputPath, char* outputPath, bool manualScoring) {
    char buffer[MAX_MESSAGE_SIZE];
    readFile(inputPath, buffer);
    Team* teams = extractTeams(buffer);
}