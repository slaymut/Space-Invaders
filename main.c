#include "headers/spaceship.h"
#include "headers/monsters.h"
#include "headers/fieldOfPlay.h"
#include "headers/backend.h"
#include "headers/frontend.h"
#include <menu.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmodex/fmod.h>

int main (int argc, char **argv)
{ 
    /* Start ncurses */
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(FALSE);
	nodelay(stdscr, TRUE);  /* Arrête les ncurses en attente de la saisie d'entrée du joueur */

	/* fonction main  */
    mainMenu();
}


/* Music */
int main(int argc, char *argv[])
{
    SDL_Surface *ecran = NULL, *pochette = NULL;
    SDL_Event event;
    SDL_Rect position;
    int continuer = 1;

    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    FMOD_RESULT resultat;

    
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    /* On ouvre la musique */
    resultat = FMOD_System_CreateSound(system, "laser.wav", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

  
    if (resultat != FMOD_OK)
    {
        fprintf(stderr, "Impossible de lire le fichier wav\n");
        exit(EXIT_FAILURE);
    }

    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(musique, -1);

    /* On joue la musique */
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Gestion du son avec FMOD", NULL);
    position.x = 0;
    position.y = 0;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_QUIT:
            continuer = 0;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_p) //Si on appuie sur P
            {
                FMOD_CHANNELGROUP *canal;
                FMOD_BOOL etat;
                FMOD_System_GetMasterChannelGroup(system, &canal);
                FMOD_ChannelGroup_GetPaused(canal, &etat);
            
                if (etat) // Si la chanson est en pause
                    FMOD_ChannelGroup_SetPaused(canal, 0); // On enlève la pause
                else // Sinon, elle est en cours de lecture
                    FMOD_ChannelGroup_SetPaused(canal, 1); // On active la pause
            }
            break;
        }

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
        SDL_BlitSurface(pochette, NULL, ecran, &position);
        SDL_Flip(ecran);
    }

    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);

    SDL_FreeSurface(pochette);
    SDL_Quit();

    
}

/* Menu principal  */

FILE* Fichier; 
Fichier = fopen("SPACEINVADERS.txt","r"); 
char Buffer[128]; 
while( fgets(Buffer,128,Fichier) ) 

printf("%s",Buffer); 
fclose(Fichier); 

char *m_choices[] = {
  "Play the game",
  "Choice difficult",
  "How to play",
  "Exit",
  (char *)NULL,
};

int EXIT = false;

/* Fonction extraite de la page ncurses */
void printInMiddle(WINDOW *win, int start_y, int start_x, int width, char *string) {
  int length, x, y;
  float temp;

  
  if(win == NULL)
    win = stdscr;
  getyx(win, y, x);
  if(start_x != 0)
    x = start_x;
  if(start_y != 0)
    y = start_y;
  if(width == 0)
    width = 80;

  length = strlen(string);
  temp = (width - length)/ 2;
  x = start_x + (int)temp;
  mvwprintw(win, y, x, "%s", string);
  refresh();
}

