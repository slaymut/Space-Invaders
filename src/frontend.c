#include "../headers/frontend.h"

char *choices[] = { 
			"EASY",
			"HARD",
			"PROGRESSIVE"
		  };

int n_choices = sizeof(choices) / sizeof(char *);


int playGame(Difficulty difficulty){

    clear();
    refresh();

    char *diff = malloc(sizeof(char)*15);
    switch (difficulty)
    {
    case FACILE:
        diff = "EASY";
        break;
    case DIFFICILE:
        diff = "HARD";
        break;
    case PROGRESSIVE:
        diff = "PROGRESSIVE";
        break;
    }

    GameConfig* config = initconfig();

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

    PositionHolder* pos_holder = ShootingMonsters(monster);
    
    int player_shoot = 0;
    int monster_laser_x = 0, monster_laser_y = 0;

    
    while(1) {
        if(config->loop_times == 0) {
            clear();            
            WinScreen();
            endwin();

            return 0;
        }

        DisplayShip(ship, ship.pos_y, ship.pos_x);
        MoveMonster(monster, config->iter_counter++, direction);
        
        if(config->iter_counter%monster->print_cpt == 0) {
            config->model++;
        }

        DisplayMonsters(monster, config->model%2);

        mvprintw(1, 1, "LIVES: %s %s %s", config->lives[0], config->lives[1], config->lives[2]);
        mvprintw(1, COLS - 20, "SCORE: %d", config->score);
        
        mvprintw(1, 20, "DIFFICULTY: %s", diff);

        if(config->monster_shoot == 0) {
            config->monster_shoot = 1;
            config->shooting_monster = rand()%(MONSTERS_PER_ROW);
            
            pos_holder = ShootingMonsters(monster);
            while(pos_holder->positions_X[config->shooting_monster] == -1) {
                config->shooting_monster = rand()%(MONSTERS_PER_ROW);
            }

            monster_laser_x = pos_holder->positions_X[config->shooting_monster]+monster->width/2;
            monster_laser_y = pos_holder->positions_Y[config->shooting_monster]+monster->height;
        }

        if(config->monster_shoot && config->iter_counter%MONSTER_LASER_BUFFER == 0) {
            mvprintw(++monster_laser_y,
                     monster_laser_x, "🔥");
        }

        if(isShipGetHit(monster_laser_y, monster_laser_x, ship)){
            ship.lives--;
            config->lives[ship.lives] = " ";
            if(ship.lives == 0){
                refresh();
                clear();
                GameOverScreen();
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
                    config->BOSS_APPEARANCE = rand()%3 + 1;
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


int MainMenu() {
    clear();
    refresh();


    WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;
		
	menu_win = newwin(20, 40, LINES/2 - 10, COLS/2 - 20);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				break;
			default:
				mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
	refresh();

    werase(menu_win);
    return highlight;
}

void print_menu(WINDOW *menu_win, int highlight)
{
	int x, y, i;

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) 
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices[i]);
		++y;
	}
	wrefresh(menu_win);
}

/* Menu principal  */
// char m_choices[4][20] = {
//   "YOUHOU",
//   "How to play",
//   "Exit",
//   (char *)NULL,
// };

// int EXIT = false;

/* Fonction extraite de la page ncurses */
// void printInMiddle(WINDOW *win, int start_y, int start_x, int width, char *string) {
//   int length, x, y;
//   float temp;

  
//   if(win == NULL)
//     win = stdscr;
//   getyx(win, y, x);
//   if(start_x != 0)
//     x = start_x;
//   if(start_y != 0)
//     y = start_y;
//   if(width == 0)
//     width = 80;

//   length = strlen(string);
//   temp = (width - length)/ 2;
//   x = start_x + (int)temp;
//   mvwprintw(win, y, x, "%s", string);
//   refresh();
// }


// void mainMenu(void) {

//     clear();
//     refresh();

//     ITEM **m_items;
//     MENU *main_menu;
//     WINDOW *main_menu_win;
//     int c, i, n_choices;

//     /* Crée les items */
//     n_choices = 4;
//     m_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
//     for(i = 0; i < n_choices; ++i)
//         m_items[i] = new_item(m_choices[i], "");
//     set_item_userptr(m_items[0], playGame);
//     set_item_userptr(m_items[1], howToPlay);
//     set_item_userptr(m_items[2], exitGame);

//     /* Creation du menu */
//     main_menu = new_menu((ITEM **)m_items);

//     /* Définir l'option de menu pour ne pas afficher la description */
//     menu_opts_off(main_menu, O_SHOWDESC);

//     /* Créer la fenêtre à associer au menu */
//     main_menu_win = newwin(LINES/2, COLS/2, (LINES - 8) /2, (COLS - 20) /2);
//     keypad(main_menu_win, TRUE);
    
//     /* Définir la fenêtre principale et la sous-fenêtre */
//     set_menu_win(main_menu, main_menu_win);
//     set_menu_sub(main_menu, derwin(main_menu_win, 4, 18, 3, 1));

//     /* Définir les contours du menu sur la chaîne " * " */
//     set_menu_mark(main_menu, " * ");

//     while(!EXIT) {
//         /* Affiche le menu */
//         post_menu(main_menu); 
//         wrefresh(main_menu_win); 
//         box(main_menu_win, 0, 0);
//         printInMiddle(main_menu_win, 1, 0, 20, "Main Menu");

//         c = wgetch(main_menu_win);
//         switch(c) {
//         case KEY_DOWN:
//             menu_driver(main_menu, REQ_DOWN_ITEM);
//             break;
//         case KEY_UP:
//             menu_driver(main_menu, REQ_UP_ITEM);
//             break;
//         case 10: {  /* Entrer */
//             ITEM *cur;
//             void (*p)(void);

//             // unpost_menu(main_menu);
//             // wrefresh(main_menu_win);

//             cur = current_item(main_menu);
//             p = item_userptr(cur);
//             p();
//             pos_menu_cursor(main_menu);
//             break;
//         }
//         }
//         wrefresh(main_menu_win);
//     }
//     /* Libére la mémoire */
//     unpost_menu(main_menu); 
//     free_menu(main_menu); 
//     for(i = 0; i < n_choices; ++i)
//         free_item(m_items[i]);
// }// void howToPlay(void) {
//     int width, height;
//     width = 28; height = 10;

//     /* Fenêtre de configuration */
//     WINDOW *win;
//     win = newwin(height , width, (LINES - height) /2, (COLS - width) /2);

//     /* Dessine la fenetre de configuration */ 
//     box(win, 0, 0);
//     mvwaddch(win, 2, 0, ACS_LTEE);
//     mvwhline(win, 2, 1, ACS_HLINE, 26);
//     mvwaddch(win, 2, 27, ACS_RTEE);

//     wattron(win , A_STANDOUT);
//     printInMiddle(win, 8, 0, 28, "* Back");
//     wattroff(win ,A_STANDOUT);

//     mvwprintw(win, 3, 1, "Q : Move Spaship to the RIGHT");
//     mvwprintw(win, 4, 1, "D : Move Spaceship to the LEFT");
//     mvwprintw(win, 5, 1, "Spacebar : Shoot");

//     wrefresh(win);

//     int ch;
//     while( (ch = wgetch(win)) != 10 ) {

//     }

//     werase(win);
//     wrefresh(win);
//     delwin(win);
// }

// void exitGame(void) {
//     EXIT = true;
// }

// void howToPlay(void) {
//     int width, height;
//     width = 28; height = 10;

//     /* Fenêtre de configuration */
//     WINDOW *win;
//     win = newwin(height , width, (LINES - height) /2, (COLS - width) /2);

//     /* Dessine la fenetre de configuration */ 
//     box(win, 0, 0);
//     mvwaddch(win, 2, 0, ACS_LTEE);
//     mvwhline(win, 2, 1, ACS_HLINE, 26);
//     mvwaddch(win, 2, 27, ACS_RTEE);

//     wattron(win , A_STANDOUT);
//     printInMiddle(win, 8, 0, 28, "* Back");
//     wattroff(win ,A_STANDOUT);

//     mvwprintw(win, 3, 1, "Q : Move Spaship to the RIGHT");
//     mvwprintw(win, 4, 1, "D : Move Spaceship to the LEFT");
//     mvwprintw(win, 5, 1, "Spacebar : Shoot");

//     wrefresh(win);

//     int ch;
//     while( (ch = wgetch(win)) != 10 ) {

//     }

//     werase(win);
//     wrefresh(win);
//     delwin(win);
// }