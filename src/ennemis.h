//=======================================================//
// Fichier qui gère les ennemis, leurs nombres, leur     //
// mouvements et leur difficulté                         //
//=======================================================//
#ifndef _ennemis
#define _ennemis


//=======================================================//
// Initialise le tbl des ennemis                         //
//=======================================================//
void init_ennemis()
{
  int i; // Bcl
  
  // Met tous à 0
  for(i=0;i<Max_ennemis;i++)
  {
    tbl_ennemis[i].mvt=0;
    tbl_ennemis[i].niveau=0;
    tbl_ennemis[i].ennemis=0;
  }
  
  // Met au niveau le plus facile
  tbl_ennemis[0].mvt=1;                
  tbl_ennemis[0].niveau=0; 
  tbl_ennemis[0].ennemis=0;  
  tbl_ennemis[0].x=1.0;
  tbl_ennemis[0].y=1.0-(float)(rand()%600)/300;
  tbl_ennemis[0].Ax=0.01;
  tbl_ennemis[0].Ay=0.001;
}


//=======================================================//
// Fonction qui rajoute un ennemis à l'écran             //
//=======================================================//
void ennemis_ajoute(int ennemis, int niveau, float Ax, float Ay)
{
  int i, j;  //Bcl
  
  // Parcoure le tbl et ajoute un ennemis
  for(i=0;i<Max_ennemis;i++)
  {
    // Si on trouve une place dans le tbl
    if(tbl_ennemis[i].mvt==0)
    {
      // Nouvelle ennemis
      tbl_ennemis[i].mvt=1;
      
      if(score<8*Max_ennemis) tbl_ennemis[i].ennemis=0;
      else tbl_ennemis[i].ennemis=1;
      
      if(score<Max_ennemis) tbl_ennemis[i].niveau=0;
      else if(score<4*Max_ennemis)tbl_ennemis[i].niveau=1;
      else if(score<6*Max_ennemis)tbl_ennemis[i].niveau=2;
      else if(score<8*Max_ennemis)tbl_ennemis[i].niveau=3;
      else if(score<10*Max_ennemis) tbl_ennemis[i].niveau=0;
      else if(score<12*Max_ennemis)tbl_ennemis[i].niveau=1;
      else if(score<14*Max_ennemis)tbl_ennemis[i].niveau=2;
      else tbl_ennemis[i].niveau=3;      
      
      tbl_ennemis[i].Ax=0.001*(niveau+1)*2;
      tbl_ennemis[i].Ay=0.001*((rand()%10)-5);
      tbl_ennemis[i].x=1.0;
      tbl_ennemis[i].y=1.0-(float)(rand()%600)/300;
      
      // Fin de la fonction
      break;
    }
  }
  
}


//=======================================================//
// Fonction qui gère le mouvement de chaque ennemis      //
//=======================================================//
void ennemis_move()
{
  int i; // Bcl
  
  for(i=0;i<Max_ennemis;i++)
  {
    if(tbl_ennemis[i].mvt==1)
    {
      // Fait les mouvements
      tbl_ennemis[i].x=tbl_ennemis[i].x-tbl_ennemis[i].Ax;
      tbl_ennemis[i].y=tbl_ennemis[i].y+tbl_ennemis[i].Ay;
      
      // Si on sort de l'écran
      if(tbl_ennemis[i].x<-1-0.14)
      {
        tbl_ennemis[i].mvt=0;
        ennemis_ajoute(tbl_ennemis[i].ennemis,tbl_ennemis[i].niveau, tbl_ennemis[i].Ax, tbl_ennemis[i].Ay);
      }
      
      if((tbl_ennemis[i].y<-1) || (tbl_ennemis[i].y>1)) tbl_ennemis[i].Ay=tbl_ennemis[i].Ay*-1;
      
      // Si c'est un pacman
      if(tbl_ennemis[i].ennemis==1)
      {
        // tire en fonction du niveau
        if(((float)(rand()%120)/(tbl_ennemis[i].niveau+1))>((110-tbl_ennemis[i].niveau)/(tbl_ennemis[i].niveau+1)))
        {
          shoot_ennemis(i);
        }
      }
      
    }
  }
}


//=======================================================//
// Fonction qui affiche les ennemis                      //
//=======================================================//
void ennemis_affiche()
{
  int i; // Bcl
  
  for(i=0;i<Max_ennemis;i++)
  {
    // Que les ennemis en mouvements
    if(tbl_ennemis[i].mvt==1)
    {
      // Recherche le type d'ennemis
      if(tbl_ennemis[i].ennemis==0)
      {
        // Affiche le cône
        model_cone(tbl_ennemis[i].x,tbl_ennemis[i].y,tbl_ennemis[i].niveau);
      }
      else
      {
        // Affiche le pacman
        model_pacman(tbl_ennemis[i].x,tbl_ennemis[i].y,tbl_ennemis[i].niveau);
      }
    }
  }
}

#endif
