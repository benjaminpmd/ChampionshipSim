#include "../include/logger.h"

void saveData(char* data) {

    if (SAVE_DATA) {

        FILE *fp = fopen(LOG_FILE_PATH, "a");

        if (fp == NULL) {
            system("mkdir -p logs");
            fp = fopen(LOG_FILE_PATH, "a");
        }
        if (fp != NULL) {
            /* append the data */
            fputs(data, fp);
            /* close the file */
            fclose(fp);
        }
    }
}


void logDebug(char *message) {
    // check if the level select is lower than the level of the function
    if (LEVEL <= DEBUG) {
        // if the level is lower create the variables to use
        char data[MAX_MESSAGE_SIZE], timeString[30];
        // extract current time
        time_t timestamp = time(NULL);
        struct tm *ptime = localtime(&timestamp);
        
        // format current time
        strftime(timeString, 30, "%d/%m/%Y %H:%M:%S", ptime);
        
        // format the data to save
        snprintf(data, MAX_MESSAGE_SIZE, "%s - DEBUG: %s\n", timeString,  message);
        
        // if the option to print datas is enable, print data
        if (PRINT_DATA) {
            fprintf(stdout, "%s", data);
        }

        saveData(data);
    }
}

void logInfo(char *message) {
    // check if the level select is lower than the level of the function
    if (LEVEL <= INFO) {
        // if the level is lower create the variables to use
        char data[MAX_MESSAGE_SIZE], timeString[30];
        // extract current time
        time_t timestamp = time(NULL);
        struct tm *ptime = localtime(&timestamp);
        
        // format current time
        strftime(timeString, 30, "%d/%m/%Y %H:%M:%S", ptime);
        
        // format the data to save
        snprintf(data, MAX_MESSAGE_SIZE, "%s - INFO: %s\n", timeString,  message);
        
        // if the option to print datas is enable, print data
        if (PRINT_DATA) {
            fprintf(stdout, "%s", data);
        }

        saveData(data);
    }
}

void logWarning(char *message) {
    // check if the level select is lower than the level of the function
    if (LEVEL <= WARNING) {
        // if the level is lower create the variables to use
        char data[MAX_MESSAGE_SIZE], timeString[30];
        // extract current time
        time_t timestamp = time(NULL);
        struct tm *ptime = localtime(&timestamp);
        
        // format current time
        strftime(timeString, 30, "%d/%m/%Y %H:%M:%S", ptime);
        
        // format the data to save
        snprintf(data, MAX_MESSAGE_SIZE, "%s - WARNING: %s\n", timeString,  message);
        
        // if the option to print datas is enable, print data
        if (PRINT_DATA) {
            fprintf(stdout, "%s", data);
        }

        saveData(data);
    }
}


void logError(char *message) {
    // check if the level select is lower than the level of the function
    if (LEVEL <= ERROR) {
        // if the level is lower create the variables to use
        char data[MAX_MESSAGE_SIZE], timeString[30];
        // extract current time
        time_t timestamp = time(NULL);
        struct tm *ptime = localtime(&timestamp);
        
        // format current time
        strftime(timeString, 30, "%d/%m/%Y %H:%M:%S", ptime);
        
        // format the data to save
        snprintf(data, MAX_MESSAGE_SIZE, "%s - ERROR: %s\n", timeString,  message);
        
        // if the option to print datas is enable, print data
        if (PRINT_DATA) {
            fprintf(stderr, "%s", data);
        }

        saveData(data);
    }
}


void logCritical(char *message) {
    // check if the level select is lower than the level of the function
    if (LEVEL <= CRITICAL) {
        // if the level is lower create the variables to use
        char data[MAX_MESSAGE_SIZE], timeString[30];
        // extract current time
        time_t timestamp = time(NULL);
        struct tm *ptime = localtime(&timestamp);
        
        // format current time
        strftime(timeString, 30, "%d/%m/%Y %H:%M:%S", ptime);
        
        // format the data to save
        snprintf(data, MAX_MESSAGE_SIZE, "%s - CRITICAL: %s\n", timeString,  message);
        
        // if the option to print datas is enable, print data
        if (PRINT_DATA) {
            fprintf(stderr, "%s", data);
        }

        saveData(data);
    }
}
