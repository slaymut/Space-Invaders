#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

void gameover(int win) {

   nodelay(stdscr, 0);
   
   if (win == 0) {
      clear();
      move((LINES/2)-1,(COLS/2)-5);
      addstr("YOU LOSE!");
      move((LINES/2),(COLS/2)-11);
      addstr("PRESS ANY KEY TO EXIT");
      move(0,COLS-1);
      refresh();
      getch();
   }
   
   else if (win == 1) {
      clear();
      move((LINES/2)-1,(COLS/2)-5);
      addstr("YOU WIN!");
      move((LINES/2),(COLS/2)-11);
      addstr("PRESS ANY KEY TO EXIT");
      move(0,COLS-1);
      refresh();
      getch();
   }



