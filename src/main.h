//=======================================================//
// Cette biblioth�que est la principale du programme     //
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
int menu=0;         // Variable qui indique que le menu est ferm�

float Ax_fusee=0;   // Enregistre l'acc�l�ration de l'abscisse de la fus�e
float Ay_fusee=0;   // Enregistre l'acc�l�ration de l'ordonn�e de la fus�e

float X_fusee=-1;   // Enregistre les coordonn�es de la fus�e
float Y_fusee=0;

// D�clare un tbl qui enregistre le d�placement des balles pour la fus�e
struct shoot tbl_shoot_fusee[100];

// D�clare un tbl qui enregistre les mouvements des ennemis
struct ennemis tbl_ennemis[Max_ennemis];

// D�clare un tbl qui enregistre le d�placement des balles des ennemis
struct shoot tbl_shoot_ennemis[Max_ennemis][100];

// Pour la fin du jeu
int gameover=0;

// Enregistre le score
int score=0;

//=======================================================//
// Librairies                                            //
//=======================================================//
#include <windows.h>  // Pour la fen�tre windows et la gestion de ses messages
#include <gl/gl.h>    // Pour OpenGL
#include <stdlib.h>   // Utilitaire
#include <time.h>     // Heure et date
#include <malloc.h>   // Pour la gestion de la m�moire
#include "etoile.h"   // Pour afficher les �toiles sur l'�cran
#include "modelisation.h" // Pour mod�liser les objets
#include "shooting.h" // Pour le tir
#include "ennemis.h"  // Gestion de l'ennemis
#include "contact.h"  // Gestion des collisions
#include "barre_de_vie.h"
#include "menu_jeu.h" // Fonction qui g�re le menu du jeu
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
 
    // Si l'on ferme la fen�tre
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
// Fonction qui g�re le jeu                              //
//=======================================================//
void fct_jeu(HDC hDC)
{
  // Vide l'�cran sur un fond noir
  glClearColor (0.0f, 0.0f, 0.0f, 0.0f);
  glClear (GL_COLOR_BUFFER_BIT);

  glPushMatrix ();
  
  // Affiche les �toiles
  move_etoile(tbl_etoile);
  fct_etoile(tbl_etoile);
  
  // Gestion des ennemis
  ennemis_move();
  ennemis_affiche();
  shoot_ennemis_move();
  shoot_ennemis_affiche();
  
  // Gestion des balles tir� par la fus�e
  shoot_fusee_move();
  shoot_fusee_affiche();
  
  // Gestion des collisions
  contact_balle();
  contact_fusee();
  contact_ennemis();
  contact_balle_fusee();
  
  // Gestion de la barre de vie
  barre_affiche();
  
  // Gestion des coordonn�es de la fus�e e prenant compte de l'acc�l�ration puis de
  // la sortie de l'�cran
  X_fusee=X_fusee+Ax_fusee;
  Y_fusee=Y_fusee+Ay_fusee;
  if(X_fusee>1-0.22) { X_fusee=1-0.22; Ax_fusee=0; }
  if(X_fusee<-1)     { X_fusee=-1    ; Ax_fusee=0; }
  if(Y_fusee>1-0.16) { Y_fusee=1-0.16; Ay_fusee=0; }
  if(Y_fusee<-1)     { Y_fusee=-1    ; Ay_fusee=0; }
  
  // Affiche la fus�e
  model_fusee(X_fusee,Y_fusee);
  
  glPopMatrix ();    // Actualise la matrice ( enfin j'suis pas sur )
  SwapBuffers (hDC); // Colle l'image calculer sur l'�cran
  Sleep (1);         // Temporise
}

#endif
