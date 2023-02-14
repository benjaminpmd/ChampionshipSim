#include "../include/config.h"
#include "../include/guiManagement.h"
#include "../include/simulationManagement.h"
#include "../include/libs.h"
#include "../include/logger.h"

int main(int argc, char **argv) {
    // init the variable that takes the choice of the user on which version of the app to run
    switch (argc) {
        case 2:
            if ((strcmp(argv[1], "--graphical") == 0) || (strcmp(argv[1], "-g") == 0)) {
                logDebug("starting GUI");
                runGui(argc, argv);
            }
            break;
        case 3:
            if (strcmp(argv[1], "-i") == 0) {
                logInfo("starting CLI with input file");
                ////////////////////////
                // TEST SECTION

                runSimulation(argv[2], DEFAULT_OUTPUT_PATH, false);
                
                // END OF TEST SECTION
                ////////////////////////
            }
            else if (strcmp(argv[1], "-o") == 0) {
                logInfo("starting CLI with output file");
            }
            else {
                logInfo("incorrect input on startup");
                printf("The parameters you specified are not correct.\n");
            }
            break;
        case 5:
            if ((strcmp(argv[1], "-i") == 0) || (strcmp(argv[1], "-o") == 0)) {
                logInfo("starting CLI with input and output files");
            }
            else if ((strcmp(argv[3], "-i") == 0) || (strcmp(argv[3], "-o") == 0)) {
                logInfo("starting CLI with input and output files");
            }
            else {
                logInfo("incorrect input on startup");
                printf("The parameters you specified are not correct.\n");
            }
            break;
        default:
            // default case to avoid any wrong input
            printf("The input you entered is not correct, please try again.\n");
            break;
    }
    return EXIT_SUCCESS;
}
