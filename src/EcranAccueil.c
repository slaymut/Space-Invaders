#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>

void menu(struct options *settings);

int main() {
     struct options settings;
  //Affiche l'Ecran d'acceuil 
   move(0,(COLS/2)-9);
   addstr("--SPACE INVADERS--");
   move (0,1);
   addstr("SCORE: ");
   move(0,COLS-19);
   addstr("m = menu  q = quit");
}
   
