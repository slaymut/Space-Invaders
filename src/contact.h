//=======================================================//
// Ce fichier contient toute les fonctions qui détermine //
// les collisions                                        //
//=======================================================//
#ifndef _collision
#define _collision


//=======================================================//
// Fonction qui détermine la collision entre les balles  //
// de la fusée et des ennemis                            //
//=======================================================//
void contact_balle()
{
  int i, j, k; // Bcl
  
  for(i=0; i<Max_ennemis; i++) for(j=0; j<100; j++)
  {
    // Fait une recherche sur le tbl des balles de la fusée
    for(k=0; k<100; k++)
    {
      if((tbl_shoot_fusee[k].mvt==1) && (tbl_shoot_ennemis[i][j].mvt==1))
      {
        if(((tbl_shoot_fusee[k].x>=tbl_shoot_ennemis[i][j].x) && (tbl_shoot_fusee[k].x<=tbl_shoot_ennemis[i][j].x+0.02)) && ((tbl_shoot_fusee[k].y+0.02>=tbl_shoot_ennemis[i][j].y) && (tbl_shoot_fusee[k].y+0.02<=tbl_shoot_ennemis[i][j].y+0.02)) || ((tbl_shoot_fusee[k].x>=tbl_shoot_ennemis[i][j].x) && (tbl_shoot_fusee[k].x<=tbl_shoot_ennemis[i][j].x+0.02)) && ((tbl_shoot_fusee[k].y+0.14>=tbl_shoot_ennemis[i][j].y) && (tbl_shoot_fusee[k].y+0.14<=tbl_shoot_ennemis[i][j].y+0.02)))
        {
          tbl_shoot_fusee[k].mvt=0;
          tbl_shoot_ennemis[i][j].mvt=0;
        }
      }
    }
  }

}


//=================================================================//
// Fonction qui détermine une collision entre une balle et la fusée//
//=================================================================//
void contact_fusee()
{
  int i, j, k; // Bcl
  
  for(i=0; i<Max_ennemis; i++) for(j=0; j<100; j++)
  {
    // Si une balle touche l'avant de l'appareil
    if((X_fusee+0.2>=tbl_shoot_ennemis[i][j].x) && (X_fusee<=tbl_shoot_ennemis[i][j].x) && (tbl_shoot_ennemis[i][j].y<=Y_fusee+0.1) && (( tbl_shoot_ennemis[i][j].y+0.02)>=(Y_fusee+0.06)) && (tbl_shoot_ennemis[i][j].mvt==1))
    {
      gameover++;
    }
    
    // Si une balle touche l'aile du bas
    if((X_fusee+0.08>=tbl_shoot_ennemis[i][j].x) && (X_fusee<=tbl_shoot_ennemis[i][j].x) && (tbl_shoot_ennemis[i][j].y<=Y_fusee+0.06) && (( tbl_shoot_ennemis[i][j].y+0.02)>=Y_fusee) && (tbl_shoot_ennemis[i][j].mvt==1))
    {
      gameover++;
    }
    
    // Si une balle touche l'aile du haut
    if((X_fusee+0.08>=tbl_shoot_ennemis[i][j].x) && (X_fusee<=tbl_shoot_ennemis[i][j].x) && (tbl_shoot_ennemis[i][j].y>=Y_fusee+0.1) && (( tbl_shoot_ennemis[i][j].y+0.02)<=Y_fusee+0.19) && (tbl_shoot_ennemis[i][j].mvt==1))
    {
      gameover++;
    }
  }
  
}


