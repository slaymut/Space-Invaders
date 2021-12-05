#include "../headers/monsters.h"

Monster* InitMonster(int lives, int which_monster, int waves_killed, Difficulty diff) {
    const char suffix_1[4][20] = {"monster1_1.txt", "monster2_1.txt", "monster3_1.txt", "boss_1.txt"};
    const char suffix_2[4][20] = {"monster1_2.txt", "monster2_2.txt", "monster3_2.txt", "boss_2.txt"};
    
    which_monster = which_monster%3;

    char filename[40] = "Textures/Monsters/";
    strcat(filename, suffix_1[which_monster]);

    char filename2[40] = "Textures/Monsters/";
    strcat(filename2, suffix_2[which_monster]);


    FILE* file = fopen(filename, "r");
    FILE* file2 = fopen(filename2, "r");

    FILE* file_bis = fopen(filename, "r");

    if (file == NULL || file_bis == NULL || file2 == NULL){
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

    monster->model = (char**) calloc(monster->height, sizeof(char *));
    for(int i = 0; i < monster->height; i++)
        monster->model[i] = (char *) calloc(monster->width, sizeof(char));

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

    monster->model2 = (char**) calloc(monster->height, sizeof(char *));
    for(int i = 0; i < monster->height; i++)
        monster->model2[i] = (char *) calloc(monster->width, sizeof(char));

    i = 0, j = 0;
    while((ch = fgetc(file2)) != EOF){
        if(ch == '\n'){
            j = 0;
            i++;
        }
        else{
            monster->model2[i][j] = ch;
            j++;
        }
    }

    monster->lives = lives;
    monster->next = NULL;
    monster->print_cpt = 15;
    
    if(diff == DIFFICILE) {
        monster->print_cpt -= waves_killed;
    }
    
    if(diff == PROGRESSIVE && waves_killed%2 == 0) {
        monster->print_cpt -= waves_killed;
    }

    monster->score_gain = lives*10;
    monster->type_of_monster = which_monster+1;

    fclose(file);
    fclose(file_bis);
    fclose(file2);

    return monster;
}

void InsertMonster(Monster* monster, 
                   int start_y, 
                   int start_x, 
                   int index, 
                   int lives, 
                   int waves_killed,
                   Difficulty diff) {

    if(monster == NULL)
        return;
    
    if(monster->next == NULL){
        Monster* newMonster = InitMonster(lives, index, waves_killed, diff);
        newMonster->pos_y = start_y;
        newMonster->pos_x = start_x;
        monster->next = newMonster;
        return;
    }
    if(monster->next)
        InsertMonster(monster->next, start_y, start_x, index, lives, waves_killed, diff);
    
}

Monster* CreateMonsterSet(int start_y, int start_x,
                          int index, 
                          Difficulty diff,
                          int waves_killed) {
    int lives = 1;
    if(diff == DIFFICILE) {
        lives = MONSTER_ROWS;
    }
    if(diff == PROGRESSIVE) {
        lives = 1 + waves_killed;
    }

    Monster* root = InitMonster(lives, index, waves_killed, diff);
    root->pos_y = start_y;
    root->pos_x = start_x;
    int spacer_y = 0;
    int spacer_x = 0;

    for(int j = 1; j <= MONSTER_ROWS; j++) {
        for(int i = 0; i < MONSTERS_PER_ROW; i++){
            if(j == 1 && i == MONSTERS_PER_ROW - 1)
                break;
            spacer_x += 10;
            InsertMonster(root, (root->pos_y + spacer_y),
                                (root->pos_x + spacer_x), index, lives, waves_killed, diff);
        }
        index++;

        if(lives > 1 && (diff == FACILE || diff == DIFFICILE))
            lives--;
        else if(lives > 1 && diff == PROGRESSIVE) {
            lives /= 2;
        }

        spacer_x = -10;
        spacer_y += 1 + root->height;
    }

    return root;
}

void MoveMonster(Monster* monster, int buffer, Direction direction) {
    if(monster == NULL) return;

    if((buffer%monster->print_cpt) == 0){
        switch (direction) {
        case RIGHT:
            monster->pos_x++;
            break;
        case LEFT:
            monster->pos_x--;
            break;
        case DOWN:
            monster->pos_y++;    
            break;
        }
    }

    MoveMonster(monster->next, buffer, direction);
}

void DisplayMonsters(Monster* root, int model_number) {
    if(root == NULL)
        return;

    if(root->lives > 0) {
        attron(COLOR_PAIR(root->lives));
        if(model_number == 0){
            for (int i = 0; i < root->height; i++) {
                mvprintw(root->pos_y+i, root->pos_x, "%s", root->model[i]);
            }
        }
        else {
            for (int i = 0; i < root->height; i++) {
                mvprintw(root->pos_y+i, root->pos_x, "%s", root->model2[i]);
            }
        }
        attroff(COLOR_PAIR(root->lives));
    }
    DisplayMonsters(root->next, model_number);
}

int MaxX(Monster* monster) {
    Monster* temp = monster;
    int colmax = 0;

    while(temp != NULL) {
        if(temp->pos_x + temp->width > colmax && temp->lives > 0)
            colmax = temp->pos_x + temp->width;

        temp = temp->next;
    }

    free(temp);
    return colmax;
}

int MinX(Monster* monster) {
    Monster* temp = monster;
    int colmin = 50;

    while(temp != NULL) {
        if(temp->pos_x < colmin && temp->lives > 0)
            colmin = temp->pos_x;

        temp = temp->next;
    }

    free(temp);
    return colmin;
}

int MaxY(Monster* monster) {
    Monster* temp = monster;
    int rowmax = 0;

    while(temp != NULL) {
        if(temp->pos_y > rowmax && temp->lives > 0)
            rowmax = temp->pos_y;

        temp = temp->next;
    }

    free(temp);
    return rowmax;
}

void changePrintCPT(Monster* root) {
    if(root == NULL)
        return;

    root->print_cpt -= 2;
    changePrintCPT(root->next);
}

int isGettingHit(Monster* root, int laser_y, int laser_x) {
    if(root == NULL)
        return 0;

    if(laser_y >= root->pos_y && laser_y-1 <= root->pos_y + root->height-1){
        if(laser_x >= root->pos_x && laser_x <= root->pos_x + root->width){
            if(root->lives > 0) {
                root->lives--;
                if(root->lives == 0)
                    return root->score_gain;
                return 1;
            }
        }
    }
    return isGettingHit(root->next, laser_y, laser_x);
}

int isEveryMonsterDead(Monster* root, int check) {
    if(root == NULL)
        return 1;

    if(root->lives > 0)
        return 0;    
    
    return isEveryMonsterDead(root->next, check);
}


PositionHolder* ShootingMonsters(Monster* monsters) {
    PositionHolder* pos_holder = malloc(sizeof(PositionHolder));

    for(int i = 0; i < MONSTERS_PER_ROW; i++) {
        pos_holder->positions_X[i] = 0;
        pos_holder->positions_Y[i] = 0;
        pos_holder->monsters_alive[i] = 0;
    }

    Monster* temp = monsters;
    int row = 0;
    while(temp != NULL) {
        row++;
        if(temp->lives){
            pos_holder->positions_X[row%MONSTERS_PER_ROW] = temp->pos_x;
            pos_holder->positions_Y[row%MONSTERS_PER_ROW] = temp->pos_y;
            pos_holder->monsters_alive[row%MONSTERS_PER_ROW] = 1;
        }
        temp = temp->next;
    }

    free(temp);
    return pos_holder;
}

void freeList(Monster* monster) {
    Monster* tmp;

    while (monster != NULL)
    {
       tmp = monster;
       monster = monster->next;
       free(tmp);
    }
}

Monster* CreateBossInstance(int start_y,
                            int start_x, 
                            Difficulty diff,
                            int waves_killed) {
    int lives = 4;

    if(diff == DIFFICILE) {
        lives = 8;
    }
    if(diff == PROGRESSIVE) {
        lives = waves_killed*2;
    }

    Monster* root = InitMonster(lives, 3, waves_killed, diff);
    root->pos_y = start_y;
    root->pos_x = start_x;

    return root;
}