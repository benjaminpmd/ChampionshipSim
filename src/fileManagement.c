#include "../include/libs.h"
#include "../include/fileManagement.h"
#include "../include/logger.h"

void readFile(char* path, char* buffer) {

    /* init variables */
    FILE *fp;

    /* open the file to read it */
    fp = fopen(path, "r");

    /* check if the file pointer is null */
    if (fp == NULL) {
      /* log the message */
      logCritical("could not open the following path");
      /* exit the process */
      exit(EXIT_FAILURE);
    }

    /* if the function that gets the buffer returns is not null */
    if (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
      /* close the file pointer */
      fclose(fp);
      /* log the message */
      logDebug("Buffer loaded from the file");
    }
}

void writeFile(char* path, char* buffer) {
  /* init file pointer */
  FILE* fp;

  fp = fopen(path, "w");

  strncat(buffer, "\n", 2);

  fwrite(buffer, strlen(buffer), 1, fp);

}

void appendFile(char* path, char* buffer) {
  /* init file pointer */
  FILE* fp;

  fp = fopen(path, "a");

  strncat(buffer, "\n", 2);
  logDebug("Compiled");
  fwrite(buffer, strlen(buffer), 1, fp);
}