/**
 * File containing structures of the program.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 1.0.0
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
    int score;
} *Team;

/**
 * Chained list of teams.
*/
typedef struct team_item {
    Team team;
    struct team_item* next;
} *TeamItem;

#endif