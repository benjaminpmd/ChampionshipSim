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
typedef struct game {
    Team firstTeam;
    int firstTeamScore;
    Team secondTeam;
    int secondTeamScore;
} *Game;

typedef struct team_list {
    Team team;
    struct team_list* previous;
    struct team_list* next;
} *TeamList;

#endif