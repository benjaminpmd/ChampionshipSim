/**
 * File containing all the logging system.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since January 25, 2023
*/
#ifndef __LOGGER__
#define __LOGGER__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/**
 * The path of the file to save data in.
 */
#define LOG_FILE_PATH "logs/debug.log"

/**
 * The max size of a log message.
 */
#define MAX_MESSAGE_SIZE 200

/**
 * The level to select, only messages with an equal or higher level will be saved and/or printed.
 */
#define LEVEL DEBUG

/**
 * An option to print data on screen.
 */
#define PRINT_DATA true

/**
 * An option to save data in a file.
 */
#define SAVE_DATA true

typedef enum {DEBUG, INFO, WARNING, ERROR, CRITICAL} levels;

/**
 * This function saves data in a log file.
 * 
 * @param data the data to save.
*/
void saveData(char* data);

/**
 * This function save a debug message into the log file. The message will only be saved if the selected level is equal or lower than debug.
 * 
 * @param message the message to save/print.
 */
void logDebug(char *message);

/**
 * This function save an information message into the log file. The message will only be saved if the selected level is equal or lower than information.
 * 
 * @param message the message to save/print.
 */
void logInfo(char *message);

/**
 * This function save a warning message into the log file. The message will only be saved if the selected level is equal or lower than warning.
 * 
 * @param message the message to save/print.
 */
void logWarning(char *message);

/**
 * This function save an error message into the log file. The message will only be saved if the selected level is equal or lower than error.
 * 
 * @param message the message to save/print.
 */
void logError(char *message);

/**
 * This function save an critical message into the log file. The message will only be saved if the selected level is equal or lower than critical.
 * 
 * @param message the message to save/print.
 */
void logCritical(char *message);

#endif