//==================================================================//
// Fonction qui détermine une collision entre un ennemis et la fusée//
//==================================================================//
void contact_ennemis()
{
  int i, j; // Bcl
  
  for(i=0; i<Max_ennemis; i++)
  {
    // Si l'ennemis dans le tbl est valide
    if(tbl_ennemis[i].mvt==1)
    {
      // Dans le cas d'une rencontre avec un ennemis triangle
      if(tbl_ennemis[i].ennemis==0)
      {
        if((X_fusee+0.2>=tbl_ennemis[i].x) && (X_fusee<=tbl_ennemis[i].x) && (tbl_ennemis[i].y<=Y_fusee+0.1) && (( tbl_ennemis[i].y+0.03)>=(Y_fusee+0.06)) && (tbl_ennemis[i].mvt==1))
        {
          gameover++;
        }
    
        if((X_fusee+0.08>=tbl_ennemis[i].x) && (X_fusee<=tbl_ennemis[i].x) && (tbl_ennemis[i].y<=Y_fusee+0.06) && ((tbl_ennemis[i].y+0.02)>=Y_fusee) && (tbl_ennemis[i].mvt==1))
        {
          gameover++;
        }
    
        if((X_fusee+0.08>=tbl_ennemis[i].x) && (X_fusee<=tbl_ennemis[i].x) && (tbl_ennemis[i].y>=Y_fusee+0.1) && (( tbl_ennemis[i].y+0.02)<=Y_fusee+0.19) && (tbl_ennemis[i].mvt==1))
        {
          gameover++;
        }
      }
      else  // C'est un pacman
      {
        if((X_fusee+0.2>=tbl_ennemis[i].x) && (X_fusee<=tbl_ennemis[i].x+0.12) && (tbl_ennemis[i].y<=Y_fusee+0.04) && (( tbl_ennemis[i].y+0.12)>=(Y_fusee+0.08)) && (tbl_ennemis[i].mvt==1))
        {
          gameover++;
        }
    
        if((X_fusee+0.12>=tbl_ennemis[i].x+0.04) && (X_fusee<=tbl_ennemis[i].x+0.12) && (tbl_ennemis[i].y<=Y_fusee+0.08) && ((tbl_ennemis[i].y+0.12)>=Y_fusee) && (tbl_ennemis[i].mvt==1))
        {
          gameover++;
        }
    
        if((X_fusee+0.12>=tbl_ennemis[i].x+0.04) && (X_fusee<=tbl_ennemis[i].x+0.12) && (tbl_ennemis[i].y<=Y_fusee+0.16) && (tbl_ennemis[i].y+0.08>=Y_fusee+0.16) && (tbl_ennemis[i].mvt==1))
        {
          gameover++;
        }
      }
    }
  }

}


//==================================================================//
// Fonction qui détermine une collision entre un ennemis et une balle/
//==================================================================//
void contact_balle_fusee()
{
  int i, j, k; // Bcl
  
  for(i=0; i<Max_ennemis; i++)
  {
    for(j=0; j<100; j++)
    {
      if(tbl_ennemis[i].ennemis==0)
      {
        if((tbl_ennemis[i].x>=tbl_shoot_fusee[j].x) && (tbl_ennemis[i].x<=tbl_shoot_fusee[j].x+0.02) && (((tbl_ennemis[i].y>=tbl_shoot_fusee[j].y+0.02) && (tbl_ennemis[i].y<=tbl_shoot_fusee[j].y+0.04)) || ((tbl_ennemis[i].y>=tbl_shoot_fusee[j].y+0.12) && (tbl_ennemis[i].y<=tbl_shoot_fusee[j].y+0.14))) && (tbl_ennemis[i].mvt==tbl_shoot_fusee[j].mvt) && ( tbl_shoot_fusee[j].mvt==1))
        {      
          // Supprime l'ennemis
          tbl_ennemis[i].mvt=0;
          
          // Ajoute au score
          score++;
          
          // Affiche un autre
          for(k=0; k<score; k++) ennemis_ajoute(tbl_ennemis[i].ennemis, tbl_ennemis[i].niveau, tbl_ennemis[i].Ax, tbl_ennemis[i].Ay);
        }
      }
      else
      {
        if((tbl_ennemis[i].x+0.1>=tbl_shoot_fusee[j].x) && (tbl_ennemis[i].x+0.02<=tbl_shoot_fusee[j].x ) && (((tbl_ennemis[i].y>=tbl_shoot_fusee[j].y+0.02) && (tbl_ennemis[i].y<=tbl_shoot_fusee[j].y+0.16)) || ((tbl_ennemis[i].y>=tbl_shoot_fusee[j].y+0.12) && (tbl_ennemis[i].y<=tbl_shoot_fusee[j].y+0.14))) && (tbl_ennemis[i].mvt==tbl_shoot_fusee[j].mvt) && ( tbl_shoot_fusee[j].mvt==1))
        {      
          // Supprime l'ennemis
          tbl_ennemis[i].mvt=0;
          
          // Ajoute au score
          score++;
          
          // Affiche un autre
          for(k=0; k<score; k++) ennemis_ajoute(tbl_ennemis[i].ennemis, tbl_ennemis[i].niveau, tbl_ennemis[i].Ax, tbl_ennemis[i].Ay);
        }        
      }
    }
  }
}


#endif
