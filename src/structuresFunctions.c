/**
 * File containing all the libraries needed to run the program.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
 * @since February, 01 2023
*/
#include "../include/structuresFunctions.h"


int getTeamScore(Team *team) {
    return team->score;
}

void setTeamScore(Team *team, int score) {
    team->score = score;
}

void incrementTeamScore(Team *team) {
    team->score++;
}

void decrementTeamScore(Team *team) {
    if (team->score > 0) {
        team->score--;
    }
}

int getTeamRank(Team *team) {
    return team->rank;
}

void setTeamRank(Team *team, int rank) {
    team->rank = rank;
}

void incrementTeamRank(Team *team) {
    team->rank++;
}

void decrementTeamRank(Team *team) {
    team->rank--;
}
