#ifndef SOLVEUR
#define SOLVEUR

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "jeux.h"
#include "image.h"

int stack();
void printGrid(Grid hextris);
int poserLaPiece(piece piece,Grid car,int x,int y, int pospiece, Listecoup *l);
int solveur(Grid hextris, liste puzzle, Listecoup *soluce);
Listecoup copie (Listecoup l, Listecoup l1);
Listecoup lancement (Grid hextris, liste puzzle);

#endif