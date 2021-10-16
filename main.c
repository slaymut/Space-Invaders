#include "headers/spaceship.h"
#include "headers/fieldOfPlay.h"

#include <sys/ioctl.h>
#include <unistd.h>

int main (int argc, char **argv)
{
    struct winsize w;
    while(1){
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

        printf ("lines %d\n", w.ws_row);
        printf ("columns %d\n", w.ws_col);

        sleep(1);
    }
    return 0;  // make sure your main returns int
}


//int main(){
    //Spaceship space = SetupSpaceship("Textures/Player/spaceship.txt");

  //  return 0;
//}