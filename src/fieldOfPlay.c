#include "../headers/fieldOfPlay.h"


GameField* InitializeField(int field_width, int field_length){
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

    GameField* gField = malloc(sizeof(GameField));
    gField->field = field;
    gField->height = field_length;
    gField->width = field_width;

    return gField;
}


void InsertEntity(GameField* field, Spaceship space, int x, int y) {
    if(x < 0 || y < 0){
        return;
    }
    
    if((y + space.height) >= field->height){
        return;
    }


    for(int i = 0; i < space.height; i++) {
        for(int j = 0; j < space.width; j++) {
            field->field[y+i][x+j] = space.model[i][j];
        }
    }
}