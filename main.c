#include "headers/fieldOfPlay.h"
#include "headers/pre_compiler.h"
#include "headers/monsters.h"

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
    curs_set(0);
    
    GameField* game = InitializeField(w.ws_col, w.ws_row);
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    int start_x = (w.ws_col/2) - ship.width;
    int start_y = (w.ws_row - w.ws_row/5);

    Monster* monster = CreateMonsterSet(w.ws_row/8, w.ws_col/4);

    char ch;
    int y;
    int count_monsters = 0;
    int count_laser = 0;
    int player_shoot = 0;
    
    while(1) {
        for(int i = 0; i < game->height; i++){
            printw("%s", game->field[i]);
        }
        for(int i = 0; i < ship.height; i++) {
            mvprintw(start_y+i, start_x, ship.model[i]);
        }
        DisplayMonsters(monster, count_monsters++);
        
        switch (ch = key_pressed()) {
            case 'd':
                for(int i = 0; i < ship.height; i++) {
                    mvprintw(start_y+i, start_x, ship.model[i]);
                }
                start_x += 3;
                break;
            case 'q':
                for(int i = 0; i < ship.height; i++) {
                    mvprintw(start_y+i, start_x, ship.model[i]);
                }
                start_x -= 3;
                break;
            case ' ':
                y = 1;
                
                break;
        }
        count_laser++;
        if(count_laser%LASER_BUFFER == 0){
            mvprintw(start_y-y, start_x + ship.width/2, "|");
            refresh();
            y++;
        }
        
        usleep(50000);

        refresh();
        clear();
    }
    getch();
    endwin();
    
    return 0;
}