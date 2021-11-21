#ifndef __MONSTERS_H
#define __MONSTERS_H

#include "pre_compiler.h"

#define BASE_PRINT_CPT 10
#define NUMBER_OF_MONSTERS_PER_ROW 7
#define NUMBER_OF_MROWS 3
#define MONSTER_LASER_BUFFER 1

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
 * @brief Position Holder for monsters that can shoot
 * 
 */
struct PositionHolder {
    int positions_X[NUMBER_OF_MONSTERS_PER_ROW];
    int positions_Y[NUMBER_OF_MONSTERS_PER_ROW];
    int shooting[NUMBER_OF_MONSTERS_PER_ROW];
};
typedef struct PositionHolder PositionHolder;

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
Monster* InitMonster(int lives, int which_monster);

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

/**
 * @brief Get min X position in the linked list
 * 
 * @param monster List of monsters
 * @param colmax Max X position
 * @return int returns "colmax"
 */
int MaxX(Monster* monster, int colmax);

/**
 * @brief Get min X position in the linked list
 * 
 * @param monster List of monsters
 * @param colmin Min X position
 * @return int returns "colmin"
 */
int MinX(Monster* monster, int colmin);

/**
 * @brief Get max Y position in the linked list
 * 
 * @param monster List of monsters
 * @param rowmax Max Y position
 * @return int the Row position (Y coordinate on the screen) according to the furthest down monster
 */
int MaxY(Monster* monster, int rowmax);

/**
 * @brief Moves monster in a direction
 * 
 * @param monster Linked list of monsters
 * @param buffer Movement buffer to know when to actually move it
 * @param direction The direction where to move the monsters
 */
void MoveMonster(Monster* monster, int buffer, Direction direction);

/**
 * @brief Display every monster models in the linked list. Takes care
 * of moving them aswell
 * 
 * @param root Root monster of the linked list
 */
void DisplayMonsters(Monster* root);

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
 * @brief Selects positions of every monster that can shoot
 * 
 * @param monsters Linked list of monsters
 * @return PositionHolder Positions
 */
PositionHolder ShootingMonsters(Monster* monsters);

#endif