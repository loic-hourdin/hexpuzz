#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include "decoupage.h"

/**
 * \fn   	int rando (int n)
 * \brief   Fonction renvoyant un entier aléatoire
 * \details Fonction permettant d'obtenir un entier positif aléatoire, modulo n
 * \param   int n: l'entier déterminant le modulo utilisé pour calculer le nombre aléatoire
 * \return  Un entier compris entre 0 et n-1 est renvoyé
 */
int rando(int n)
{
	if(n==0){
		return(0);
	}
	static int preums = 1;
	if (preums) {preums = 0; srand(times(NULL));}
	return rand()%n;
}

/**
 * \fn       void ajoutPiece (liste *puzzle)
 * \brief    Cette fonction permet de ralonger la longueur de la liste
 * \details  On prends le quart en valeur entière de la taille de la liste et on choisit aléatoirement des pièces que l'on duplique et que l'on met en fin de liste
 * \param    liste *puzzle: Un pointeur vers une liste de pieces pour la modifier sans retourner de listes
 * \return   void
 */
void ajoutPiece (liste *puzzle)
{
	//On rajoute un quart de pièces de plus par rapport à la taille de la liste
	int n = 2, i;
	//On choisit une pièce aléatoirement et on l'a rajoute à la fin de la fonction
	while (n > 0)
	{
		i = rando(puzzle->nbPieces);
		puzzle->donnee[puzzle->nbPieces] = puzzle->donnee[i];
		puzzle->donnee[i].couleur = rando(COULEURMAX - COULEURMIN) + COULEURMIN;
		puzzle->nbPieces++;
		n--;
	}
}

/**
 * \fn       void desordreListe (liste *puzzle)
 * \brief    Cette fonction permet de mélanger l'ordre des pièces
 * \param    liste *puzzle: on travaille avec un pointeur pour modifier la liste directement sans avoir à la retourner
 * \return   void
 */
void desordreListe (liste *puzzle)
{
	//On recupère la taille de la liste
	int taille = puzzle->nbPieces, i,j;
	piece pieceI;

	while (taille > 0)
	{
		i = rando(puzzle->nbPieces);
		j = rando(puzzle->nbPieces);
		//On veut échanger deux pièces de positions différentes
		if (i == j){
			while (j == i)
			j = rando(puzzle->nbPieces);
		}

		//On échange les positions des deux pièces
		pieceI = puzzle->donnee[i];
		puzzle->donnee[i] = puzzle->donnee[j];
		puzzle->donnee[j] = pieceI;

		taille--;
	}
}

/**
 * \fn       piece decoupagePiece(Grid hextris, int nbHex, couple hex)
 * \brief    Permet de decouper une piece
 * \details  En prenant en entrée un couple de coordonnée avec la grille et la taille de la pièce, on créer d'abord une liste de voisins de l'hexagone en paramètre. Puis on choisit un voisin aléatoirement, on le retire de la liste des voisins et on met ses voisins dans la liste. On répète le processus jusqu'à obtenir une liste de la taille passée en paramètre.
 * \param    Grid hextris: grille sur laquelle on travaille, dans lequelle on decoupe
 * \param    int nbHex: la taille de la piece
 * \param    couple hex: l'hexagone qui sera la premiere dans la piece
 * \return   Une piece forme d'hexagone
 */
