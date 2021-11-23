#ifndef __SPACESHIP_H
#define __SPACESHIP_H

#include "pre_compiler.h"
#include "monsters.h"

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
    int lazr_x, lazr_y;

    int player_shoot;
};
typedef struct Spaceship Spaceship;

/**
 * @brief Structure representing a Laser
 * 
 */
struct Laser {
    int y;
    int x;
};
typedef struct Laser Laser;

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

/**
 * @brief Takes care of the spaceship's laser hitbox
 * 
 * @param monster Monsters to hit
 * @param ship The spaceship
 * @return Spaceship with new values. This return is used so we 
 * don't have to use a pointer on "ship"
 */
Spaceship laserHitboxChecker(Monster* monster, Spaceship ship);

#endif