#include "../headers/fieldOfPlay.h"

GameConfig* initconfig() {
    GameConfig* config = malloc(sizeof(GameConfig));
    config->score = 0;
    config->BOSS_APPEARANCE = 0;
    config->boss_fight = 0;
    config->loop_times = 0;
    config->monster_shoot = 0;
    config->shooting_monster = 0;
    config->iter_counter = 1;
    config->lives[0] = "🧡";
    config->lives[1] = "💛";
    config->lives[2] = "💚";

    return config;
}