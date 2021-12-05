#ifndef __FIELD_OF_PLAY_H
#define __FIELD_OF_PLAY_H

#include "pre_compiler.h"

/**
 * @brief Struct containing all the game configurations
 * 
 */
struct GameConfig {
    int loop_times;
    int BOSS_APPEARANCE;
    int boss_fight;
    int score;
    int shooting_monster;
    int monster_shoot;
    int iter_counter;
    int model;
    char* lives[2];
};
typedef struct GameConfig GameConfig;

GameConfig* initconfig();

#endif