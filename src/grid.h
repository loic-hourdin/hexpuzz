#ifndef GRID
#define GRID


typedef struct {
	int x;
	int y;
} couple;

enum {HAUT_GAUCHE, HAUT_DROITE, GAUCHE, DROITE, BAS_GAUCHE, BAS_DROITE};

typedef struct {
	int LARGEUR;
	int HAUTEUR;
	int **carte;
} Grid;

couple correspondance (int i, couple hex);
Grid creatGrid (int x, int y);
Grid creatGridInit1 (int x, int y);
Grid copyGrid (Grid hextris);
Grid grilleHexagone (int cote);
Grid grilleTriangle(int cote);
Grid grilleTriangleInverse(int cote);
void freeGrid (Grid hextris);

#endif