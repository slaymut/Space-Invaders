//=======================================================//
// Ce fichier est destin� � la mod�lisation de           //
// la barre de vie du vaisseau                           //
//=======================================================//

#ifndef _vie
#define _vie

void barre_affiche()
{
  // Affiche la barre
  glBegin (GL_QUADS); // D�but du dessin des carr�s
  
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (-1.0, 1.0f);
  glColor3f(1.0f,0.0f,0.0f);  glVertex2f (-1.0 , 0.98f);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (1-((float)gameover/125) , 0.98f);
  glColor3f(0.0f,0.0f,1.0f);  glVertex2f (1-((float)gameover/125), 1.0f); 
  glEnd(); // Fin du dessin
}

#endif