int playGame(){
        setlocale(LC_ALL, "");

    initscr(); raw(); noecho(); cbreak(); curs_set(0);
    //start_color();

    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    // init_pair(4, COLOR_WHITE, COLOR_BLACK);
    // wbkgd(stdscr, COLOR_PAIR(4));
    
    int x[50];
    int y[50];

    time_t t;
    srand(time(&t));
    Difficulty difficulty = DIFFICILE;
    GameConfig* config = malloc(sizeof(GameConfig));
    config->iter_counter = 1;
    config->lives[0] = "🧡";
    config->lives[1] = "💛";
    config->lives[2] = "💚";

    switch (difficulty) {
        case FACILE:
            config->loop_times = 2;
            config->BOSS_APPEARANCE = 3;
            break;
        case DIFFICILE:
            config->loop_times = 3;
            config->BOSS_APPEARANCE = 2;
            break;
        case PROGRESSIVE:
            config->loop_times = -1;
            config->BOSS_APPEARANCE = rand()%3 + 1;
            break;
    }
    
    Spaceship ship = SetupSpaceship("Textures/Player/spaceship.txt");
    ship.pos_x = (COLS/2) - ship.width/2;
    ship.pos_y = (LINES - LINES/5);

    Monster* monster = CreateMonsterSet(LINES/8, COLS/4, 0, difficulty, ship.waves_killed);
    Direction direction = RIGHT;

    PositionHolder pos_holder = ShootingMonsters(monster);
    
    int player_shoot = 0;
    int monster_laser_x = 0, monster_laser_y = 0;
    
    
    while(1) {
        if(config->loop_times == 0) {
            clear();
            mvprintw(LINES/2, COLS/2, "YOU WIN! BRAVOOOOO!");

            getch();
            endwin();

            return 0;
        }


        if(config->iter_counter%20 == 0) {
            for(int i = 0; i < 50; i++) {
                x[i] = rand()%COLS +3;
                y[i] = rand()%LINES +3;
            }
        }
        
        for(int i = 0; i < 50; i++) {
            mvprintw(y[i], x[i], "%c", '*');
        }

        DisplayShip(ship, ship.pos_y, ship.pos_x);
        MoveMonster(monster, config->iter_counter++, direction);
        
        if(config->iter_counter%monster->print_cpt == 0) {
            config->model++;
        }

        DisplayMonsters(monster, config->model%2);

        mvprintw(1, 1, "LIVES: %s %s %s", config->lives[0], config->lives[1], config->lives[2]);
        mvprintw(1, COLS - 10, "SCORE: %d", config->score);

        if(config->monster_shoot == 0) {
            config->monster_shoot = 1;
            config->shooting_monster = rand()%(MONSTERS_PER_ROW);
            
            pos_holder = ShootingMonsters(monster);
            monster_laser_x = pos_holder.positions_X[config->shooting_monster]+monster->width/2;
            monster_laser_y = pos_holder.positions_Y[config->shooting_monster]+monster->height;
        }

        if(config->monster_shoot && config->iter_counter%MONSTER_LASER_BUFFER == 0) {
            mvprintw(++monster_laser_y,
                     monster_laser_x, "🔥");
        }

        if(isShipGetHit(monster_laser_y, monster_laser_x, ship)){
            ship.lives--;
            config->lives[ship.lives] = " ";
            if(ship.lives == 0){
                clear();
                mvprintw(LINES/2, COLS/2, "YOU LOST. DO BETTER NEXT TIME !");

                getch();
                endwin();

                return 0;
            }
            
            config->monster_shoot = 0;
            monster_laser_x = 0;
            monster_laser_y = 0;
        }
        if(monster_laser_y == LINES) {
            config->monster_shoot = 0;
            monster_laser_x = 0;
            monster_laser_y = 0;
        }
        
        if(MaxX(monster) == COLS - COLS/15){
            MoveMonster(monster, config->iter_counter, DOWN);
            direction = LEFT;
        }
        if(MinX(monster) == COLS/15){
            MoveMonster(monster, config->iter_counter, DOWN);
            direction = RIGHT;
        }

        switch (key_pressed()) {
            case 'd':
                if(ship.pos_x + ship.width < COLS - COLS/15)
                    ship.pos_x += 3;
                break;
            case 'q':
                if(ship.pos_x > COLS/15)
                    ship.pos_x -= 3;
                break;
            case ' ':
                if(!player_shoot){
                    ship.laser_y = ship.pos_y;
                    ship.laser_x = ship.pos_x + ship.width/2;
                    player_shoot = 1;
                }
                break;
        }
        if(ship.laser_y == 0) {
            player_shoot = 0;
        }
        int temp_score = 0;
        if((temp_score = isGettingHit(monster, ship.laser_y, ship.laser_x)) && player_shoot == 1){
            if(isEveryMonsterDead(monster, 0)) {
                ship.waves_killed++;
                if(ship.waves_killed%config->BOSS_APPEARANCE == 0){
                    monster = CreateBossInstance(LINES/8, COLS/2, difficulty, ship.waves_killed);
                    config->boss_fight = 1;
                }
                else{
                    if(config->boss_fight){
                        config->boss_fight = 0;
                        config->loop_times--;
                    }
                    monster = CreateMonsterSet(LINES/8, COLS/4, 0, difficulty, ship.waves_killed);
                }
            }
            if(temp_score > 1) {
                config->score += temp_score;
            }
            player_shoot = 0;
            ship.laser_x = 0;
            ship.laser_y = 0;
        }
        
        if(player_shoot == 1 && config->iter_counter%LASER_BUFFER == 0){
            ship.laser_y -= 1;
            mvprintw(ship.laser_y, ship.laser_x, "⚡");
        }
        
        usleep(50000);

        refresh();
        clear();
    }

    freeList(monster);
    getch();
    endwin();
    
    return 0;
}

