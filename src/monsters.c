#include "../headers/monsters.h"

Monster* InitMonster(int lives, int which_monster) {
    const char suffix[4][15] = {"monster1.txt", "monster2.txt", "monster3.txt", "boss.txt"};
    
    char filename[30] = "Textures/Monsters/";
    strcat(filename, suffix[which_monster]);

    FILE* file = fopen(filename, "r");
    FILE* file_bis = fopen(filename, "r");

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

    monster->lives = lives;
    monster->next = NULL;
    monster->print_cpt = 10;
    monster->score_gain = lives*10;

    fclose(file);
    fclose(file_bis);

    return monster;
}

void InsertMonster(Monster* monster, int start_y, int start_x, int index, int lives) {
    if(monster == NULL)
        return;
    
    if(monster->next == NULL){
        Monster* newMonster = InitMonster(lives, index);
        newMonster->pos_y = start_y;
        newMonster->pos_x = start_x;
        monster->next = newMonster;
        return;
    }
    if(monster->next)
        InsertMonster(monster->next, start_y, start_x, index, lives);
    
}

Monster* CreateMonsterSet(int start_y, int start_x,
                          int index, 
                          Difficulty diff,
                          int waves_killed) {
    int lives = 1;
    if(diff == DIFFICILE) {
        lives = 3;
    }
    if(diff == PROGRESSIVE) {
        lives = waves_killed*2;
    }

    Monster* root = InitMonster(lives, index);
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
                                (root->pos_x + spacer_x), index, lives);
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

void DisplayMonsters(Monster* root) {
    if(root == NULL)
        return;
    
    if(root->lives > 0) {
        for (int i = 0; i < root->height; i++) {
            mvprintw(root->pos_y+i, root->pos_x, "%s", root->model[i]);
        }
    }
    DisplayMonsters(root->next);
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


PositionHolder ShootingMonsters(Monster* monsters) {
    PositionHolder pos_holder;

    Monster* temp = monsters;
    int row = 0;
    while(temp != NULL) {
        row++;
        if(temp->lives){
            pos_holder.positions_X[row%MONSTERS_PER_ROW] = temp->pos_x;
            pos_holder.positions_Y[row%MONSTERS_PER_ROW] = temp->pos_y;
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

Monster* CreateBossInstance(int start_y, int start_x, 
                          Difficulty diff,
                          int waves_killed) {
    int lives = 4;

    if(diff == DIFFICILE) {
        lives = 8;
    }
    if(diff == PROGRESSIVE) {
        lives = waves_killed*2;
    }

    Monster* root = InitMonster(lives, 3);
    root->pos_y = start_y;
    root->pos_x = start_x;

    return root;
}