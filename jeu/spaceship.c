#include "backend.h"

struct Spaceship *createSpaceship(int x, int y) {
  struct Spaceship *spaceship = malloc(sizeof(struct Spaceship));

  /* Le vaisseau spatial a initialement des munitions de 3 et c'est son max de munitions */
  spaceship -> image = "_/^\\_";
  spaceship -> x     = x;
  spaceship -> y     = y;
  spaceship -> ammo  = 3;

  return spaceship;
}

enum Status commandSpaceship(Board *board, enum Command com) {
  int new_x, i;
  int shoot = false;

  switch(com) {
    case LEFT:
      new_x = board -> spaceship -> x - 1;
      break;
    case RIGHT:
      new_x = board -> spaceship -> x + 1;
      break;
    case SHOOT:
      new_x = board -> spaceship -> x;
      shoot = true;
      break;
    case HOLD:
      new_x = board -> spaceship -> x;
      break;
  }

  /* Si alien n'est pas NULL alors il y a des aliens */
  int exit_c = true;
  struct Alien *alien = NULL;
  for(i = 0; i < NO_ALIENS; i++) {
    alien = board -> aliens[i];
    if( alien != NULL ) exit_c = false ;
  }
  if( exit_c )
    return ALIENS_DEFEATED;

  /* Vérifie la collision avec alien_bomb */
  if( board -> alien_bomb != NULL) {
    if( (board -> alien_bomb -> y == board -> spaceship -> y) && 
      (new_x == board -> alien_bomb -> x || new_x + 1 == board -> alien_bomb -> x 
        || new_x + 2 == board -> alien_bomb -> x || new_x + 3 == board -> alien_bomb -> x
        || new_x + 4 == board -> alien_bomb -> x) ) {
      free(board -> alien_bomb);
      board -> alien_bomb = NULL;
      return SHOT_DOWN;
    }
  }

  /* Vérifie si on est toujours à l'intérieur des frontières de l'ecran */
  if(new_x <= 0 || new_x + 5 >= board -> max_x)
    return GAME_ON;

  /* Bouge le vaisseau */
  if(!shoot) {
    board -> spaceship -> x = new_x;
    return GAME_ON;
  }

  /* Verifie les munitions */
  if(board -> spaceship -> ammo > 0) {
    board -> spaceship -> ammo = 0;
    fireSpaceshipBullet(board, board -> spaceship -> x + 2, board -> spaceship -> y);
    return GAME_ON;
  }

  return GAME_ON;
}

void fireSpaceshipBullet(Board *board, int start_x, int start_y) {
  struct Bullet *bullet = malloc(sizeof(struct Bullet));
  bullet -> x = start_x; bullet -> y = start_y; 
  bullet -> symbol = '!';

  board -> spaceship -> bullet = bullet;
}

void moveSpaceshipBullets(Board *board) {
  /* Vérifie si la balle a tiré */
  if(board -> spaceship -> bullet == NULL) 
    return;

  if(board -> spaceship -> bullet -> y - 1 < 0) {
    free(board -> spaceship -> bullet);
    board -> spaceship -> bullet = NULL;
    board -> spaceship -> ammo = 1;
    return;
  }else {
    board -> spaceship -> bullet -> y--;
    checkBulletCollision(board);
  }
}