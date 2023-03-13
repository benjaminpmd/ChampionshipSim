/**
 * File containing structures of the program.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 0.0.1
 * @since February, 01 2023
*/
#ifndef __STRUCTURES__
#define __STRUCTURES__

#include <stdbool.h>

/**
 * Structure of a team.
 * It contains a rank and a score.
*/
typedef struct team {
    char* name;
    int rank;
    bool active;
} *Team;

/**
 * Structure of a game.
 * It contains two teams playing against each others.
*/
typedef struct match_result {
    Team firstTeam;
    int firstTeamScore;
    Team secondTeam;
    int secondTeamScore;
} *MatchResult;

typedef struct team_item {
    Team team;
    struct team_item* previous;
    struct team_item* next;
} *TeamItem;

#endif