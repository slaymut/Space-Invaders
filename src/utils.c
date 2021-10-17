#include "../headers/utils.h"

void DisplayShip(Spaceship ship)
{
    for(int i = 0; i < ship.height; i++){
        printf("%s\n", ship.model[i], ship.lives);
    }
}