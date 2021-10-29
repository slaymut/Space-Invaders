#include "headers/fieldOfPlay.h"
#include "headers/pre_compiler.h"
#include "headers/monsters.h"

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
    Laser laser = {0, 0, '|'};
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
                if(!player_shoot){
                    y = 1;
                    laser.laser_x = start_x;
                    laser.laser_y = start_y;
                    player_shoot = 1;
                }
                break;
        }
        count_laser++;
        if(player_shoot == 1 && count_laser%LASER_BUFFER == 0){
            mvprintw(laser.laser_y-y, laser.laser_x + ship.width/2, "%c", laser.beam);
            y++;
        }

        if((start_y - y) == 0) {
            player_shoot = 0;
        }
        
        usleep(40000);

        refresh();
        clear();
    }
    getch();
    endwin();
    
    return 0;
}