//=======================================================//
// Ce fichier est le ficier principale avec le WINAPI et //
// et les fonctions de base pour OpenGL                  //
//=======================================================//

#include <stdio.h>
#include <stdlib.h>
#include "main.h"


//=======================================================//
// Déclaration des fonctions du main.c                   //
//=======================================================//
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


//=======================================================//
// Fonction princiaple                                   //
//=======================================================//
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
  int i;
  WNDCLASS wc;
  HWND hWnd;
  HDC hDC;
  HGLRC hRC;        
  MSG msg;
  BOOL bQuit = FALSE;
  time_t t;  // Pour enregistrer l'heure
  
  time(&t);  // Enregistre l'heure
  srand(&t); // Initialise le générateur aléatoire

  // Prépare la fenêtre windows
  wc.style = CS_OWNDC;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = "GLSample";
  RegisterClass (&wc);

  // Crée la fenêtre windows
  hWnd = CreateWindow (
    "GLSample", "OpenGL Sample", 
    WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
    0, 0, Xmax, Ymax,
    NULL, NULL, hInstance, NULL);

  // Ouvre OpenGL
  EnableOpenGL (hWnd, &hDC, &hRC);

  // Initialise le jeu
  init_jeu(tbl_etoile);

  // Boucle du programme
  while ((!bQuit) && (gameover<250))
  {
    // Analyse les messages
    if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
    {
      // Si c'est un message pour fermer l'application
      if (msg.message == WM_QUIT) bQuit = TRUE;
      else
      {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
      }
    }
    else
    {
      // LE JEU
      fct_jeu(hDC);
    }
  }
  
  for(i=0;i<5;i++) printf("\a");

  DisableOpenGL (hWnd, hDC, hRC); //Ferme OpenGL proprement
  DestroyWindow (hWnd);           // Ferme la fenêtre proprement
  return msg.wParam;              // Fin du programme
}


//=======================================================//
// Ouvre OpenGL                                          //
//=======================================================//
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
  PIXELFORMATDESCRIPTOR pfd;
  int iFormat;

  // Obtient le DC
  *hDC = GetDC (hWnd);

  // Initialise le format de pixels
  ZeroMemory (&pfd, sizeof (pfd));
  pfd.nSize = sizeof (pfd);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
    PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
  pfd.iPixelType = PFD_TYPE_RGBA;
  pfd.cColorBits = 24;
  pfd.cDepthBits = 16;
  pfd.iLayerType = PFD_MAIN_PLANE;
  iFormat = ChoosePixelFormat (*hDC, &pfd);
  SetPixelFormat (*hDC, iFormat, &pfd);

  // crée le rendu
  *hRC = wglCreateContext( *hDC );
  wglMakeCurrent( *hDC, *hRC );
}


//=======================================================//
// Ferme OpenGL                                          //
//=======================================================//
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
