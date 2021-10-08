#include "../headers/spaceship.h"

void AfficherVaisseau()
{
    char ch;
    FILE *file = fopen("Textures/Monsters/monster1.txt", "r"); // read mode

    //Get file size for malloc
    fseek(file, 0, SEEK_END);
    int size = ftell(file); 
    fseek(file, 0, SEEK_SET);

    char *vaisseau = malloc(sizeof(char)*size);

    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    int i=0;
    while((ch = fgetc(file)) != EOF){
        vaisseau[i] = ch;
        i++;
    }

   printf("%s\n", vaisseau);

   fclose(file);
}