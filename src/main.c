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


    for (int i = 0; i < argc; i++) {

        /* check if manual input of score is requested */
        if ((strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "--manual-scoring") == 0)) {
            manualScoring = true;
        }
        /* check if an input file is specified */
        else if ((strcmp(argv[i], "-i") == 0) || (strcmp(argv[i], "--input") == 0)) {
            if (i+1 < argc) {
                inputPath = argv[i+1];
            }
            else {
                puts("Incorrect input, seems like you forgot input path.");
            }
        }
        /* check if an output file is specified */
        else if ((strcmp(argv[i], "-o") == 0) || (strcmp(argv[i], "--output") == 0)) {
            if (i+1 < argc) {
                outputPath = argv[i+1];
            }
            else {
                puts("Incorrect output, seems like you forgot input path.");
            }
        }
    }

    runSimulation(inputPath, outputPath, manualScoring);

    return EXIT_SUCCESS;
}
