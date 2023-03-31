#include "../include/fileManagement.h"
#include "../include/logger.h"

void readFile(char *path, char *buffer) {

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

void writeFile(char *path, char *buffer) {

  /* remove file content*/
  FILE *fp = fopen(path, "w");
  fclose(fp);
  logDebug("Reset output file content");

  int desc;

  desc = open(path, O_RDWR | O_CREAT, 0666);
  
  if (desc != -1) {
    write(desc, buffer, strlen(buffer));
    logDebug("Write buffer content");
  }
  else {
    logError("Error on open");
  }
  close(desc);
  logDebug("Close the file");
}