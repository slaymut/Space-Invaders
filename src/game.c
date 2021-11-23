#include "../headers/game.h"

void PlayGame() {
    
    time_t t;
    srand(time(&t));
    Direction direction = RIGHT;
    GLOBAL_GAME_DIFFICULTY = DIFFICILE;

    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    Monster* monster = CreateMonsterSet(LINES/8, COLS/4, 0);
    
    PositionHolder pos_holder = ShootingMonsters(monster);
    int shooting_monster = 0;
    int monster_shoot = 0;
    int shooting_rate = rand()%10 + 50;

    int iter_counter = 1;
    
    int monster_laser_x = 0, monster_laser_y = 0;
    
    while(1) {
        DisplayShip(ship, ship.pos_y, ship.pos_x);
        MoveMonster(monster, iter_counter++, direction);
        DisplayMonsters(monster);

        mvprintw(1, 1, "LIVES: %d", ship.lives);

        if(iter_counter%shooting_rate == 0 && monster_shoot == 0) {
            monster_shoot = 1;
            shooting_rate = rand()%10 + 50;
            shooting_monster = rand()%(NUMBER_OF_MONSTERS_PER_ROW);
            
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
                mvprintw(LINES/2, COLS/4, "YOU LOST. DO BETTER NEXT TIME !");
                mvprintw(LINES/2+1, COLS/4, "PRESS A KEY TO EXIT.");
                return;
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
        
        if(MaxX(monster, 0) == COLS - COLS/15){
            MoveMonster(monster, iter_counter++, DOWN);
            direction = LEFT;
        }
        if(MinX(monster, 50) == COLS/15){
            MoveMonster(monster, iter_counter++, DOWN);
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
                if(!ship.player_shoot){
                    ship.lazr_x = ship.pos_x + ship.width/2;
                    ship.lazr_y = ship.pos_y;
                    ship.player_shoot = 1;
                }
                break;
        }
        
        ship = laserHitboxChecker(monster, ship);
        
        if(ship.player_shoot == 1 && iter_counter%LASER_BUFFER == 0){
            ship.lazr_y -= 1;
            mvprintw(ship.lazr_y, ship.lazr_x, "⚡");
        }
        
        usleep(50000);

        refresh();
        clear();
    }
}

int isGameOver(Monster* monster, int ship_y) {
    if(MaxY(monster, 0) >= ship_y - 3){
        return 1;
    }
    return 0;
}