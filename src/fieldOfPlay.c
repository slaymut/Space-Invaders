#include "../headers/fieldOfPlay.h"


GameField InitializeField(int field_width, int field_length){
    char** field = (char**) malloc(field_length*sizeof(char *));

    for(int i = 0; i < field_length; i++)
        field[i] = (char *) malloc(field_width*sizeof(char));

    for(int i = 0; i < field_width; i++){
        field[0][i] = '-';
        field[field_length-1][i] = '-';
    }
    for(int i = 1; i < field_length-1; i++){
        for(int j = 0; j < field_width; j++){
            if(j == 0 || j == field_width-1)
                field[i][j] = '|';
            else
                field[i][j] = ' ';
        }
    }

    GameField gField = {field, field_length, field_width};
    return gField;
}


void SetupSpaceship(char* filepath){
    FILE *file = fopen(filepath, "r"); // read mode
    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    Spaceship ship;
    ship = InitSpaceship(filepath);

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

    for(int meow = 0; meow < i+1; meow++){
        printf("%s\n", ship.model[meow]);
    }

    fclose(file);
}