/**
 * File containing all the functions useful to manipulate structures.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#ifndef __STRUCTURES_FUNCTIONS__
#define __STRUCTURES_FUNCTIONS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

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
char* getName(Team team);

/**
 * Function to get the score of a team.
 * 
 * @param team the team to get data from.
 * @return the score of the team.
*/
int getScore(Team team);

/**
 * Function to set the name of a team.
 * 
 * @param team the team to update.
 * @param name the name of the team.
*/
void setName(Team team, char* name);

/**
 * Function to set the score of a team.
 * 
 * @param team the team to update.
 * @param score the score of the team.
*/
void setScore(Team team, int score);

/**
 * Function to increment the score of a team.
 * 
 * @param team the team to update.
*/
void incrementScore(Team team);

/**
 * Function that returns an initialzed team list item.
 * 
 * @return an initialzed team list item.
*/
TeamItem initTeamItem();

/**
 * Function that returns an allocated team item.
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
 * Function that creates a new Team with a string name.
 * 
 * @param list an item of the list.
 * @param name the name of the team to add.
 * @return a @link TeamItem.
*/
TeamItem addTeam(TeamItem list, char* name);

/**
 * Function that checks if a team list element is empty or not.
 * 
 * @param list a @link TeamItem.
 * @return a boolean wether the element is empty or not.
*/
bool isEmpty(TeamItem list);

/**
 * Function that checks if a team list next element is empty or not.
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
 * Function that returns the team at the given index.
 * 
 * @param list the list to get the team from.
 * @param index the index of the team
 * @return the team at the given index or NULL if the team is not found or if the index does not exist.
*/
Team getTeamAt(TeamItem list, int index);

/**
 * Removes an element in a list.
 * 
 * @param list the list to remove an element.
 * @param element the element to remove from the list.
 * @return the updated list.
*/
TeamItem removeTeamItem(TeamItem list, TeamItem element);

/**
 * Prints the content of a list.
 * 
 * @param list the list to print the content from.
*/
void printTeamItem(TeamItem list);

#endif