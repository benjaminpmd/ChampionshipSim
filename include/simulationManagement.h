/**
 * File containing all the functions to simulate a championship.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#ifndef __SIMULATION_MANAGEMENT__
#define __SIMULATION_MANAGEMENT__

#include "./structures.h"

/**
 * launch the simulation from a file path.
 * 
 * @param buffer the buffer to get the teams from.
 * @return an array of teams
*/
Team* extractTeams(char* buffer);

/**
 * launch the simulation from a file path.
 * 
 * @param inputPath the path of the file to get the teams from.
 * @param outputPath the path of the file to export the results.
*/
void simulate(char* inputPath, char* outputPath);

#endif