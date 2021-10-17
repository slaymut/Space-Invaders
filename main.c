#include "headers/fieldOfPlay.h"

#include <sys/ioctl.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);

    GameField game = InitializeField(w.ws_col, w.ws_row);
    for(int i = 0; i < game.height; i++){
        printf("%s\n", game.field[i]);
    }
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    DisplayShip(ship);

    return 0;
}