//=======================================================//
// Fichier qui g�re les �toiles au fond de l'�cran       //
//=======================================================//
#ifndef _etoile
#define _etoile


//=======================================================//
// Structure pour identifier chaque �toile               //
//=======================================================//
struct etoile
{
  float x;
  float y;
};


//=======================================================//
// Fonction qui initialise le tbl d'�toile               //
//=======================================================//
void init_etoile(struct etoile tbl[1000])
{
  int i; // Bcl
  
  for(i=0;i<1000;i++)
  {
    // Coordonn�e sur l'�cran
    tbl[i].x=((float)(rand()%800)/400)-1;
    tbl[i].y=((float)(rand()%600)/300)-1;
  }
}


//=======================================================//
// Fonction qui bouge les �toiles sur l'�cran            //
//=======================================================//
void move_etoile(struct etoile tbl[1000])
{
  int i; // Bcl
  
  for(i=0;i<1000;i++)
  {
    // Bouge les �toiles vers la gauche
    tbl[i].x=tbl[i].x-0.003;
    
    // Si une �toile sort de l'�cran
    if(tbl[i].x<-1.0)
    {
      // Place l'�toile � droie de l'�cran
      tbl[i].x=1;
      
      // Change son ordonn�e
      tbl[i].y=((float)(rand()%600)/300)-1;
    }
    
  } // Fin de la boucle
}


//=======================================================//
// Fonction qui affiche les �toiles sur l'�cran          //
//=======================================================//
void fct_etoile(struct etoile tbl[1000])
{
  int i, j; // Bcl
  
  glBegin (GL_POINTS); // D�but du dessin
  
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
