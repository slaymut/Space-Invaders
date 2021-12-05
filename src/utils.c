#include "../headers/utils.h"

char key_pressed()
{
    struct termios oldterm, newterm;

    int oldfd; char c, result = 0;
    tcgetattr (STDIN_FILENO, &oldterm);
    
    newterm = oldterm; newterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (STDIN_FILENO, TCSANOW, &newterm);
    oldfd = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl (STDIN_FILENO, F_SETFL, oldfd | O_NONBLOCK);
    
    c = getchar();
    tcsetattr (STDIN_FILENO, TCSANOW, &oldterm);
    fcntl (STDIN_FILENO, F_SETFL, oldfd);
    
    if (c != EOF) {
        ungetc(c, stdin);
        result = getchar();
    }
    return result;
}

void open_screens_files(char* filename, int start_y, int start_x) {
    char filepath[30] = "Textures/screens/";
    strcat(filepath, filename);

    FILE* file = fopen(filepath, "r");

    if (file == NULL){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    char ch;
    int height = 0;
    int width = 0;
    attron(A_BOLD);
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n'){
            height++; width=0;
        }else{
            width++;
        }
        mvprintw(start_y + height, start_x + width, "%c", ch);
    }

    for(int i = 0; i < LINES; i += rand()%2 + 2) {
        for(int j = rand()%5; j < COLS; j += rand()%10 + 10) {
            if(!(i < start_y + height +1 && i > start_y - 1 && j < start_x + width + 1 && j > start_x - 1)){
                mvprintw(i, j, "%c", '.');
            }
        }
    }

    attroff(A_BOLD);

    fclose(file);
}

void StartScreen() {
    open_screens_files("mainscreen.txt", LINES/8, COLS/2 - 29);
    attron(A_BLINK);
    attron(A_BOLD);
    attron(A_STANDOUT);
    mvprintw(LINES - LINES/3, COLS/2 - 12,  " PRESS ANY KEY TO PLAY ");
    attroff(A_BLINK);
    attroff(A_BOLD);
    attroff(A_STANDOUT);

    getch();
}

void WinScreen() {
    open_screens_files("winner.txt", LINES/3 - 4, COLS/2 - 28);
    attron(A_BLINK);
    attron(A_BOLD);
    attron(A_STANDOUT);
    mvprintw(LINES - LINES/3, COLS/2 - 13,  " THANK YOU FOR PLAYING ! ");
    attroff(A_BLINK);
    attroff(A_BOLD);
    attroff(A_STANDOUT);

    getch();
}

void GameOverScreen() {
    open_screens_files("loser.txt", LINES/3 - 4, COLS/2 - 33);
    attron(A_BLINK);
    attron(A_BOLD);
    attron(A_STANDOUT);
    mvprintw(LINES/2, COLS/2 - 12,  " GOOD LUCK NEXT TIME ! ");
    attroff(A_BLINK);
    attroff(A_BOLD);
    attroff(A_STANDOUT);

    getch();
}