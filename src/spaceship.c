#include "../headers/spaceship.h"

void DisplayShip()
{
    FILE *file = fopen("Textures/Player/spaceship.txt", "r"); // read mode
    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    int file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    Spaceship ship = {malloc(sizeof(char)*file_size), 4};

    int i=0;
    char ch;
    while((ch = fgetc(file)) != EOF){
        ship.model[i] = ch;
        i++;
    }

   printf("%s\n\nThe Spaceship has %d lives\n", ship.model[1], ship.lives);

   fclose(file);
}