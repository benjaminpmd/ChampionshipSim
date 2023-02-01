/**
 * File containing structures of the program.
 * 
 * @authors Alice MABILLE, Benjamin PAUMARD
 * @version 0.0.1
 * @since February, 01 2023
*/
#ifndef __STRUCTURES__
#define __STRUCTURES__

/**
 * Structure of a team.
 * It contains a rank and a score.
*/
typedef struct team {
    int rank;
    int score;
} Team;

/**
 * Structure of a game.
 * It contains two teams playing against each others.
*/
typedef struct game {
    Team firstTeam;
    Team secondTeam;
} Game;

#endif