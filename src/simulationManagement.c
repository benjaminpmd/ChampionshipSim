#include "../include/simulationManagement.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"
#include "../include/libs.h"

Team* extractTeams(char* buffer) {
    printf("%s\n", buffer);
    Team* teams;
    return teams;
}

void simulate(char* inputPath, char* outputPath) {
    char buffer[MAX_MESSAGE_SIZE];
    readFile(inputPath, buffer);
    Team* teams = extractTeams(buffer);
}