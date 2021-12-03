#include <unistd.h>
#include <ncurses.h>
#include <menu.h>

extern int EXIT;

/* For displays */
enum Command getCommand(int d);

/* Game functions */
void writeScoreToFile(int score);

/* Menu functions */
void mainMenu(void);
int playGame(void);