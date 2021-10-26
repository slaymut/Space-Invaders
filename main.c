#include "headers/fieldOfPlay.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>

// int main (int argc, char **argv)
// {
    
    
//     struct winsize w;
//     ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

//     printf ("lines %d\n", w.ws_row);
//     printf ("columns %d\n", w.ws_col);

//     GameField* game = InitializeField(w.ws_col, w.ws_row);
    
//     Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
//     int start_x = (w.ws_col/2) - ship.width;
//     int start_y = (w.ws_row - w.ws_row/5);
    
//     InsertEntity(game, ship, start_x, start_y);

//     for(int i = 0; i < game->height; i++){
//         printf("%s\n", game->field[i]);
//     }
    
//     return 0;
// }

int main (int argc, char **argv)
{   
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    initscr();
    raw();
    noecho();
    cbreak();
    
    GameField* game = InitializeField(w.ws_col, w.ws_row);
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    int start_x = (w.ws_col/2) - ship.width;
    int start_y = (w.ws_row - w.ws_row/5);

    char ch;
    //InsertEntity(game, ship, start_x, start_y);
    while(1) {    
         for(int i = 0; i < game->height; i++){
            printw("%s", game->field[i]);
        }
        for(int i = 0; i < ship.height; i++) {
            mvprintw(start_y+i, start_x, ship.model[i]);
        }
        
        switch (ch = key_pressed()) {
            case 'd':
                start_x += 3;
                break;
            case 'q':
                start_x -= 3;
                break;
        }
        
        usleep(50000);

        refresh();
        clear();
    }
    getch();
    endwin();
    
    return 0;
}