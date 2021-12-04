#include "pre_compiler.h"

#include "monsters.h"
#include "fieldOfPlay.h"
#include "spaceship.h"

extern int EXIT;

/* For displays */
enum Command getCommand(int d);

/* Game functions */
void writeScoreToFile(int score);

/* Menu functions */
void mainMenu(void);
int playGame(void);

void howToPlay(void);

void exitGame(void);


/* Fonction extraite de la page ncurses */
void printInMiddle(WINDOW *win, int start_y, int start_x, int width, char *string);
