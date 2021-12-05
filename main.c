#include "headers/utils.h"
#include "headers/frontend.h"

int main(int argc, char** argv) {
    setlocale(LC_ALL, "");

    initscr(); raw(); noecho(); cbreak(); curs_set(0);
    
    //start_color();
    // init_pair(3, COLOR_BLUE, COLOR_BLACK);
    // init_pair(2, COLOR_RED, COLOR_BLACK);
    // init_pair(1, COLOR_GREEN, COLOR_BLACK);
    // init_pair(4, COLOR_WHITE, COLOR_BLACK);
    // wbkgd(stdscr, COLOR_PAIR(4));
    
    time_t t;
    srand(time(&t));
    
    StartScreen();

    int input = MainMenu();
    Difficulty difficulty = input - 1;

    playGame(difficulty);

    return 0;
}