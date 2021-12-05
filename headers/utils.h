#ifndef __UTILS_H
#define __UTILS_H

#include "pre_compiler.h"
#include "monsters.h"

struct Screen {
    char **model;
    int height;
    int width;
};
typedef struct Screen Screen;

/**
 * @brief Non-blocking way of getting user input
 * 
 * @return returns the character corresponding to the user keyboard input
 */
char key_pressed();

void open_screens_files(char* filename, int start_y, int start_x);

void StartScreen();

#endif