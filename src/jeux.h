#ifndef JEU
#define JEU

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include <errno.h>
#include "image.h"
#include "decoupage.h"
#include "grid.h"
#include "newgame.h"
#include "option.h"


typedef struct maillon *Listecoup;
struct maillon
{
	int x;
	int y;
	int piecemv;
	int pospiece;
	Listecoup suivant;
};


int taillegridex;
int taillegridey;
int lol;



int jeux ();
void affichegrid( Grid grid, int x, int y);
void chargebackjeu();
void affichepiece(piece piece,int x,int y);
Grid test1(Grid grid,liste l);// a suprimer fonction de test
int testpiece(piece piece,int x,int y);
int testpiecesurgrille(piece piece,Grid car,int xpiece,int ypiece,int xgrid,int ygrid,int deplacementx, int  deplacementy, int pospiece,Listecoup* l);
int undo(Listecoup* lpiececoup, Grid carte,liste llpiece);
Listecoup cons (Listecoup l, int x, int y, int pospiece);
Listecoup retour (Listecoup l);
int testgridwin(Grid map);

#endif
