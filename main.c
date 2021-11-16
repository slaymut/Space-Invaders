#include "headers/fieldOfPlay.h"
#include "headers/pre_compiler.h"
#include "headers/monsters.h"

int main (int argc, char **argv)
{ 
    setlocale(LC_ALL, "");

    initscr(); raw(); noecho(); cbreak(); curs_set(0);
    time_t t;

    //srand(time(&t));
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    Laser laser = {0, 0, '|'};
    int start_x = (COLS/2) - ship.width/2;
    int start_y = (LINES - LINES/5);

    Monster* monster = CreateMonsterSet(LINES/8, COLS/4, 1);
    Direction direction = RIGHT;

    char ch;
    int y;
    int iter_counter = 0;
    int player_shoot = 0;
    
    while(1) {
        DisplayShip(ship, start_y, start_x);
        MoveMonster(monster, iter_counter++, direction);
        DisplayMonsters(monster);
        
        if(MaxX(monster, 0) == COLS - COLS/15){
            MoveMonster(monster, iter_counter++, DOWN);
            direction = LEFT;
        }
        if(MinX(monster, 50) == COLS/15){
            MoveMonster(monster, iter_counter++, DOWN);
            direction = RIGHT;
        }

        /*
        if(isGameOver(monster, start_y)){
            refresh();
            clear();

            mvprintw(COLS/2, LINES/2, "YOU LOSE HAHAHA !");
            break;
        }
        */
       
        switch (ch = key_pressed()) {
            case 'd':
                start_x += 3;
                break;
            case 'q':
                start_x -= 3;
                break;
            case ' ':
                if(!player_shoot){
                    y = 1;
                    laser.laser_x = start_x + ship.width/2;
                    laser.laser_y = start_y;
                    player_shoot = 1;
                }
                break;
        }
        if((start_y - y) == 0)
            player_shoot = 0;


        if(isGettingHit(monster, laser.laser_y, laser.laser_x) && player_shoot == 1){
            player_shoot = 0;
            laser.laser_x = 0;
            laser.laser_y = 0;
        }
        
        if(player_shoot == 1 && iter_counter%LASER_BUFFER == 0){
            laser.laser_y -= 1;
            mvprintw(laser.laser_y, laser.laser_x, "%c", laser.beam);
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