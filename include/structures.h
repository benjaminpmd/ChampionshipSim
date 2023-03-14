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
    bool hasLost;
} *Team;

/**
 * Chained list of teams.
*/
typedef struct team_item {
    Team team;
    struct team_item* next;
} *TeamItem;

/**
 * Structure of a game.
 * It contains two list playing against each others.
*/
typedef struct match_result {
    char firstTeam[100];
    int firstTeamScore;
    char secondTeam[100];
    int secondTeamScore;
} *MatchResult;

#endif