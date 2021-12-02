#ifndef __MONSTERS_H
#define __MONSTERS_H

#include "pre_compiler.h"

#define MONSTERS_PER_ROW 8
#define MONSTER_ROWS 3
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
    int score_gain;
    int type_of_monster;

    struct Monster *next;
};
typedef struct Monster Monster;

/**
 * @brief Position Holder for monsters that can shoot
 * 
 */
struct PositionHolder {
    int positions_X[MONSTERS_PER_ROW];
    int positions_Y[MONSTERS_PER_ROW];
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

enum Difficulty {
    FACILE,
    DIFFICILE,
    PROGRESSIVE
};
typedef enum Difficulty Difficulty;

/**
 * @brief Allocate enough memory, get the Monster model, initialize
 * basic datafields
 * 
 * @return Monster* Initialized monster
 */
Monster* InitMonster(int lives, int which_monster, int waves_killed);

/**
 * @brief Insert a monster inside the linked link "monster".
 * Inserted at the next available place.
 * 
 * @param monster root monster
 * @param start_y Y starting coordinate
 * @param start_x X starting coordinate
 */
void InsertMonster(Monster* monster, int start_y, int start_x, int index, int lives, int waves_killed);

/**
 * @brief Create a Set of monsters with a given number
 * 
 * @param start_y Starting point on the Y axis
 * @param start_x Starting point on the X axis
 * @param index Position in the linked list
 * @return The set of monsters
 */
Monster* CreateMonsterSet(int start_y, int start_x, int index, Difficulty diff, int waves_killed);

/**
 * @brief Get min X position in the linked list
 * 
 * @param monster List of monsters
 * @return returns "colmax"
 */
int MaxX(Monster* monster);

/**
 * @brief Get min X position in the linked list
 * 
 * @param monster List of monsters
 * @return int returns "colmin"
 */
int MinX(Monster* monster);

/**
 * @brief Get max Y position in the linked list
 * 
 * @param monster List of monsters
 * @return int the Row position (Y coordinate on the screen) according to the furthest down monster
 */
int MaxY(Monster* monster);

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
 * @brief Checks if every monster is dead
 * 
 * @param root 
 * @return int 
 */
int isEveryMonsterDead(Monster* root, int check);

/**
 * @brief Selects positions of every monster that can shoot
 * 
 * @param monsters Linked list of monsters
 * @return PositionHolder Positions
 */
PositionHolder ShootingMonsters(Monster* monsters);

/**
 * @brief 
 * 
 * @param monster 
 */
void freeList(Monster* monster);

/**
 * @brief Create a Boss Instance
 * 
 * @param start_y 
 * @param start_x 
 * @param diff 
 * @param waves_killed 
 * @return Monster* 
 */
Monster* CreateBossInstance(int start_y, int start_x, 
                          Difficulty diff,
                          int waves_killed);

#endif