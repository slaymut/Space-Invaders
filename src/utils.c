#include "../headers/utils.h"

void DisplayShip(Spaceship ship)
{
    for(int i = 0; i < ship.height; i++){
        printf("%s\n", ship.model[i]);
    }
}

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