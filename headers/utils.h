#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "spaceship.h"

/**
 * @brief Displays the spaceship's model
 * 
 * @param ship The spaceship to display
 */
void DisplayShip(Spaceship ship);

char key_pressed();

#endif