include <stdio.h>
#include <stdlib.h> 
#include <curses.h> 
#include <time.h>


#define MAX_BOMBS 1000
/* Space Invaders */


struct player {
	int r,c; // ligne, colonne
	char ch; // symbole
};

struct alien {
	int r,c; // ligne, colonne
	int pr,pc;
	int en_vie; // 1=En vie 0=detruit
	char direction; // 'l'=gauche 'r'=droit
	char ch; // symbole
};

struct shoot {
	int r,c; // ligne, colonne
	int active; /* 1=active 0=inactive */
	char ch; // symbole
};

struct bomb {
	int r,c; // ligne, colonne
	int active; // 1=active 0=inactive
	int loop; 
	char ch; // symbol
};

struct options { 
	int overall,alien,shots,bombs,
        bombchance; 
};
	
void menu(struct options *settings); // list for user
void gameover(int win); // win or lost?
int main() {
    // struct for each type

/* Cela permettra d'afficher le message "Victory" ou "Deafeat"*/
void gameover(int win) {

   nodelay(stdscr, 0);
   
   if (win == 0) {
      clear();
      move((LINES/2)-1,(COLS/2)-5);
      addstr("DEFEAT !");
      move((LINES/2),(COLS/2)-11);
      addstr("APPUYEZ SUR N'IMPORTE QUEL BOUTON POUR QUITTER");
      move(0,COLS-1);
      refresh();
      getch();
   }
   
   else if (win == 1) {
      clear();
      move((LINES/2)-1,(COLS/2)-5);
      addstr("VICTORY !");
      move((LINES/2),(COLS/2)-11);
      addstr("APPUYEZ SUR N'IMPORTE QUEL BOUTON POUR QUITTER");
      move(0,COLS-1);
      refresh();
      getch();
   }
}