piece decoupagePiece(Grid hextris, int nbHex, couple hex)
{
	//A chaque hexagone que l'on rajoute dans la pièce, on mettra la valeur de l'hexagone dans la grille à 0
	hextris.carte[hex.x][hex.y] = 0;

	// hexPossibles nous permettra d'avoir une liste d'hexagones voisins des hexagones dans la pièce en construction, 
	// res est le résultat qu'on retournera, on l'initialise avec le premier hexagone dont les coordonnées sont en entrée
	piece hexPossibles, res;
	hexPossibles.nbHex = 0;
	res.nbHex = 1;
	res.Coord[0].x = hex.x;
	res.Coord[0].y = hex.y;

	int i,j,k;
	couple voisin;
	
	// Dans cette boucle on va mettre à jour les voisins du premier hexagone dans la pièce
	// on procède à 3 vérifications:
	//		- la première vérifie que les coordonnées des voisins sont dans les intervalles [0,Hauteur/Largeur]
	//		- la seconde permet de vérifier qu'on ne prends que les vrais voisins de l'hexagone (cf. layout odd-r)
	//		- la troisième vérifie que le voisin n'est pas un hexagone vide
	for (k=0;k<6;k++){

		voisin = correspondance(k, hex);
		i = voisin.x;
		j = voisin.y;
		if ((-1 < hex.x+i && hex.x+i < hextris.HAUTEUR) && (-1 < hex.y+j && hex.y+j < hextris.LARGEUR)) {
			if( hextris.carte[hex.x + i][hex.y + j] > 0 ) {
				hexPossibles.Coord[hexPossibles.nbHex].x = hex.x + i;
				hexPossibles.Coord[hexPossibles.nbHex].y = hex.y + j;
				hexPossibles.nbHex++;
			}
		}
	}

	//Si la liste de voisins est vide, alors on renvoie une pièce d'un hexagone
	if (hexPossibles.nbHex == 0)
		return res;

	//Dans cette boucle on va répéter les opérations ci-dessus en prenant aléatoirement un hexagone dans la liste des possibilités
	while (nbHex > 0)
	{
		//On choisit un hexagone, on le met dans la pièce, et on la retire de la liste des possibilités et de la carte (valeur mis à 0)
		k = rando(hexPossibles.nbHex);
		res.Coord[res.nbHex] = hexPossibles.Coord[k];
		for (i=k;i<hexPossibles.nbHex-1;i++)
			hexPossibles.Coord[i] = hexPossibles.Coord[i+1];

		hex.x = res.Coord[res.nbHex].x;
		hex.y = res.Coord[res.nbHex].y;
		hextris.carte[hex.x][hex.y] = 0;
		res.nbHex++;
		hexPossibles.nbHex--;

		if (hexPossibles.nbHex == 0)
			nbHex = 0;

		// on met a jour la liste des possibilités à jour en rajoutant les voisins du nouvel hexagone comme à l'initialisation
		else
		{
			for (k=0;k<6;k++){
				voisin = correspondance(k,hex);
				i = voisin.x;
				j = voisin.y;
				if ((-1 < hex.x+i && hex.x+i < hextris.HAUTEUR) && (-1 < hex.y+j && hex.y+j < hextris.LARGEUR)) {
					if( hextris.carte[hex.x + i][hex.y + j] > 0 ) {
						hexPossibles.Coord[hexPossibles.nbHex].x = hex.x + i;
						hexPossibles.Coord[hexPossibles.nbHex].y = hex.y + j;
						hexPossibles.nbHex++;
					}
				}
			}
			nbHex--;
		}
	}

	res.couleur = rando(COULEURMAX - COULEURMIN) + COULEURMIN;

	for (i=res.nbHex;i<TAILLEMAX;i++){
		res.Coord[i].x = 0;
		res.Coord[i].y = 0;
	}

	return res;
}

/**
 * \fn       liste decoupage(Grid Puzzle)
 * \brief    On prends une grille non vide en entrée et on la découpe pour avoir une liste de pièce qui y correspond
 * \details  On copie la grille car on en aura besoin pour l'affichage et le découpage d'une pièce nécessite que l'on mette a 0 les valeurs de la grille. Avec une double boucle for, on fait le tour de la grille et l'on découpe pièce par pièce grâce a la fonction précédente. Puis, on copie des pièces pour rallonger la longueur de la liste et on mélange l'ordre. Pour finir on initialise les cases restantes à une pièce d'un hexagone en 0,0 avec couleur nulle.
 * \param    Grid Puzzle: grille a partir duquelle on creer la liste de pieces
 * \return   La liste de pieces correspondant a la grille en entree 
 */
liste decoupage(Grid Puzzle)
{
	//On a besoin de dupliquer la grille car on l'utilisera pour l'affichage du jeu
	Grid hextris = copyGrid(Puzzle);
	couple hex;

	//On compte le nombre de grille non nul pour vérifier que la grille n'est pas vide
	int i,j,compteur = 0, nbHex;
	for (i=0;i<hextris.HAUTEUR;i++) {
		for (j=0;j<hextris.LARGEUR;j++) {
			if (hextris.carte[i][j] != 0)
				compteur++;
		}
	}

	//Si c'est le cas, on interrompt le programme
	if (compteur == 0) {
		perror("[decoupage] Grille vide en entrée");
		exit(EXIT_FAILURE);
	}

	//On initialise la liste de pièces
	liste res;
	res.nbPieces = 0;

	//On fait le tour de la grille et on decoupe une pièce que l'on rajoute à la liste 
	for (i=0;i<hextris.HAUTEUR;i++) {
		for(j=0;j<hextris.LARGEUR;j++) {
			if (hextris.carte[i][j] != 0)
			{
				//La taille varie de 2 a 5
				nbHex = rando(hexMax - hexMin) + hexMax-1;
				hex.x = i;
				hex.y = j;
				res.donnee[res.nbPieces] = decoupagePiece(hextris, nbHex, hex);
				res.nbPieces++;
			}
		}
	}


	freeGrid(hextris);

	ajoutPiece(&res);
	desordreListe(&res);

	piece Nulle;
	for (i=0;i<TAILLEMAX;i++){
		Nulle.Coord[i].x = 0;
		Nulle.Coord[i].y = 0;
		Nulle.couleur = 0;
		Nulle.nbHex = 0;
	}

	for (i=res.nbPieces;i<TAILLEMAX*3;i++){
		res.donnee[i] = Nulle;
	}

	return res;
}