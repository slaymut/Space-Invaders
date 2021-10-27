#ifndef __FIELD_OF_PLAY_H
#define __FIELD_OF_PLAY_H

#include "spaceship.h"
#include "utils.h"

/**
 * @brief The game field
 * 
 */
struct GameField{
    char** field;
    int height, width;
};
typedef struct GameField GameField;

/**
 * @brief Create field structure
 * 
 * @param field_width Terminal width
 * @param field_length Terminal height
 */
GameField* InitializeField(int field_width, int field_length);

void InsertEntity(GameField* field, Spaceship space, int x, int y);


#endif