void howToPlay(void) {
  int width, height;
  width = 28; height = 10;

  /* Fenêtre de configuration */
  WINDOW *win;
  win = newwin(height , width, (LINES - height) /2, (COLS - width) /2);
  
  /* Dessine la fenetre de configuration */ 
  box(win, 0, 0);
  mvwaddch(win, 2, 0, ACS_LTEE);
  mvwhline(win, 2, 1, ACS_HLINE, 26);
  mvwaddch(win, 2, 27, ACS_RTEE);

  wattron(win , A_STANDOUT);
  printInMiddle(win, 8, 0, 28, "* Back");
  wattroff(win ,A_STANDOUT);

  mvwprintw(win, 3, 1, "-x-   is worth 10 points");
  mvwprintw(win, 4, 1, "<o>   is worth 20 points");
  mvwprintw(win, 5, 1, "/-\\   is worth 30 points");
  mvwprintw(win, 6, 1, "~o0o~ is worth 50 points");

  wrefresh(win);

  int ch;
  while( (ch = wgetch(win)) != 10 ) {

  }

  werase(win);
  wrefresh(win);
  delwin(win);
}


void exitGame(void) {
  EXIT = true;
}

void mainMenu(void) {
  ITEM **m_items;
  MENU *main_menu;
  WINDOW *main_menu_win;
  int c, i, n_choices;

  /* Crée les items */
  n_choices = 4;
  m_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
  for(i = 0; i < n_choices; ++i)
      m_items[i] = new_item(m_choices[i], "");
  set_item_userptr(m_items[0], playGame);
  set_item_userptr(m_items[1], howToPlay);
  set_item_userptr(m_items[2], exitGame);

  /* Creation du menu */
  main_menu = new_menu((ITEM **)m_items);

  /* Définir l'option de menu pour ne pas afficher la description */
  menu_opts_off(main_menu, O_SHOWDESC);

  /* Créer la fenêtre à associer au menu */
  main_menu_win = newwin(8, 20, (LINES - 8) /2, (COLS - 20) /2);
  keypad(main_menu_win, TRUE);
  
  /* Définir la fenêtre principale et la sous-fenêtre */
  set_menu_win(main_menu, main_menu_win);
  set_menu_sub(main_menu, derwin(main_menu_win, 4, 18, 3, 1));

  /* Définir les contours du menu sur la chaîne " * " */
  set_menu_mark(main_menu, " * ");

  while(!EXIT) {
    /* Affiche le menu */
    post_menu(main_menu); 
    wrefresh(main_menu_win); 
    box(main_menu_win, 0, 0);
    printInMiddle(main_menu_win, 1, 0, 5, "SPACE INVADERS");
    printInMiddle(main_menu_win, 1, 0, 20, "Main Menu");
    mvwaddch(main_menu_win, 2, 0, ACS_LTEE);
    mvwhline(main_menu_win, 2, 1, ACS_HLINE, 18);
    mvwaddch(main_menu_win, 2, 19, ACS_RTEE);


    c = wgetch(main_menu_win);
    switch(c) {
      case KEY_DOWN:
        menu_driver(main_menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(main_menu, REQ_UP_ITEM);
        break;
      case 10: {  /* Entrer */
        ITEM *cur;
        void (*p)(void);

        // unpost_menu(main_menu);
        // wrefresh(main_menu_win);

        cur = current_item(main_menu);
        p = item_userptr(cur);
        p();
        pos_menu_cursor(main_menu);
        break;
      }
    }
    wrefresh(main_menu_win);
  }
  /* Libére la mémoire */
  unpost_menu(main_menu); 
  free_menu(main_menu); 
  for(i = 0; i < n_choices; ++i)
    free_item(m_items[i]);
}
