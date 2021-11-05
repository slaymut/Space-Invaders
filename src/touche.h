//=======================================================//
// Fichier qui permet une gestion du clavier             //
//=======================================================//
#ifndef _clavier
#define _clavier

void fct_clavier(wParam)
{
  int i; // Bcl
  
  // Si on est pas dans le menu
  if(menu==0)
  {

    // Analyse le paramètre
    switch (wParam)
    {
      // Touche Echap
      case VK_ESCAPE:       
        PostQuitMessage(0);
        break;
      
      // Touche du Bas
      case VK_DOWN:
        if(Ay_fusee>-0.02) Ay_fusee=Ay_fusee-0.005;
        break;

      // Touche du haut
      case VK_UP:
        if(Ay_fusee<0.02) Ay_fusee=Ay_fusee+0.005;
        break;
        
      // Touche de la gauche
      case VK_LEFT:
        if(Ax_fusee>-0.02) Ax_fusee=Ax_fusee-0.005;
        break;

      // Touche du haut
      case VK_RIGHT:
        if(Ax_fusee<0.02) Ax_fusee=Ax_fusee+0.005;
        break;
      
      // Touche 5 du pad pour l'arrêt de secours !
      case VK_TAB:
        Ax_fusee=0;
        Ay_fusee=0;
        break;
      
      // Touche espace pour tirer
      case VK_SPACE:
        // La barre d'espacement est déclenché
        shoot_fusee();
        break;

    }  // Fin du switch
  }
  //else // Si on est plus dans le menu, c'est qu'on est en train de jouer
  
}      // Fin de la fonction

#endif
