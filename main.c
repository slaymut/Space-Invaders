#include "headers/fieldOfPlay.h"
#include "headers/pre_compiler.h"
#include "headers/monsters.h"

int main (int argc, char **argv)
{   
    initscr(); raw(); noecho(); cbreak(); curs_set(0);
    
    //GameField* game = InitializeField(COLS, LINES);
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    Laser laser = {0, 0, '|'};
    int start_x = (COLS/2) - ship.width;
    int start_y = (LINES - LINES/5);

    Monster* monster = CreateMonsterSet(LINES/8, COLS/4, 1);

    char ch;
    int y;
    int iter_counter = 0;
    int player_shoot = 0;
    
    while(1) {
        // for(int i = 0; i < game->height; i++){
        //     printw("%s", game->field[i]);
        // }
        for(int i = 0; i < ship.height; i++) {
            mvprintw(start_y+i, start_x, ship.model[i]);
        }
        DisplayMonsters(monster, iter_counter++);
        
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
        if((start_y - y) == 0)
            player_shoot = 0;

        int pos = isGettingHit(monster, laser.laser_y, laser.laser_x);
        if(pos != 0){
            DeleteMonster(monster, pos);
            player_shoot = 0;
        }

        if(player_shoot == 1 && iter_counter%LASER_BUFFER == 0){
            laser.laser_y -= 1;
            mvprintw(laser.laser_y, laser.laser_x + ship.width/2, "%c", laser.beam);
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