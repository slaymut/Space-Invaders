#include "backend.h"
#include "frontend.h"
#include <string.h>

int ALIEN_SPEED = 190;

float timedifference_msec(struct timeval t0, struct timeval t1) {
  return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

enum Status play(WINDOW *win, Board *board, int lvl) {
  /* User input is held in d */
  int d;

  /* Controle pour les timers */ 
  /* Pour la vitesse des balles */
  struct timeval stopb, startb;
  double diff_tb = 0.0;
  gettimeofday(&startb, NULL);
  /* Pour la vitesse des aliens */
  struct timeval stopa, starta;
  double diff_ta = 0.0;
  gettimeofday(&starta, NULL);
  /* Pour la vitesse des aliens++ */
  struct timeval stops, starts;
  double diff_ts = 0.0;
  gettimeofday(&starts, NULL);
  /* Pour la vitesse des bomb d'aliens */
  struct timeval stopab, startab;
  double diff_tab = 0.0;
  gettimeofday(&startab, NULL);

  /* Monter le tableau */
  enum Command c = HOLD;
  enum Status s  = GAME_ON;
  int pause = false;

  /* Le jeu commence ici */
  while( (d = wgetch(win)) != 'q') {
    werase(win);
    displayBoard(board, win, lvl);

    /* Vérifier les conditions de l'ecran */
    if( s == SHOT_DOWN ) 
      s = respawnShip(board, win, lvl);
    if( s == ALIENS_DEFEATED) {
      return ALIENS_DEFEATED;
    }
    if( s == ALIENS_WON ) 
      return ALIENS_WON;

    c = getCommand(d);

    /* Commande Pause */
    if( c == PAUSE )
      pause = true;
    else if( c != HOLD )
      pause = false;
    if(pause)
      continue;

    /* Déplace le vaisseau spatial et vérifie son statut */
    s = commandSpaceship(board, c);

    /* Calcul de la vitesse */
    /* Déplace la balle toutes les 0,05 secondes */
    gettimeofday(&stopb, NULL);
    if(diff_tb >= BULLET_SPEED) {
      moveSpaceshipBullets(board);
      gettimeofday(&startb, NULL);
    }
    diff_tb = timedifference_msec(startb, stopb);

    /* Déplace les extraterrestres toutes les 0,15 secondes */
    gettimeofday(&stopa, NULL);
    if(diff_ta >= ALIEN_SPEED) {
      /* Déplace l'étranger et vérifiez son statut */
      s = moveAliens(board);
      gettimeofday(&starta, NULL);
    }
    diff_ta = timedifference_msec(starta, stopa);

    /* Déplacez l'alien++ spécial à 0,18 seconde */
    gettimeofday(&stops, NULL);
    if(diff_ts >= SPECIAL_ALIEN_SPEED) {
      moveSpecialAlien(board);
      gettimeofday(&starts, NULL);
    }
    diff_ts = timedifference_msec(starts, stops);

    /* Déplacez les bombs de l'alien++ spécial à 0,18 seconde */
    gettimeofday(&stopab, NULL);
    if(diff_tab >= ALIEN_BOMB_SPEED) {
      moveAlienBomb(board);
      gettimeofday(&startab, NULL);
    }
    diff_tab = timedifference_msec(startab, stopab);

    wrefresh(win);
  }
  return QUIT;
}

void updateBoard(Board *board) {
  board -> aliens          = createBlockOfAliens(1, 1);
  board -> alien_direction = RIGHT;
  board -> special_alien   = NULL;
  board -> alien_bomb      = NULL;
  board -> blocks          = createBlocks(board -> max_y);
}

void writeScoreToFile(int score) {
  FILE *fp;
  fp = fopen("high-scores.txt", "r");

  /* créez le fichier des high-scores*/
  if( fp == NULL ) {
    fp = fopen("high-scores.txt", "w");
    close(fp);
    fp = fopen("high-scores.txt", "r"); 
  }

  char f_str[70], s_str[70], l_str[70];
  char *f_s, *s_s, *l_s;
  f_s = fgets(f_str, 70, fp); s_s = fgets(s_str, 70, fp); l_s = fgets(l_str, 70, fp); 
  fclose(fp);

  fp = fopen("high-scores.txt", "w");
  int hold, *ptr;

  if(f_s == NULL) {
    fprintf(fp, "%ld\n", score);
    fclose(fp);
    return;
  }else if(s_s == NULL) {

    /* du plus haut au plus bas*/
    hold = strtol(f_str, &ptr, 10);
    if( score > hold ) {
      fprintf(fp, "%ld\n", score);
      fprintf(fp, "%s", f_str);
    }else {
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%ld\n",  score);
    }

    fclose(fp);
    return;
  }else if(l_s == NULL) {

    hold = strtol(f_str, &ptr, 10);
    if( score > hold ) {
      fprintf(fp, "%ld\n", score);
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%s", s_str);
    }else if( score > (hold = strtol(s_str, &ptr, 10)) ) {
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%ld\n", score);
      fprintf(fp, "%s", s_str);
    }else {
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%s", s_str);
      fprintf(fp, "%ld\n", score);
    }

    fclose(fp);
    return;
  }else {

    hold = strtol(f_str, &ptr, 10);
    if( score > hold ) {
      fprintf(fp, "%ld\n", score);
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%s", s_str);
    }else if( score > (hold = strtol(s_str, &ptr, 10)) ) {
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%ld\n", score);
      fprintf(fp, "%s", s_str);
    }else if ( score > (hold = strtol(l_str, &ptr, 10)) ) {
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%s", s_str);
      fprintf(fp, "%ld\n", score);
    }else {
      fprintf(fp, "%s", f_str);
      fprintf(fp, "%s", s_str);
      fprintf(fp, "%s", l_str);
    }

    fclose(fp);
    return;
  }
}