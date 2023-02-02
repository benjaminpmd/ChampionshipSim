#include "../include/fileManagement.h"
#include "../include/logger.h"

char* readFile(char* path) {
    FILE *f;
    char buffer[BUFFER_SIZE];

    f = fopen(path, "r");
    if (f == NULL) {
        char message[MAX_MESSAGE_SIZE];
        snprintf(message, MAX_MESSAGE_SIZE, "could not open the following path: %s\n", path);
        logError(message);
        exit(EXIT_SUCCESS);
    }

    while (fgets(buffer, BUFFER_SIZE, f) != NULL) {
      printf("%s", buffer);
    }
}

void writeFile(char* path, char* data) {}