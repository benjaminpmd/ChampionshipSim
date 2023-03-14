/**
 * File containing all the functions to simulate a championship.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#ifndef __SIMULATION_TOOLS__
#define __SIMULATION_TOOLS__

#include "./structures.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>

/**
 * launch the simulation from a file path.
 * 
 * @param buffer the buffer to get the teams from.
 * @param matchDuration the duration of each match.
 * @return an array of teams
*/
TeamItem extractData(char* buffer, int* matchDuration);


void simulateMatch(Team firstTeam, Team secondTeam, bool manualScoring, int bufferSemid, int scoringSemid, int matchDuration);

/**
 * launch the simulation from a file path.
 * 
 * @param inputPath the path of the file to get the teams from.
 * @param outputPath the path of the file to export the results.
 * @param manualScoring the boolean wether the score should be manual or not.
 * @param graphical the boolean wether the gui is required or not.
*/
int runSimulation(char* inputPath, char* outputPath, bool manualScoring, bool graphical);

#endif