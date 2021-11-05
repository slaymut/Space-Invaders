//=======================================================//
// Ce fichier est destin� � la mod�lisation des          //
// diff�rents objets du jeu                              //
//=======================================================//
#ifndef _model
#define _model

//=======================================================//
// Mod�lisation de la fus�e du h�ro                      //
//=======================================================//
void model_fusee(float x, float y)
{
  glBegin (GL_QUADS); // D�but du dessin des carr�s
  
  // Corps principale de la fus�e
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (0.04f+x, 0.1f+y);
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (0.04f+x , 0.06f+y);
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (0.2f+x , 0.06f+y);
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (0.2f+x, 0.1f+y); 
  
  // Canon du bas
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.04f+x, 0.04f+y);
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.04f+x , 0.02f+y);
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.1f+x, 0.02f+y);
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.1f+x , 0.04f+y);    
  
  // Aile du bas
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.02f+x, 0.0f+y);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.02f+x , 0.06f+y);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.1f+x , 0.06f+y);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.04f+x, 0.0f+y);  
  
  // Canon du haut
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.04f+x, 0.12f+y);
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.04f+x , 0.14f+y);
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.1f+x, 0.14f+y);
  glColor3f(1.0f,1.0f,0.0f);  glVertex2f (0.1f+x , 0.12f+y);   
  
  // Aile du haut
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.02f+x, 0.1f+y);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.02f+x , 0.16f+y);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.04f+x, 0.16f+y);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (0.1f+x , 0.1f+y);  
  
  glEnd (); // Fin du dessin
  
  glBegin (GL_TRIANGLES); // D�but du dessin des triangles
  
  // T�te de la fus�e
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (0.2f+x, 0.06f+y);
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (0.2f+x , 0.1f+y);
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (0.22f+x, 0.08f+y);
  
  // Vitre du cockpit
  glColor3f(0.0f,1.0f,1.0f);  glVertex2f (0.2f+x, 0.065f+y);
  glColor3f(0.0f,1.0f,1.0f);  glVertex2f (0.2f+x , 0.095f+y);
  glColor3f(0.0f,1.0f,1.0f);  glVertex2f (0.215f+x, 0.08f+y);  
  
  glEnd (); // Fin du dessin
}


//=======================================================//
// Mod�lisation des c�nes ennemis                        //
//=======================================================//
void model_cone(float x, float y, int couleur)
{
  glBegin (GL_TRIANGLES); // D�but du dessin des triangles
  
  // Couleur du c�ne
  if(couleur==0) glColor3f(0.0f,0.0f,1.0f);
  if(couleur==1) glColor3f(0.0f,1.0f,0.0f);
  if(couleur==2) glColor3f(1.0f,1.0f,0.0f);
  if(couleur==3) glColor3f(1.0f,0.0f,0.0f);
  
  // Dessine le c�ne
  glVertex2f (0.0f+x, 0.02f+y);
  glVertex2f (0.04f+x , 0.0f+y);
  glVertex2f (0.04f+x, 0.04f+y);
  
  glEnd (); // Fin du dessin
}


//=======================================================//
// Mod�lisation des pacmans                              //
//=======================================================//
void model_pacman(float x, float y, int couleur)
{
  glBegin (GL_QUADS); // D�but du dessin des triangles
  
  // Canon ( jaune )
  glColor3f(1.0f,1.0f,0.0f);
  glVertex2f (0.00f+x, 0.02f+y);
  glVertex2f (0.04f+x, 0.02f+y);
  glVertex2f (0.04f+x, 0.04f+y);
  glVertex2f (0.00f+x, 0.04f+y);  
  
  // Couleur du bonhomme
  if(couleur==0) glColor3f(0.0f,0.0f,1.0f);
  if(couleur==1) glColor3f(0.0f,1.0f,0.0f);
  if(couleur==2) glColor3f(1.0f,1.0f,0.0f);
  if(couleur==3) glColor3f(1.0f,0.0f,0.0f);
  
  // Dessine le haut
  glVertex2f (0.06f+x, 0.12f+y);
  glVertex2f (0.1f+x,  0.12f+y);
  glVertex2f (0.14f+x, 0.08f+y);
  glVertex2f (0.02f+x, 0.08f+y);
  
  // Dessine au dessus de la bouche
  glVertex2f (0.02f+x, 0.06f+y);
  glVertex2f (0.14f+x,  0.06f+y);
  glVertex2f (0.14f+x, 0.08f+y);
  glVertex2f (0.02f+x, 0.08f+y);
  
  // Dessine � droite de la bouche
  glVertex2f (0.08f+x, 0.06f+y);
  glVertex2f (0.14f+x,  0.06f+y);
  glVertex2f (0.14f+x, 0.04f+y);
  glVertex2f (0.08f+x, 0.04f+y);

  // Dessine le bas du v�hicule
  glVertex2f (0.02f+x, 0.04f+y);
  glVertex2f (0.14f+x,  0.04f+y);
  glVertex2f (0.10f+x, 0.0f+y);
  glVertex2f (0.06f+x, 0.0f+y);
  
  glEnd (); // Fin du dessin
  
  // Dessine le cockpit du v�hicule
  glBegin (GL_TRIANGLES);
  glColor3f(0.0f,1.0f,1.0f);
  glVertex2f (0.028f+x, 0.08f+y);
  glVertex2f (0.06f+x, 0.08f+y);
  glVertex2f (0.06f+x, 0.112f+y);
  glEnd ();
}


#endif
