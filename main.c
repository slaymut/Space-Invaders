#include "headers/frontend.h"


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
