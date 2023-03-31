#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/config.h"
#include "../include/simulationTools.h"
#include "../include/logger.h"

int main(int argc, char **argv) {

    // create the directory to store results
    system("mkdir -p results");
    system("mkdir -p tmp");

    // check if scoring is manual
    bool manualScoring = false;

    char* inputPath = NULL;
    char* outputPath = NULL;

    char commands[6][30] = {
        "-m",
        "--manual-scoring",
        "-i",
        "--input",
        "-o",
        "--output"
    };

    int commandsNb = sizeof(commands)/30;

    for (int i = 0; i < argc; i++) {

        /* check if manual input of score is requested */
        if ((strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "--manual-scoring") == 0)) {
            manualScoring = true;
        }
        /* check if an input file is specified */
        else if ((strcmp(argv[i], "-i") == 0) || (strcmp(argv[i], "--input") == 0)) {
            if (i+1 < argc) {
                bool isCommand = false;
                for (int j=0; j <commandsNb; j++) { 
                    if ((strcmp(argv[i+1], commands[j]) == 0)) {
                        isCommand = true;
                    }
                }
                if (!isCommand) {
                    inputPath = argv[i+1];
                }
                else {
                    puts("Incorrect input, seems like the path is incorrect.");
                    exit(EXIT_SUCCESS);
                }
            }
            else {
                puts("Incorrect input, seems like you forgot the input path.");
                exit(EXIT_SUCCESS);
            }
        }
        /* check if an output file is specified */
        else if ((strcmp(argv[i], "-o") == 0) || (strcmp(argv[i], "--output") == 0)) {
            if (i+1 < argc) {
                bool isCommand = false;
                for (int j=0; j <commandsNb; j++) { 
                    if ((strcmp(argv[i+1], commands[j]) == 0)) {
                        isCommand = true;
                    }
                }
                if (!isCommand) {
                    outputPath = argv[i+1];
                }
                else {
                    puts("Incorrect output, seems like the path is incorrect.");
                    exit(EXIT_SUCCESS);
                }
            }
            else {
                puts("Incorrect output, seems like you forgot the input path.");
                exit(EXIT_SUCCESS);
            }
        }
    }

    runSimulation(inputPath, outputPath, manualScoring);

    return EXIT_SUCCESS;
}
