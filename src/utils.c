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

int isGameOver(Monster* monster, int ship_y) {
    if(MaxY(monster, 0) >= ship_y - 3){
        return 1;
    }
    return 0;
}