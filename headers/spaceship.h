#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Structure representing the player's spaceship
 * 
 */
struct Spaceship{
    char* model;
    short lives;
};
typedef struct Spaceship Spaceship;

/**
 * @brief Displays the spaceship's model
 * 
 */
void DisplayShip();

#endif