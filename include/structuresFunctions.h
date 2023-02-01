/**
 * File containing all the functions useful to manipulate structures.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#ifndef __STRUCTURES_FUNCTIONS__
#define __STRUCTURES_FUNCTIONS__

#include "structures.h"

/**
 * Function to get the score of a team.
 * 
 * @param team the team to get the score from.
 * @return the score of the team as an int.
*/
int getTeamScore(Team *team);

/**
 * Function to set the score of a team.
 * 
 * @param team the team to update.
 * @param score the score to set.
*/
void setTeamScore(Team *team, int score);

/**
 * Function to increment the score of a team.
 * 
 * @param team the team to update.
*/
void incrementTeamScore(Team *team);

/**
 * Function to decrement the score of a team.
 * 
 * @param team the team to update.
*/
void decrementTeamScore(Team *team);

/**
 * Function to get the rank of a team.
 * 
 * @param team the team to update.
 * @return the rank of the team as an int.
*/
int getTeamRank(Team *team);

/**
 * Function to set the rank of a team.
 * 
 * @param team the team to update.
 * @param rank the score to set.
*/
void setTeamRank(Team *team, int rank);

/**
 * Function to increment the rank of a team.
 * 
 * @param team the team to update.
*/
void incrementTeamRank(Team *team);

/**
 * Function to decrement the rank of a team.
 * 
 * @param team the team to update.
*/
void decrementTeamRank(Team *team);

#endif