#include "headers/spaceship.h"
#include "headers/monsters.h"
#include "headers/fieldOfPlay.h"

int main (int argc, char **argv)
{ 
    setlocale(LC_ALL, "");

    initscr(); raw(); noecho(); cbreak(); curs_set(0);
    //start_color();

    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    // init_pair(4, COLOR_WHITE, COLOR_BLACK);
    // wbkgd(stdscr, COLOR_PAIR(4));
    


    time_t t;
    srand(time(&t));
    Difficulty difficulty = DIFFICILE;
    GameConfig* config = malloc(sizeof(GameConfig));
    config->iter_counter = 1;
    config->lives[0] = "🧡";
    config->lives[1] = "💛";
    config->lives[2] = "💚";

    switch (difficulty) {
        case FACILE:
            config->loop_times = 2;
            config->BOSS_APPEARANCE = 3;
            break;
        case DIFFICILE:
            config->loop_times = 3;
            config->BOSS_APPEARANCE = 2;
            break;
        case PROGRESSIVE:
            config->loop_times = -1;
            config->BOSS_APPEARANCE = rand()%3 + 1;
            break;
    }
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    ship.pos_x = (COLS/2) - ship.width/2;
    ship.pos_y = (LINES - LINES/5);

    Monster* monster = CreateMonsterSet(LINES/8, COLS/4, 0, difficulty, ship.waves_killed);
    Direction direction = RIGHT;

    PositionHolder pos_holder = ShootingMonsters(monster);
    
    int player_shoot = 0;
    int monster_laser_x = 0, monster_laser_y = 0;
    
    
    while(1) {
        if(config->loop_times == 0) {
            clear();

            int x[200];
            int y[200];
            for(int i = 0; i < 200; i++) {
                x[i] = rand()%COLS +3;
                y[i] = rand()%LINES +3;
            }
            for(int i = 0; i < 200; i++) {
                mvprintw(y[i], x[i], "%c", '*');
            }

            mvprintw(LINES/2, COLS/2, "YOU WIN! BRAVOOOOO!");
            
            
            
            getch();
            endwin();

            return 0;
        }

        // if(config->iter_counter%20 == 0) {
        //     for(int i = 0; i < 200; i++) {
        //         x[i] = rand()%COLS +3;
        //         y[i] = rand()%LINES +3;
        //     }
        // }
        // for(int i = 0; i < 200; i++) {
        //     mvprintw(y[i], x[i], "%c", '*');
        // }
        

        DisplayShip(ship, ship.pos_y, ship.pos_x);
        MoveMonster(monster, config->iter_counter++, direction);
        
        if(config->iter_counter%monster->print_cpt == 0) {
            config->model++;
        }

        DisplayMonsters(monster, config->model%2);

        mvprintw(1, 1, "LIVES: %s %s %s", config->lives[0], config->lives[1], config->lives[2]);
        mvprintw(1, COLS - 10, "SCORE: %d", config->score);

        if(config->monster_shoot == 0) {
            config->monster_shoot = 1;
            config->shooting_monster = rand()%(MONSTERS_PER_ROW);
            
            pos_holder = ShootingMonsters(monster);
            monster_laser_x = pos_holder.positions_X[config->shooting_monster]+monster->width/2;
            monster_laser_y = pos_holder.positions_Y[config->shooting_monster]+monster->height;
        }

        if(config->monster_shoot && config->iter_counter%MONSTER_LASER_BUFFER == 0) {
            mvprintw(++monster_laser_y,
                     monster_laser_x, "🔥");
        }

        if(isShipGetHit(monster_laser_y, monster_laser_x, ship)){
            ship.lives--;
            config->lives[ship.lives] = " ";
            if(ship.lives == 0){
                clear();
                mvprintw(LINES/2, COLS/2, "YOU LOST. DO BETTER NEXT TIME !");

                getch();
                endwin();

                return 0;
            }
            
            config->monster_shoot = 0;
            monster_laser_x = 0;
            monster_laser_y = 0;
        }
        if(monster_laser_y == LINES) {
            config->monster_shoot = 0;
            monster_laser_x = 0;
            monster_laser_y = 0;
        }
        
        if(MaxX(monster) == COLS - COLS/15){
            MoveMonster(monster, config->iter_counter, DOWN);
            direction = LEFT;
        }
        if(MinX(monster) == COLS/15){
            MoveMonster(monster, config->iter_counter, DOWN);
            direction = RIGHT;
        }

        switch (key_pressed()) {
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
                    ship.laser_y = ship.pos_y;
                    ship.laser_x = ship.pos_x + ship.width/2;
                    player_shoot = 1;
                }
                break;
        }
        if(ship.laser_y == 0) {
            player_shoot = 0;
        }
        int temp_score = 0;
        if((temp_score = isGettingHit(monster, ship.laser_y, ship.laser_x)) && player_shoot == 1){
            if(isEveryMonsterDead(monster, 0)) {
                ship.waves_killed++;
                if(ship.waves_killed%config->BOSS_APPEARANCE == 0){
                    monster = CreateBossInstance(LINES/8, COLS/2, difficulty, ship.waves_killed);
                    config->boss_fight = 1;
                    config->BOSS_APPEARANCE = rand()%3 + 1;
                }
                else{
                    if(config->boss_fight){
                        config->boss_fight = 0;
                        config->loop_times--;
                    }
                    monster = CreateMonsterSet(LINES/8, COLS/4, 0, difficulty, ship.waves_killed);
                }
            }
            if(temp_score > 1) {
                config->score += temp_score;
            }
            player_shoot = 0;
            ship.laser_x = 0;
            ship.laser_y = 0;
        }
        
        if(player_shoot == 1 && config->iter_counter%LASER_BUFFER == 0){
            ship.laser_y -= 1;
            mvprintw(ship.laser_y, ship.laser_x, "⚡");
        }
        
        usleep(50000);

        refresh();
        clear();
    }

    freeList(monster);
    getch();
    endwin();
    
    return 0;
}