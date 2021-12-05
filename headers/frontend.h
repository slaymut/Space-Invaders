#include "pre_compiler.h"

#include "monsters.h"
#include "fieldOfPlay.h"
#include "spaceship.h"
#include "utils.h"

/**
 * @brief Launches the game
 * 
 * @param difficulty  
 */
int playGame(Difficulty difficulty);

/**
 * @brief Main menu to choose the difficulty
 * 
 * @return difficulty 
 */
int MainMenu();

/**
 * @brief Prints the main menu
 * 
 * @param menu_win 
 * @param highlight 
 */
void print_menu(WINDOW *menu_win, int highlight);