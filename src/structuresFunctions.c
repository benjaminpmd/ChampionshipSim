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

TeamList initTeamList() {
    return NULL;
}

bool isEmpty(TeamList teams) {
    if (teams == NULL) {
        return true;
    }
    return false;
}

bool hasNext(TeamList teams) {
    if (isEmpty(teams->next)) {
        return false;
    }
    return true;
}

TeamList getNext(TeamList teams) {
    return teams->next;
}

TeamList addTeam(TeamList teams, char* name) {
    
    /* creates the new team */
    Team newTeam = (Team) malloc(sizeof(struct team));
    /* setup data of new team */
    newTeam->active = true;
    newTeam->rank = 0;
    newTeam->name = name;

    TeamList newListItem = (TeamList) malloc(sizeof(struct team_list));
    newListItem->team = newTeam;
    newListItem->next = initTeamList();


    if (isEmpty(teams)) {
        newListItem->previous = initTeamList();
        teams = newListItem;
    }
    else {
        /* iterate over the team to find the last element */
        TeamList teamIterator = teams;

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
