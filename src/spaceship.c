#include "../headers/spaceship.h"

Spaceship InitSpaceship(char* filepath){

    FILE* file = fopen(filepath, "r");
    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char ch;
    int row = 1, col = 0;
    int tmp = 0;
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n'){
            row++;
            tmp=0;
        }
        tmp++;
        if(col < tmp)
            col = tmp;
    }

    Spaceship ship;

    ship.model = (char**) calloc(row, sizeof(char *));
    for(int i = 0; i < row; i++)
        ship.model[i] = (char *) calloc(col, sizeof(char));
    
    ship.height = row;
    ship.width = col;
    ship.lives = 3;
    ship.waves_killed = 0;
    ship.laser_x = 0;
    ship.laser_y = 0;

    fclose(file);
    
    return ship;
}

Spaceship SetupSpaceship(char* filepath){
    FILE *file = fopen(filepath, "r"); // read mode
    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    Spaceship ship = InitSpaceship(filepath);

    int i=0, j=0;
    char ch;
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n'){
            j = 0;
            i++;
        }
        else{
            ship.model[i][j] = ch;
            j++;
        }
    }

    fclose(file);
    return ship;
}

void DisplayShip(Spaceship ship, int start_y, int start_x) {
    for(int i = 0; i < ship.height; i++) {
        mvprintw(start_y+i, start_x, ship.model[i]);
    }
}

int isShipGetHit(int laser_y, int laser_x, Spaceship ship) {
    if(laser_y >= ship.pos_y && laser_y-1 <= ship.pos_y + ship.height-1){
        if(laser_x >= ship.pos_x && laser_x <= ship.pos_x + ship.width){          
            return 1;
        }
    }
    return 0;
}