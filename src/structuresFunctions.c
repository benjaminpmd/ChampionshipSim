/**
 * File containing all the libraries needed to run the program.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#include "../include/structuresFunctions.h"

int getTeamRank(Team team) {
    return team->rank;
}

void setTeamRank(Team team, int rank) {
    team->rank = rank;
}

void incrementTeamRank(Team team) {
    team->rank++;
}

void decrementTeamRank(Team team) {
    team->rank--;
}

TeamItem initTeamItem() {
    return NULL;
}

bool isEmpty(TeamItem teams) {
    if (teams == NULL) {
        return true;
    }
    return false;
}

bool hasNext(TeamItem teams) {
    if (isEmpty(teams->next)) {
        return false;
    }
    return true;
}

TeamItem getNext(TeamItem teams) {
    return teams->next;
}

TeamItem addTeam(TeamItem teams, char* name) {
    
    /* creates the new team */
    Team newTeam = (Team) malloc(sizeof(struct team));
    /* setup data of new team */
    newTeam->active = true;
    newTeam->rank = 0;
    newTeam->name = name;

    TeamItem newListItem = (TeamItem) malloc(sizeof(struct team_item));
    newListItem->team = newTeam;
    newListItem->next = initTeamItem();


    if (isEmpty(teams)) {
        newListItem->previous = initTeamItem();
        teams = newListItem;
    }
    else {
        /* iterate over the team to find the last element */
        TeamItem teamIterator = teams;

        /* find the last element of the list */
        while(hasNext(teamIterator)) {
            teamIterator = getNext(teamIterator);
        }
        /* add the previous element to the new one */
        newListItem->previous = teamIterator;
        /* add the new element to the last element of the current list */
        teamIterator->next = newListItem;
    }

    return teams;
}

int getLength(TeamItem teams) {
    int counter = 0;
    
    while(!isEmpty(teams) && hasNext(teams)) {
        counter++;
        teams = getNext(teams);
    }
    return counter;
}

Team getTeamAt(TeamItem teams, int index) {
    int length = getLength(teams);
    int i = 0;
    Team team = NULL;
    while ((i < index) && (i < length)) {
        teams = getNext(teams);
        i++;
        if (i == index) {
            team = teams->team;
        }
    }
    return team;
}