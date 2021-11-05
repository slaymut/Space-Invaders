//=======================================================//
// Ce fichier est destiné à la gestion du tir            //
//=======================================================//
#ifndef _shooting
#define _shooting


//=======================================================//
// Structure qui définis un ennemis                      //
//=======================================================//
struct ennemis
{
  float x;      
  float y;      
  float Ax;     // accélération horizontal
  float Ay;     // accélération vertical
  int ennemis;  // type d'ennemis
  int niveau;   // niveau de l'adversaire
  int mvt;
};


//=======================================================//
// Structure pour une balle                              //
//=======================================================//
struct shoot
{
  float x;
  float y;
  float vitesse;
  int mvt;
};


//=======================================================//
// Fonction qui initialise le tir de la fusée            //
//=======================================================//
void init_shoot_fusee()
{
  int i; // Bcl
  
  // Initialise le tbl en mettant aucun mvt de balle
  for(i=0;i<100;i++) tbl_shoot_fusee[i].mvt=0;
}


//=======================================================//
// Fonction qui initialise le tir des ennemis            //
//=======================================================//
void init_shoot_ennemis()
{
  int i, j; // Bcl
  
  // Initialise le tbl en mettant aucun mvt de balle
  for(i=0;i<Max_ennemis;i++) for(j=0;j<100;j++) tbl_shoot_ennemis[i][j].mvt=0;
}


//=======================================================//
// Fonction qui permet à la fusée de tirer               //
//=======================================================//
void shoot_fusee()
{
  int i; // Bcl
   
  // Recherche la première balle non déclenché et l'active
  for(i=0;i<100;i++)
  {
    if(tbl_shoot_fusee[i].mvt==0)
    {
      tbl_shoot_fusee[i].mvt=1;
      tbl_shoot_fusee[i].y=Y_fusee;
      tbl_shoot_fusee[i].x=X_fusee+0.1;
      return; // Sort de la boucle
    }
  }
}


//=======================================================//
// Fonction qui permet au ennemis de tirer               //
//=======================================================//
void shoot_ennemis(int num_ennemis)
{
  int i, j; // Bcl

  // Recherche la première balle non déclenché et l'active
  for(j=0;j<100;j++)
  {
    if(tbl_shoot_ennemis[num_ennemis][j].mvt==0)
    {
      tbl_shoot_ennemis[num_ennemis][j].mvt=1; 
      tbl_shoot_ennemis[num_ennemis][j].y=tbl_ennemis[num_ennemis].y+0.002;
      tbl_shoot_ennemis[num_ennemis][j].x=tbl_ennemis[num_ennemis].x;
      return; // Sort de la boucle
    }
  }
}


//=======================================================//
// Fonction qui avance toute les balles de la fusee      //
//=======================================================//
void shoot_fusee_move()
{
  int i; // Bcl
  
  // Parcoure le tbl et avance chaque balle lancé d'une unité
  for(i=0;i<100;i++)
  {
    // Bouge que s'il y a mouvement
    if(tbl_shoot_fusee[i].mvt==1)
    {
      if(tbl_shoot_fusee[i].x<1.0) tbl_shoot_fusee[i].x=tbl_shoot_fusee[i].x+0.005;
      else tbl_shoot_fusee[i].mvt=0; // La balle ne sert plus à rien en dehors de l'écran
    }
  }
}


//=======================================================//
// Fonction qui avance toute les balles des ennemis      //
//=======================================================//
void shoot_ennemis_move()
{
  int i, j; // Bcl
  
  // Parcoure le tbl et avance chaque balle lancé d'une unité
  for(i=0;i<Max_ennemis;i++) for(j=0;j<100;j++)
  {
    // Bouge que s'il y a mouvement
    if(tbl_shoot_ennemis[i][j].mvt==1)
    {
      if(tbl_shoot_ennemis[i][j].x>-1.0) tbl_shoot_ennemis[i][j].x-=0.01;
      else tbl_shoot_ennemis[i][j].mvt=0; // La balle ne sert plus à rien en dehors de l'écran
    }
  }
}


//=======================================================//
// Fonction qui affiche les balles pour la fusee         //
//=======================================================//
void shoot_fusee_affiche()
{
  int i; // Bcl
  
  for(i=0;i<100;i++)
  {
    glBegin (GL_QUADS); // Début du dessin
  
    // Bouge que s'il y a mouvement
    if(tbl_shoot_fusee[i].mvt==1)
    {
      // Affiche la balle du bas ( en jaune )
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.02f+tbl_shoot_fusee[i].x, 0.04f+tbl_shoot_fusee[i].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.02f+tbl_shoot_fusee[i].x , 0.02f+tbl_shoot_fusee[i].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.0f+tbl_shoot_fusee[i].x , 0.02f+tbl_shoot_fusee[i].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.0f+tbl_shoot_fusee[i].x, 0.04f+tbl_shoot_fusee[i].y); 

      // Affiche la balle du haut
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.02f+tbl_shoot_fusee[i].x, 0.14f+tbl_shoot_fusee[i].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.02f+tbl_shoot_fusee[i].x , 0.12f+tbl_shoot_fusee[i].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.0f+tbl_shoot_fusee[i].x , 0.12f+tbl_shoot_fusee[i].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.0f+tbl_shoot_fusee[i].x, 0.14f+tbl_shoot_fusee[i].y); 
    }
  }  
  glEnd (); // Fin du dessin
}


//=======================================================//
// Fonction qui affiche les balles des ennemis           //
//=======================================================//
void shoot_ennemis_affiche()
{
  int i, j; // Bcl
  
  for(i=0;i<Max_ennemis;i++) for(j=0;j<100;j++)
  {
    glBegin (GL_QUADS); // Début du dessin
  
    // Bouge que s'il y a mouvement
    if(tbl_shoot_ennemis[i][j].mvt==1)
    {
      // Affiche la balle
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.02f+tbl_shoot_ennemis[i][j].x, 0.0f+tbl_shoot_ennemis[i][j].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.02f+tbl_shoot_ennemis[i][j].x , 0.02f+tbl_shoot_ennemis[i][j].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.0f+tbl_shoot_ennemis[i][j].x , 0.02f+tbl_shoot_ennemis[i][j].y);
      glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.0f+tbl_shoot_ennemis[i][j].x, 0.0f+tbl_shoot_ennemis[i][j].y); 
    }
  }  
  glEnd (); // Fin du dessin
}


#endif
