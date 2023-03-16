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
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Function to init a team.
 *
 * @return a team.
*/
Team initTeam();

/**
 * Function to allocate memory to a team.
 *
 * @return a team.
*/
Team allocTeam();

/**
 * Function to get the name of a team.
 * 
 * @param team the team to get data from.
 * @return the name of the team as an char pointer.
*/
char* getTeamName(Team team);

/**
 * Function to get the status of a team.
 * 
 * @param team the team to get data from.
 * @return the status of the team as a boolean.
*/
bool hasLost(Team team);

/**
 * Function to set the name of a team.
 * 
 * @param team the team to update.
 * @param name the name of the team.
*/
void setTeamName(Team team, char* name);

/**
 * Function to set the status of a team.
 * 
 * @param team the team to update.
 * @param hasLost wether the team has lost or not.
*/
void setTeamLoss(Team team, bool hasLost);

/**
 * Function that return an initialzed team list item.
 * 
 * @return an initialzed team list item.
*/
TeamItem initTeamItem();

/**
 * Function that return an allocated team item.
 * 
 * @return allocated memory for the list.
*/
TeamItem allocTeamItem();

/**
 * Function to get team from the list.
 * 
 * @param list an item of the list.
 * @return a team.
*/
Team getTeam(TeamItem list);

/**
 * Function to get the next element from the list.
 * 
 * @param list an item of the list.
 * @return the next element.
*/
TeamItem getNext(TeamItem list);

/**
 * Function to set team to the list specified list element.
 * 
 * @param list an item of the list.
 * @param team a team to set to the current element of the list.
*/
void setItemTeam(TeamItem list, Team team);

/**
 * Function to set the next element to the list specified list element.
 * 
 * @param list an item of the list.
 * @param nextItem the next list element to set to the current element of the list.
*/
void setItemNext(TeamItem list, TeamItem nextItem);

/**
 * Function that create a new Team with a string name.
 * 
 * @param list an item of the list.
 * @param name the name of the team to add.
 * @return a @link TeamItem.
*/
TeamItem addTeam(TeamItem list, char* name);

/**
 * Function that check if a team list element is empty or not.
 * 
 * @param list a @link TeamItem.
 * @return a boolean wether the element is empty or not.
*/
bool isEmpty(TeamItem list);

/**
 * Function that check if a team list next element is empty or not.
 * 
 * @param list a @link TeamItem.
 * @return a boolean wether the next element is empty or not.
*/
bool hasNext(TeamItem list);

/**
 * Function that returns the length of a list.
 * 
 * @param list the list to get the length from.
 * @return the length of the list.
*/
int getLength(TeamItem list);

/**
 * Function that returns the number of active teams in a list.
 * 
 * @param list the list to get the number from.
 * @return the number of active teams in the list.
*/
int getActiveTeams(TeamItem list);

/**
 * Function that returns the team at the given index.
 * 
 * @param list the list to get the team from.
 * @param index the index of the team
 * @return the team at the given index or NULL if the team is not found or if the index does not exist.
*/
Team getTeamAt(TeamItem list, int index);

Team getTeamFromName(TeamItem list, char* name);

TeamItem removeTeamItem(TeamItem list, TeamItem element);

void printTeamItem(TeamItem list);



#endif