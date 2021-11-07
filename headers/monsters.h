#ifndef __MONSTERS_H
#define __MONSTERS_H

#include "pre_compiler.h"

#define NUMBER_OF_MONSTERS 21
#define NUMBER_OF_MROWS 3

/**
 * @brief Structure of a Monster/Alien
 */
struct Monster {
    int lives;
    char** model;
    int pos_x, pos_y;
    int height, width;
    int print_cpt;

    int list_position;

    struct Monster *next;
};
typedef struct Monster Monster;

/**
 * @brief Direction to which the monsters move
 */
enum Direction {
    RIGHT,
    DOWN,
    LEFT
};
typedef enum Direction Direction;

/**
 * @brief Allocate enough memory, get the Monster model, initialize
 * basic datafields
 * 
 * @return Monster* Initialized monster
 */
Monster* InitMonster();

/**
 * @brief Insert a monster inside the linked link "monster".
 * Inserted at the next available place.
 * 
 * @param monster root monster
 * @param start_y Y starting coordinate
 * @param start_x X starting coordinate
 */
void InsertMonster(Monster* monster, int start_y, int start_x, int index);

/**
 * @brief Create a Set of monsters with a given number
 * 
 * @param start_y Starting point on the Y axis
 * @param start_x Starting point on the X axis
 * @param index Position in the linked list
 * @return Monster* The set of monsters
 */
Monster* CreateMonsterSet(int start_y, int start_x, int index);

int MaxX(Monster* monster, int colmax);
int MinX(Monster* monster, int colmin);

/**
 * @brief Display every monster models in the linked list. Takes care
 * of moving them aswell
 * 
 * @param root Root monster of the linked list
 * @param buffer Buffer for moving the monsters
 * @param direction Direction to move the monsters
 */
void DisplayMonsters(Monster* root, int buffer, Direction direction);

/**
 * @brief Detects if a monster is getting hit
 * 
 * @param root Linked list of monsters
 * @param laser_y Y position of the laser
 * @param laser_x X position of the laser
 * @return int The monster's position in the linked list
 */
int isGettingHit(Monster* root, int laser_y, int laser_x);

/**
 * @brief Deletes a monster from the linked list
 * 
 * @param root Linked list of monsters
 * @param pos Position of the monster to delete
 */
void DeleteMonster(Monster* root, int pos);

#endif