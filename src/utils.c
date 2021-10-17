#include "../headers/utils.h"

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