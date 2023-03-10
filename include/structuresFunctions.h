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
#include <stdlib.h>

/**
 * Function to get the rank of a team.
 * 
 * @param team the team to update.
 * @return the rank of the team as an int.
*/
int getTeamRank(Team team);

/**
 * Function to set the rank of a team.
 * 
 * @param team the team to update.
 * @param rank the score to set.
*/
void setTeamRank(Team team, int rank);

/**
 * Function to increment the rank of a team.
 * 
 * @param team the team to update.
*/
void incrementTeamRank(Team team);

/**
 * Function to decrement the rank of a team.
 * 
 * @param team the team to update.
*/
void decrementTeamRank(Team team);

/**
 * Function that return an initialzed team list item.
 * 
 * @return an initialzed team list item.
*/
TeamList initTeamList();

/**
 * Function that check if a team list element is empty or not.
 * 
 * @param teams a @see TeamList.
 * @return a boolean wether the element is empty or not.
*/
bool isEmpty(TeamList teams);

/**
 * Function that check if a team list next element is empty or not.
 * 
 * @param teams a @see TeamList.
 * @return a boolean wether the next element is empty or not.
*/
bool hasNext(TeamList teams);

/**
 * Function to get the next element of a team list element.
 * 
 * @param teams a @see TeamList.
 * @return the next element of the element passed in argument.
*/
TeamList getNext(TeamList teams);

/**
 * Function that create a new Team with a string name.
 * TODO: end documentation
*/
TeamList addTeam(TeamList teams, char* name);


MatchResult initMatchResult();

MatchResult allocMatchResult();

#endif