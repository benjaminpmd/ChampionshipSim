#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/config.h"
#include "../include/simulationTools.h"
#include "../include/logger.h"

char *filePath;

int main(int argc, char **argv)
{

    // create the directory to store results
    system("mkdir -p results");

    // check if scoring is manual
    bool manualScoring = false;

    for (int i = 0; i < argc; i++)
    {
        if ((strcmp(argv[i], "-m") == 0) || (strcmp(argv[i], "--manual-scoring") == 0))
        {
            manualScoring = true;
        }
    }

    // init the variable that takes the choice of the user on which version of the app to run
    switch (argc)
    {
    case 3:
        if (strcmp(argv[1], "-i") == 0)
        {
            logInfo("starting CLI with input file");
            runSimulation(argv[2], DEFAULT_OUTPUT_PATH, manualScoring, false);
        }
        else if (strcmp(argv[1], "-o") == 0)
        {
            logInfo("starting CLI with output file");
            runSimulation(NULL, argv[2], manualScoring, false);
        }
        else
        {
            logInfo("incorrect input on startup");
            printf("The parameters you specified are not correct.\n");
        }
        break;
    case 5:
        if ((strcmp(argv[1], "-i") == 0) && (strcmp(argv[3], "-o") == 0))
        {
            logInfo("starting CLI with input and output files");
            runSimulation(argv[2], argv[4], manualScoring, false);
        }
        else if ((strcmp(argv[1], "-o") == 0) || (strcmp(argv[3], "-i") == 0))
        {
            logInfo("starting CLI with input and output files");
            runSimulation(argv[4], argv[2], manualScoring, false);
        }
        else
        {
            logInfo("incorrect input on startup");
            printf("The parameters you specified are not correct.\n");
        }
        break;
    default:
        logInfo("starting CLI without input");
        runSimulation(NULL, DEFAULT_OUTPUT_PATH, manualScoring, false);
        break;
    }
    return EXIT_SUCCESS;
}
