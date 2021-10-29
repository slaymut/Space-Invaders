#include "../headers/monsters.h"

Monster* InitMonster(int lives) {
    FILE* file = fopen("Textures/Monsters/monster1.txt", "r");
    FILE* file_bis = fopen("Textures/Monsters/monster1.txt", "r");
    if (file == NULL || file_bis == NULL){
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
    while((ch = fgetc(file_bis)) != EOF){
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
    monster->print_cpt = 20;

    fclose(file);
    fclose(file_bis);

    return monster;
}

void InsertMonster(Monster* monster, int start_y, int start_x) {
    if(monster == NULL)
        return;
    
    if(monster->next == NULL){
        Monster* newMonster = InitMonster(1);
        newMonster->pos_y = start_y;
        newMonster->pos_x = start_x + newMonster->width;
        monster->next = newMonster;
        return;
    }
    if(monster->next)
        InsertMonster(monster->next, start_y, start_x);
    
}

Monster* CreateMonsterSet(int start_y, int start_x) {
    Monster* root = InitMonster(1);
    root->pos_y = start_y;
    root->pos_x = start_x;
    int spacer_y = 0;
    int spacer_x = 0;

    for(int j = 1; j <= NUMBER_OF_MROWS; j++) {
        for(int i = 0; i < NUMBER_OF_MONSTERS/NUMBER_OF_MROWS; i++){
            if(j == 1 && i == NUMBER_OF_MONSTERS/NUMBER_OF_MROWS - 1)
                break;
            spacer_x += 10;
            InsertMonster(root, (root->pos_y + spacer_y),
                                (root->pos_x + spacer_x) - root->width);
        }
        spacer_x = -10;
        spacer_y += 2;
    }

    return root;
}

void DisplayMonsters(Monster* root, int index/*, int limit_x, int limit_y*/) {
    if(root == NULL)
        return;
    
    for (int i = 0; i < root->height; i++) {
        mvprintw(root->pos_y, root->pos_x, "%s", root->model[i]);
    }
    if((index%root->print_cpt) == 0){
        root->pos_x++;
    }
    DisplayMonsters(root->next, index);
}