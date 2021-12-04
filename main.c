#include "headers/spaceship.h"
#include "headers/monsters.h"
#include "headers/fieldOfPlay.h"
#include "headers/backend.h"
#include "headers/frontend.h"
#include <menu.h>


int main (int argc, char **argv)
{ 
    /* Start ncurses */
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	nodelay(stdscr, TRUE);  /* Arrête les ncurses en attente de la saisie d'entrée du joueur */

	/* fonction main  */
    mainMenu();
}




/* Fonction extraite de la page ncurses */
void printInMiddle(WINDOW *win, int start_y, int start_x, int width, char *string) {
  int length, x, y;
  float temp;

  
  if(win == NULL)
    win = stdscr;
  getyx(win, y, x);
  if(start_x != 0)
    x = start_x;
  if(start_y != 0)
    y = start_y;
  if(width == 0)
    width = 80;

  length = strlen(string);
  temp = (width - length)/ 2;
  x = start_x + (int)temp;
  mvwprintw(win, y, x, "%s", string);
  refresh();
}

