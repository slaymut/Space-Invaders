#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include "pre_compiler.h"

#define LASER_BUFFER 1

/**
 * @brief Structure representing the player's spaceship
 * 
 */
struct Spaceship{
    char** model;
    short lives;
    int width, height;
    int pos_x, pos_y;
    int waves_killed;
    int laser_x, laser_y;
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
void DisplayShip(Spaceship ship, int start_y, int start_x);

/**
 * @brief If the Spaceship is hit by enemy laser !
 * 
 * @param laser_y Laser position on Y axis
 * @param laser_x Laser position on X axis
 * @param ship Player's spaceship
 * @return int 1 if true, 0 if false
 */
int isShipGetHit(int laser_y, int laser_x, Spaceship ship);

#endif