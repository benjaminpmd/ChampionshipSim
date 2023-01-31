#include "../include/gui.h"
#include "../include/libs.h"
#include "../include/logger.h"

int main(int argc, char **argv) {
    logDebug("Salut");
    // init the variable that takes the choice of the user on which version of the app to run
    int userInput = 0;
    
    while ((userInput != 1) && (userInput != 2)) {
        // ask the user what version must be used
        printf("> Select the version of the app to use:\n1: CLI version\n2: GUI version\nChoice (1 or 2): ");
        scanf("%d", &userInput);
        // act depending on the user input
        switch (userInput) {

        case 1:
            // case one is cli
            printf("Command currently unavailable.\n");
            break;
        
        case 2:
            // case two is GUI
            runGui(argc, argv);
            break;

        default:
            // default case to avoid any wrong input
            printf("The input you entered is not correct, please try again.\n");
            break;
        }
    }
    return EXIT_SUCCESS;
}
