#include "pre_compiler.h"

#include "monsters.h"
#include "fieldOfPlay.h"
#include "spaceship.h"


/* Menu functions */
void mainMenu(void);
int playGame(Difficulty difficulty);

int MainMenu();

void print_menu(WINDOW *menu_win, int highlight);