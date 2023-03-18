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

char* getName(Team team) {
    return team->name;
}

int getScore(Team team) {
    return team->score;
}

void setName(Team team, char* name) {
    team->name = name;
}

void setScore(Team team, int score) {
    team->score = score;
}

void incrementScore(Team team) {
    team->score++;
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
    setName(newTeam, name);
    setScore(newTeam, 0);

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

TeamItem removeTeamItem(TeamItem list, TeamItem element) {
    TeamItem iterator = list;
    TeamItem tmp = list;

    if(isEmpty(list)) {
        return NULL;
    }

    if (iterator == element) {
        tmp = list;
        list = list->next;
        return list;
    }

    while (!isEmpty(iterator) && iterator != element) {
        tmp = iterator;
        iterator = getNext(iterator);
    }

    if (isEmpty(iterator)) {
        setItemNext(tmp, initTeamItem());
        return list;
    }

    if (iterator == element) {
        setItemNext(tmp, getNext(iterator));
    }
    return list;
}

void printTeamItem(TeamItem list) {
    while (!isEmpty(list)) {
        printf("{ Name: %s, Score: %d }\n", getName(getTeam(list)), getScore(getTeam(list)));
        list = getNext(list);
    }
}