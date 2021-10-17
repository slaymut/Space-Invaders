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
    char** model;
    short lives;
    int width, height;

};
typedef struct Spaceship Spaceship;

/**
 * @brief Initilize Spaceship, find spaceship dimensions and allocate enough memory
 * 
 * @param filepath 
 * @return The initialized spaceship
 */
Spaceship InitSpaceship(char* filepath);

/**
 * @brief Create SpaceShip structure
 * 
 * @param filePath Path to .txt file
 * @return The setup spaceship
 */
Spaceship SetupSpaceship(char* filePath);

#endif