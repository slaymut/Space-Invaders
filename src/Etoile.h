//=======================================================//
// Fichier qui gère les étoiles au fond de l'écran       //
//=======================================================//
#ifndef _etoile
#define _etoile


//=======================================================//
// Structure pour identifier chaque étoile               //
//=======================================================//
struct etoile
{
  float x;
  float y;
};


//=======================================================//
// Fonction qui initialise le tbl d'étoile               //
//=======================================================//
void init_etoile(struct etoile tbl[1000])
{
  int i; // Bcl
  
  for(i=0;i<1000;i++)
  {
    // Coordonnée sur l'écran
    tbl[i].x=((float)(rand()%800)/400)-1;
    tbl[i].y=((float)(rand()%600)/300)-1;
  }
}


//=======================================================//
// Fonction qui bouge les étoiles sur l'écran            //
//=======================================================//
void move_etoile(struct etoile tbl[1000])
{
  int i; // Bcl
  
  for(i=0;i<1000;i++)
  {
    // Bouge les étoiles vers la gauche
    tbl[i].x=tbl[i].x-0.003;
    
    // Si une étoile sort de l'écran
    if(tbl[i].x<-1.0)
    {
      // Place l'étoile à droie de l'écran
      tbl[i].x=1;
      
      // Change son ordonnée
      tbl[i].y=((float)(rand()%600)/300)-1;
    }
    
  } // Fin de la boucle
}


//=======================================================//
// Fonction qui affiche les étoiles sur l'écran          //
//=======================================================//
void fct_etoile(struct etoile tbl[1000])
{
  int i, j; // Bcl
  
  glBegin (GL_POINTS); // Début du dessin
  
  for(i=0; i<1000; i++)
  {
    // Met la couleur
    glColor3f(1.0f,1.0f,1.0f);
    
    // Positionne le point
    glVertex2f (tbl[i].x, tbl[i].y);
  }
  
  glEnd (); // Fin du dessin
}

#endif
