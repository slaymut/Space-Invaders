#include "../headers/fieldOfPlay.h"


Spaceship SetupSpaceship(char* filepath){
    FILE *file = fopen(filepath, "r"); // read mode
    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    Spaceship ship;
    

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

    for(int meow = 0; meow < i; meow++){
        printf("%s", ship.model[meow]);
    }

    fclose(file);

    return ship;
}