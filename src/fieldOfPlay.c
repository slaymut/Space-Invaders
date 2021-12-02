#include "../headers/fieldOfPlay.h"

GameConfig InitConfig() {
    GameConfig config = {0, 0, 0, 0};
    config.lives[0] = "🧡";
    config.lives[1] = "💛";
    config.lives[2] = "💚";

    return config;
}