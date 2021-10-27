#include "../headers/monsters.h"

Monster* InitMonster(int lives) {
    FILE* file = fopen("Textures/Monsters/monster1.txt", "r");
    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    Monster* monster = malloc(sizeof(Monster));

    char ch;
    monster->height = 1;
    monster->width = 0;
    int tmp = 0;
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n'){
            monster->height++;tmp=0;
        }
        tmp++;
        if(monster->width < tmp)
            monster->width = tmp;
    }

    monster->model = (char**) malloc(monster->height*sizeof(char *));
    for(int i = 0; i < monster->height; i++)
        monster->model[i] = (char *) malloc(monster->width*sizeof(char));

    int i = 0, j = 0;
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n'){
            j = 0;
            i++;
        }
        else{
            monster->model[i][j] = ch;
            j++;
        }
    }

    monster->lives = lives;
    monster->next = NULL;

    fclose(file);

    return monster;
}

void InsertMonster(Monster* monster, int start_y, int start_x) {
    if(monster == NULL)
        return;
    
    if(monster->next == NULL){
        Monster* newMonster = InitMonster(1);
        newMonster->pos_y = start_y;
        newMonster->pos_x = start_x;
        monster->next = newMonster;
        return;
    }
    if(monster->next)
        InsertMonster(monster->next, start_y, start_x);
    
}

Monster* CreateMonsterSet(int nbr_of_monsters) {
    Monster* root = InitMonster(1);
    root->pos_y = 5;
    root->pos_x = 20;
    int spacer_x = root->width;
    for(int i = 0; i < nbr_of_monsters; i++){
        int spacer_y = root->height + 2;
        spacer_x += 10;
        InsertMonster(root, root->pos_y, root->pos_x + spacer_x);
    }

    return root;
}

void DisplayMonsters(Monster* root) {
    if(root == NULL)
        return;

    for (int i = 0; i < root->height; i++) {
        mvprintw(root->pos_y, root->pos_x, "%s", root->model[i]);
    }
    DisplayMonsters(root->next);
}