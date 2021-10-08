#ifndef __FIELD_OF_PLAY_H
#define __FIELD_OF_PLAY_H

#include <stdio.h>
#include <stdlib.h>

struct GameField{
    char* field;
};
typedef struct GameField GameField;

void InitializeField();

#endif