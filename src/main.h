//=======================================================//
// Cette bibliothèque est la principale du programme     //
// Elle collecte les informations des autres biblio      //
//=======================================================//

#ifndef _main
#define _main


//=======================================================//
// Variable                                              //
//=======================================================//
#define Xmax 800
#define Ymax 600
#define Max_ennemis 1
struct etoile tbl_etoile[1000];
int menu=0;         // Variable qui indique que le menu est fermé

float Ax_fusee=0;   // Enregistre l'accélération de l'abscisse de la fusée
float Ay_fusee=0;   // Enregistre l'accélération de l'ordonnée de la fusée

float X_fusee=-1;   // Enregistre les coordonnées de la fusée
float Y_fusee=0;

// Déclare un tbl qui enregistre le déplacement des balles pour la fusée
struct shoot tbl_shoot_fusee[100];

// Déclare un tbl qui enregistre les mouvements des ennemis
struct ennemis tbl_ennemis[Max_ennemis];

// Déclare un tbl qui enregistre le déplacement des balles des ennemis
struct shoot tbl_shoot_ennemis[Max_ennemis][100];

// Pour la fin du jeu
int gameover=0;

// Enregistre le score
int score=0;

//=======================================================//
// Librairies                                            //
//=======================================================//
#include <windows.h>  // Pour la fenêtre windows et la gestion de ses messages
#include <gl/gl.h>    // Pour OpenGL
#include <stdlib.h>   // Utilitaire
#include <time.h>     // Heure et date
#include <malloc.h>   // Pour la gestion de la mémoire
#include "etoile.h"   // Pour afficher les étoiles sur l'écran
#include "modelisation.h" // Pour modéliser les objets
#include "shooting.h" // Pour le tir
#include "ennemis.h"  // Gestion de l'ennemis
#include "contact.h"  // Gestion des collisions
#include "barre_de_vie.h"
#include "menu_jeu.h" // Fonction qui gère le menu du jeu
#include "touche.h"   // Gestion des touches du clavier


//=======================================================//
// Fonction qui analyse les messages windows             //
//=======================================================//
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    case WM_CREATE:
      return 0;
 
    // Si l'on ferme la fenêtre
    case WM_CLOSE:
      PostQuitMessage (0);
      return 0;

    case WM_DESTROY:
      return 0;

    // Si l'on appuie sur le clavier
    case WM_KEYDOWN:
      fct_clavier(wParam);
      return 0;

    default:
      return DefWindowProc (hWnd, message, wParam, lParam);
  }
}

//=======================================================//
// Fonction qui initialise le jeu                        //
//=======================================================//
void init_jeu(struct etoile tbl[1000])
{
  init_etoile(tbl_etoile);
  init_shoot_fusee();
  init_ennemis();
  init_shoot_ennemis();
}

//=======================================================//
// Fonction qui gère le jeu                              //
//=======================================================//
void fct_jeu(HDC hDC)
{
  // Vide l'écran sur un fond noir
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);

  glPushMatrix ();
  
  // Affiche les étoiles
  move_etoile(tbl_etoile);
  fct_etoile(tbl_etoile);
  
  // Gestion des ennemis
  ennemis_move();
  ennemis_affiche();
  shoot_ennemis_move();
  shoot_ennemis_affiche();
  
  // Gestion des balles tiré par la fusée
  shoot_fusee_move();
  shoot_fusee_affiche();
  
  // Gestion des collisions
  contact_balle();
  contact_fusee();
  contact_ennemis();
  contact_balle_fusee();
  
  // Gestion de la barre de vie
  barre_affiche();
  
  // Gestion des coordonnées de la fusée e prenant compte de l'accélération puis de
  // la sortie de l'écran
  X_fusee=X_fusee+Ax_fusee;
  Y_fusee=Y_fusee+Ay_fusee;
  if(X_fusee>1-0.22) { X_fusee=1-0.22; Ax_fusee=0; }
  if(X_fusee<-1)     { X_fusee=-1    ; Ax_fusee=0; }
  if(Y_fusee>1-0.16) { Y_fusee=1-0.16; Ay_fusee=0; }
  if(Y_fusee<-1)     { Y_fusee=-1    ; Ay_fusee=0; }
  
  // Affiche la fusée
  model_fusee(X_fusee,Y_fusee);
  
  glPopMatrix ();    // Actualise la matrice ( enfin j'suis pas sur )
  SwapBuffers (hDC); // Colle l'image calculer sur l'écran
  Sleep (1);         // Temporise
}

#endif
