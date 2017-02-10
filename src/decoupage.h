#ifndef DECOUPAGE
#define DECOUPAGE
#include "grid.h"
#include "image.h"

// TAILLEMAX rendra la manipulation des pièces (tableau de coordonnées) plus flexible, tant que sa taille réelle est inférieur à celle-ci
#define TAILLEMAX 200

// Servira à attribuer des couleurs
#define COULEURMIN 2
#define COULEURMAX 9



typedef struct {
	couple Coord[TAILLEMAX];
	int nbHex;
	int couleur;
} piece;

typedef struct {
	piece donnee[TAILLEMAX*3];
	int nbPieces;
} liste;


int rando(int n);
void ajoutPiece (liste *puzzle);
void desordreListe (liste *puzzle);
piece decoupagePiece(Grid hextris, int taillePiece, couple hex);
liste decoupage(Grid hextris);


#endif