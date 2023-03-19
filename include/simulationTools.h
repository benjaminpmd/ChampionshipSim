/**
 * File containing all the functions to simulate a championship.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#ifndef __SIMULATION_TOOLS__
#define __SIMULATION_TOOLS__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>

#include "structures.h"

/**
 * launch the simulation from a file path.
 * 
 * @param buffer the buffer to get the list from.
 * @param matchDuration the duration of each match.
 * @return an array of list
*/
TeamItem extractData(char* buffer, int* matchDuration);

/**
 * Update the buffer to write in the file at the end of the simulation.
 * 
 * @param buffer the buffer to store all the results.
 * @param result the result of the match to add.
*/
void updateOuputBuffer(char* buffer, char* result);

/**
 * Function that simulate a match.
 * 
 * @param firstTeam the first team in the match.
 * @param secondTeam the second team in the match.
 * @param manSemid the ID of the semaphore of manual input.
 * @param msqid the key of the message queue to use to send results.
 * @param matchDuration the duration of a match.
*/
void simulateMatch(Team firstTeam, Team secondTeam, int manSemid, int msqid, int matchDuration);

/**
 * launch the simulation from a file path.
 * 
 * @param inputPath the path of the file to get the list from.
 * @param outputPath the path of the file to export the results.
 * @param manualScoring the boolean wether the score should be manual or not.
*/
int runSimulation(char* inputPath, char* outputPath, bool manualScoring);

#endif