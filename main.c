#include "headers/game.h"

int main (int argc, char **argv)
{ 
    setlocale(LC_ALL, "");

    initscr(); raw(); noecho(); cbreak(); curs_set(0);
    
    PlayGame();
    
    getch();
    endwin();
    
    return 0;
}