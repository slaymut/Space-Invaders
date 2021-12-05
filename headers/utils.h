#ifndef __UTILS_H
#define __UTILS_H

#include "pre_compiler.h"
#include "monsters.h"

/**
 * @brief Non-blocking way of getting user input
 * 
 * @return returns the character corresponding to the user keyboard input
 */
char key_pressed();

/**
 * @brief Opens and displays a screen
 * 
 * @param filename File name
 * @param start_y Starting Y position
 * @param start_x Starting X position
 */
void open_screens_files(char* filename, int start_y, int start_x);

/**
 * @brief Displays the first screen when starting the game
 * 
 */
void StartScreen();

/**
 * @brief Displays the winning screen
 * 
 */
void WinScreen();

/**
 * @brief Displays the game over screen
 * 
 */
void GameOverScreen();

#endif