#ifndef __FIELD_OF_PLAY_H
#define __FIELD_OF_PLAY_H

#include "pre_compiler.h"

struct GameConfig {
    int loop_times;
    int BOSS_APPEARANCE;
    int boss_fight;
    int score;
    char* lives[2];
};
typedef struct GameConfig GameConfig;

#endif