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

    ship.model = (char**) malloc(row*sizeof(char *));
    for(int i = 0; i < row; i++)
        ship.model[i] = (char *) malloc(col*sizeof(char));
    ship.height = row;
    ship.width = col;
    ship.lives = 3;

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

void DisplayShip(Spaceship ship) {
    for(int i = 0; i < ship.height; i++){
        printf("%s\n", ship.model[i]);
    }
}

void AfficherLaser(int start_y, int start_x) {
    //wprintw(start_y, start_x, "|");
}