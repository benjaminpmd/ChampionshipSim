/**
 * File containing all the libraries needed to run the program.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#include "../include/structuresFunctions.h"

/***** Team section *****/

Team initTeam() {
    return NULL;
}

Team allocTeam() {
    return malloc(sizeof(struct team));
}

char* getTeamName(Team team) {
    return team->name;
}

bool hasLost(Team team) {
    return team->hasLost;
}

void setTeamName(Team team, char* name) {
    team->name = name;
}

void setTeamLoss(Team team, bool hasLost) {
    team->hasLost = hasLost;
}

/***** TeamItem list section *****/

TeamItem initTeamItem() {
    return NULL;
}

TeamItem allocTeamItem() {
    return malloc(sizeof(struct team_item));
}

Team getTeam(TeamItem list) {
    return list->team;
}

TeamItem getNext(TeamItem list) {
    return list->next;
}

void setItemTeam(TeamItem list, Team team) {
    list->team = team;
}

void setItemNext(TeamItem list, TeamItem nextItem) {
    list->next = nextItem;
}

TeamItem addTeam(TeamItem list, char* name) {
    
    /* creates the new team */
    Team newTeam = allocTeam();
    TeamItem newTeamItem = allocTeamItem();

    /* setup data of new team */
    setTeamName(newTeam, name);
    setTeamLoss(newTeam, false);

    setItemTeam(newTeamItem, newTeam);
    setItemNext(newTeamItem, initTeamItem());


    if (isEmpty(list)) {
        list = newTeamItem;
    }
    else {
        /* iterate over the team to find the last element */
        TeamItem iterator = list;

        /* find the last element of the list */
        while(hasNext(iterator)) {
            iterator = getNext(iterator);
        }
        /* add the new element to the last element of the current list */
        setItemNext(iterator, newTeamItem);
    }
    return list;
}

bool isEmpty(TeamItem list) {
    return (list == NULL);
}

bool hasNext(TeamItem list) {
    if (isEmpty(list->next)) {
        return false;
    }
    return true;
}

int getLength(TeamItem list) {
    int counter = 0;
    
    while(!isEmpty(list)) {
        counter++;
        list = getNext(list);
    }
    return counter;
}

int getActiveTeams(TeamItem list) {
    int counter = 0;
    
    while(!isEmpty(list)) {
        if (!hasLost(getTeam(list))) {
            counter++;
        }
        list = getNext(list);
    }
    return counter;
}

Team getTeamAt(TeamItem list, int index) {
    int length = getLength(list);
    int i = 0;
    Team team = NULL;
    while ((i <= index) && !isEmpty(list)) {
        if (i == index) {
            team = list->team;
        }
        list = getNext(list);
        i++;
    }
    return team;
}

Team getTeamFromName(TeamItem list, char* name) {
    while (hasNext(list)) {
        if (strcmp(getTeam(list)->name, name) == 0) {
            return getTeam(list);
        }
        list = getNext(list);
    }
    return NULL;
}



void printTeamItem(TeamItem list) {
    while (hasNext(list)) {
        printf("{ Name: %s, hasLost: %d }\n", list->team->name, list->team->hasLost);
        list = getNext(list);
    }
}