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
    /* init values */
    int length = getLength(list);
    int i = 0;
    Team team = NULL;

    /* iterate while the value is not the right */
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
    /* init values */
    TeamItem tmp = list;

    /* if the list is already empty, return NULL */
    if(isEmpty(list)) {
        return NULL;
    }

    /* if the first element is the one to remove */
    if (list == element) {
        tmp = list;
        list = getNext(list);
        free(getTeam(tmp));
        free(tmp);
        return list;
    }

    /* else check items to remove the right one */
    TeamItem iterator = list;

    /* iterate while the element is not the one researched */
    while (!isEmpty(iterator) && (iterator != element)) {
        tmp = iterator;
        iterator = getNext(iterator);
    }

    /* if the element has been found, remove it*/
    if (!isEmpty(iterator)) {
        
        setItemNext(tmp, getNext(iterator));

        free(getTeam(iterator));
        free(iterator);
    }

    return list;
}

void printTeamItem(TeamItem list) {
    while (!isEmpty(list)) {
        printf("{ Name: %s, Score: %d }\n", getName(getTeam(list)), getScore(getTeam(list)));
        list = getNext(list);
    }
}