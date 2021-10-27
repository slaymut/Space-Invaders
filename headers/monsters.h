#ifndef __MONSTERS_H
#define __MONSTERS_H

#include "pre_compiler.h"

#define NUMBER_OF_MONSTERS 15

/**
 * @brief Structure of a Monster/Alien
 * 
 */
struct Monster {
    int lives;
    char** model;
    int pos_x, pos_y;
    int height, width;

    struct Monster *next;
};
typedef struct Monster Monster;

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
void InsertMonster(Monster* monster, int start_y, int start_x);

/**
 * @brief Create a Set of monsters with a given number
 * 
 * @param nbr_of_monsters Given number of monsters to create
 * @return Monster* The set of monsters
 */
Monster* CreateMonsterSet(int nbr_of_monsters);

/**
 * @brief Display every monster models in the linked list
 * starting from root
 * 
 * @param root Root monster of the linked list
 */
void DisplayMonsters(Monster* root);

#endif