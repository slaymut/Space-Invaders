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
