#ifndef __FIELD_OF_PLAY_H
#define __FIELD_OF_PLAY_H

#include <stdio.h>
#include <stdlib.h>
#include "spaceship.h"

struct GameField{
    char** field;
};
typedef struct GameField GameField;

void InitializeField(int field_width, int field_length);
Spaceship SetupSpaceship(char* filePath);

#endif