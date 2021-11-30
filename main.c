#include "headers/fieldOfPlay.h"
#include "headers/pre_compiler.h"
#include "headers/monsters.h"

int main (int argc, char **argv)
{ 
    setlocale(LC_ALL, "");

    initscr(); raw(); noecho(); cbreak(); curs_set(0);
    
    time_t t;
    srand(time(&t));
    Difficulty difficulty = FACILE;

    int loop_times = 0;
    int BOSS_APPEARANCE = 0;
    int boss_fight = 0;

    switch (difficulty) {
        case FACILE:
            loop_times = 2;
            BOSS_APPEARANCE = 3;
            break;
        case DIFFICILE:
            loop_times = 3;
            BOSS_APPEARANCE = 2;
            break;
        case PROGRESSIVE:
            loop_times = -1;
            BOSS_APPEARANCE = rand()%3 + 1;
            break;
    }
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    Laser laser = {0, 0};
    ship.pos_x = (COLS/2) - ship.width/2;
    ship.pos_y = (LINES - LINES/5);

    Monster* monster = CreateMonsterSet(LINES/8, COLS/4, 0, difficulty, ship.waves_killed);
    Direction direction = RIGHT;

    PositionHolder pos_holder = ShootingMonsters(monster);
    int shooting_monster = 0;
    int monster_shoot = 0;
    int shooting_rate = rand()%10 + 50;

    char ch;
    int iter_counter = 1;
    int player_shoot = 0;
    int monster_laser_x = 0, monster_laser_y = 0;
    
    while(1) {
        if(loop_times == 0) {
            clear();
            mvprintw(LINES/2, COLS/2, "YOU WIN! BRAVOOOOO!");

            getch();
            endwin();

            return 0;
        }

        DisplayShip(ship, ship.pos_y, ship.pos_x);
        MoveMonster(monster, iter_counter++, direction);
        DisplayMonsters(monster);

        mvprintw(1, 1, "LIVES: %d", ship.lives);
        mvprintw(3, 1, "WAVES KILLED: %d", ship.waves_killed);

        if(iter_counter%shooting_rate == 0 && monster_shoot == 0) {
            monster_shoot = 1;
            shooting_rate = rand()%10 + 50;
            shooting_monster = rand()%(MONSTERS_PER_ROW);
            
            pos_holder = ShootingMonsters(monster);
            monster_laser_x = pos_holder.positions_X[shooting_monster];
            monster_laser_y = pos_holder.positions_Y[shooting_monster];
        }

        if(monster_shoot && iter_counter%MONSTER_LASER_BUFFER == 0) {
            mvprintw(++monster_laser_y,
                     monster_laser_x, "*");
        }

        if(isShipGetHit(monster_laser_y, monster_laser_x, ship)){
            ship.lives--;
            if(ship.lives == 0){
                clear();
                mvprintw(LINES/2, COLS/2, "YOU LOST. DO BETTER NEXT TIME !");

                getch();
                endwin();

                return 0;
            }
            
            monster_shoot = 0;
            monster_laser_x = 0;
            monster_laser_y = 0;
        }
        if(monster_laser_y == LINES) {
            monster_shoot = 0;
            monster_laser_x = 0;
            monster_laser_y = 0;
        }
        
        if(MaxX(monster) == COLS - COLS/15){
            MoveMonster(monster, iter_counter, DOWN);
            direction = LEFT;
        }
        if(MinX(monster) == COLS/15){
            MoveMonster(monster, iter_counter, DOWN);
            direction = RIGHT;
        }

        switch (ch = key_pressed()) {
            case 'd':
                if(ship.pos_x + ship.width < COLS - COLS/15)
                    ship.pos_x += 3;
                break;
            case 'q':
                if(ship.pos_x > COLS/15)
                    ship.pos_x -= 3;
                break;
            case ' ':
                if(!player_shoot){
                    laser.laser_x = ship.pos_x + ship.width/2;
                    laser.laser_y = ship.pos_y;
                    player_shoot = 1;
                }
                break;
        }
        if(laser.laser_y == 0) {
            player_shoot = 0;
        }

        if((isGettingHit(monster, laser.laser_y, laser.laser_x) && player_shoot == 1)){
            if(isEveryMonsterDead(monster, 0)) {
                ship.waves_killed++;
                if(ship.waves_killed%BOSS_APPEARANCE == 0){
                    monster = CreateBossInstance(LINES/8, COLS/2, difficulty, ship.waves_killed);
                    boss_fight = 1;
                }
                else{
                    if(boss_fight){
                        boss_fight = 0;
                        loop_times--;
                    }
                    monster = CreateMonsterSet(LINES/8, COLS/4, 0, difficulty, ship.waves_killed);
                }
            }
            player_shoot = 0;
            laser.laser_x = 0;
            laser.laser_y = 0;
        }
        
        if(player_shoot == 1 && iter_counter%LASER_BUFFER == 0){
            laser.laser_y -= 1;
            mvprintw(laser.laser_y, laser.laser_x, "⚡");
        }
        
        usleep(40000);

        refresh();
        clear();
    }

    freeList(monster);
    getch();
    endwin();
    
    return 0;
}