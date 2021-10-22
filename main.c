#include "headers/fieldOfPlay.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <ncurses.h>

int main (int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);

    GameField* game = InitializeField(w.ws_col, w.ws_row);
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    int start_x = (w.ws_col/2) - ship.width;
    int start_y = (w.ws_row - w.ws_row/5);
    
    //while(1){
        InsertEntity(game, ship, start_x, start_y);

        for(int i = 0; i < game->height; i++){
            printf("%s\n", game->field[i]);
        }


    //}
    
    return 0;
}