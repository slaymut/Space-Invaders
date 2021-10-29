#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include "pre_compiler.h"

#define LASER_BUFFER 1000000

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

/**
 * @brief Displays the spaceship's model
 * 
 * @param ship The spaceship to display
 */
void DisplayShip(Spaceship ship);

void AfficherLaser(int start_y, int start_x);

#endif