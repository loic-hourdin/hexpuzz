#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include "grid.h"


/**
 * \fn       couple correspondance(int i, couple coord)
 * \brief    Cette fonction permet de recuperer les coordonnées relatives d'une voisin au choix pa rapport au couple en entrée
 * \param    int i: Allant de 0 à 5, cette entier correspond au voisin aue l'on veut obtenir, voir enum dans grid.h
 * \param    couple coord: Hexagone auquel on cherche le voisin, on en a besoin en entree pour choisir le bon voisin
 * \return   Il s'agit des coordonnees relatives a l'hexagone en entree
 */
couple correspondance(int i, couple coord)
{
	couple res;
	if (i == HAUT_GAUCHE){
		if (coord.x%2 == 0)
			res.y = -1;
		else
			res.y = 0;
		res.x = -1;
	}

	else if (i == HAUT_DROITE){
		if (coord.x%2 == 0)
			res.y = 0;
		else
			res.y = +1;
		res.x = -1;

	}

	else if (i == GAUCHE){
		//Voisin à gauche
		res.y = -1;
		res.x = 0;
	}
	else if (i == DROITE){
		//Voisin à droite
		res.y = 1;
		res.x = 0;
	}
	else if (i == BAS_GAUCHE){
			if (coord.x%2 == 0)
				res.y = -1;
			else
				res.y = 0;
		res.x = 1;
	}

	else if (i == BAS_DROITE){
		if (coord.x%2 == 0)
			res.y = 0;
		else
			res.y = 1;
		res.x = 1;
	}
	
	else
		exit(EXIT_FAILURE);

	return res;
}

/**
 * \fn       Grid creatGrid (int x, int y)
 * \brief    On cree une grille dont les valeurs sont initialisees a 0
 * \param    int x: la hauteur de la grille
 * \param    int y: la largeur de la grille
 * \return   Une grille de taille x * y dont les valeurs sont initalisees a 0
 */
Grid creatGrid (int x, int y)
{
	Grid res;
	res.HAUTEUR = x;
	res.LARGEUR = y;
	res.carte = malloc(x*sizeof(int*));
	int i,j;
	for (i=0;i<x;i++){
		res.carte[i] = malloc(y*sizeof(int));
		for (j=0;j<y;j++)
			res.carte[i][j] = 0;
	}
	return res;
}

/**
 * \fn       Grid creatGridInit1 (int x, int y)
 * \brief    Il s'agit de la meme fonction qu'avant avec les valeurs initialisees a 1
 * \param    int x: la hauteur de la grille
 * \param    int y: la largeur de la grille
 * \return   Une grille de taille x * y dont les valeurs sont initalisees a 1
 */
Grid creatGridInit1 (int x, int y)
{
	Grid res;
	res.HAUTEUR = x;
	res.LARGEUR = y;
	res.carte = malloc(x*sizeof(int*));
	int i,j;
	for (i=0;i<x;i++){
		res.carte[i] = malloc(y*sizeof(int));
		for (j=0;j<y;j++)
			res.carte[i][j] = 1;
	}
	return res;
}

/**
 * \fn       Grid copyGrid (Grid hextris)
 * \brief    Creer une nouvelle grille en copiant celle en entree
 * \param    Grid hextris: la grille que l'on souhaite copier
 * \return   Une nouvelle grille identique a la precedente
 */
Grid copyGrid (Grid hextris)
{
	Grid res = creatGrid(hextris.HAUTEUR, hextris.LARGEUR);
	int i,j;
	for (i=0;i<res.HAUTEUR;i++)
		for (j=0;j<res.LARGEUR;j++)
			res.carte[i][j] = hextris.carte[i][j];
	return res;
}

/**
 * \fn       Grid grilleHexagone (int cote)
 * \brief    On creer une grille dont les hexagones de valeurs a 1 donne une hexagone
 * \details  On creer une grille initalise a 1. On va ensuite prendre les triangles dans chaque coin de l'hexagone et mettre les valeurs a 0 de facon a obtenir l'hexagone de 1. Cependant, si en entree on a un cote de longueur pair, l'hexagone ne sera pas regulier, avec deux cotes opposees de longeur cote-1.
 * \param    int cote: la longueur des cotes de l'hexagone souhaitee
 * \return   Une grille avec une forme hexagonale en son interieur
 */
Grid grilleHexagone (int cote)
{

	int largeur = 2 * cote - 1;
	Grid res = creatGridInit1(largeur,largeur);
	couple voisin, hex;

	//On va mettre des 0 dans le "triangle" en haut à gauche
	//Il s'agit de la case par laquelle on commence, la premiere case a cote de l'hexagone
	hex.y = cote/2 -1;
	hex.x = 0;
	int k = hex.y;
	while (k > -1)
	{
		//On met a 0 la case de la carte
		res.carte[hex.x][hex.y] = 0;
		//Si la prochaine case sor de la grille, on repart de k-1 et de la ligne 0
		if (hex.y + correspondance(BAS_GAUCHE,hex).y < 0){
			hex.y = k-1;
			hex.x = 0;
			k--;
		}

		//Si on ne sort pas encore, on prend le voisin en bas a gauche de la ou l'on se trouve
		else {
			voisin = correspondance(BAS_GAUCHE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	//Idem dans le "triangle" en bas à gauche
	//Le principe dans la boucle while est exactement le meme, sauf pour les valeurs a l'initialisation
	hex.y = cote/2 - 1;
	hex.x = largeur-1;
	k = hex.y;
	while (k > -1)
	{
		res.carte[hex.x][hex.y] = 0;
		if (hex.y + correspondance(HAUT_GAUCHE,hex).y < 0){
			hex.y = k-1;
			hex.x = largeur-1;
			k--;
		}

		else {
			voisin = correspondance(HAUT_GAUCHE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	//Idem dans le "triangle" en haut à droite
	//Le principe dans la boucle while est exactement le meme, sauf pour les valeurs a l'initialisation
	hex.y = largeur - cote/2;
	hex.x = 0;
	k = hex.y;
	while (k < largeur)
	{
		res.carte[hex.x][hex.y] = 0;
		if (hex.y + correspondance(BAS_DROITE,hex).y == largeur){
			hex.y = k+1;
			hex.x = 0;
			k++;
		}

		else {
			voisin = correspondance(BAS_DROITE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	//Idem dans le "triangle" en bas à droite
	//Le principe dans la boucle while est exactement le meme, sauf pour les valeurs a l'initialisation
	hex.y = largeur - cote/2;
	hex.x = largeur - 1;
	k = hex.y;
	while (k < largeur)
	{
		res.carte[hex.x][hex.y] = 0;
		if (hex.y + correspondance(HAUT_DROITE,hex).x == largeur){
			hex.y = k+1;
			hex.x = largeur - 1;
			k++;
		}

		else {
			voisin = correspondance(HAUT_DROITE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	return res;
}

/**
 * \fn       Grid grilleTriangle(int cote)
 * \brief    Cette fonction creera une grille avec une forme de triangle
 * \details  On itinalise une grille a 1 et on met a 0 les triangles sur les coins hauts de la grille, comme la fonction precedente
 * \param    int cote: La longeur souhaitee du triangle
 * \return   La grille avec des 1 qui forme un triangle
 */
Grid grilleTriangle(int cote) {
	Grid res = creatGridInit1(cote,cote);
	couple hex, voisin;
	int k;

	hex.y = cote/2 - 1;
	hex.x = 0;
	k = hex.y;
	//Le principe est analogue a la fonction precedente pour les deux boucles while
	while (k > -1)
	{
		res.carte[hex.x][hex.y] = 0;
		if (hex.y + correspondance(BAS_GAUCHE,hex).y < 0){
			hex.y = k-1;
			hex.x = 0;
			k--;
		}

		else {
			voisin = correspondance(BAS_GAUCHE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	hex.y = cote/2 + 1;
	hex.x = 0;
	k = hex.y;
	while (k < cote)
	{
		res.carte[hex.x][hex.y] = 0;
		if (hex.y + correspondance(BAS_DROITE,hex).y > cote-1){
			hex.y = k+1;
			hex.x = 0;
			k++;
		}

		else {
			voisin = correspondance(BAS_DROITE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	return res;
}

/**
 * \fn       Grid grilleTriangleInverse(int cote)
 * \brief    Cette fonction creera une grille avec une forme de triangle dans le sens inverse a la fonction precedente
 * \details  Idem mais avec les coins bas
 * \param    int cote: La longeur souhaitee du triangle
 * \return   La grille avec des 1 qui forme un triangle
 */
Grid grilleTriangleInverse(int cote) {
	Grid res = creatGridInit1(cote,cote);
	couple hex, voisin;
	int k;

	hex.y = cote/2 - 1;
	hex.x = cote - 1;
	k = hex.y;
	//Le principe est analogue a la fonction precedente pour les deux boucles while
	while (k > -1)
	{
		res.carte[hex.x][hex.y] = 0;
		if (hex.y + correspondance(HAUT_GAUCHE,hex).y < 0){
			hex.y = k-1;
			hex.x = cote - 1;
			k--;
		}

		else {
			voisin = correspondance(HAUT_GAUCHE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	hex.y = cote/2 + 1;
	hex.x = cote - 1;
	k = hex.y;
	while (k < cote)
	{
		res.carte[hex.x][hex.y] = 0;		
		if (hex.y + correspondance(HAUT_DROITE,hex).y > cote-1){
			hex.y = k+1;
			hex.x = cote - 1;
			k++;
		}

		else {
			voisin = correspondance(HAUT_DROITE,hex);
			hex.x += voisin.x;
			hex.y += voisin.y;
		}
	}

	return res;
}

/**
 * \fn       void freeGrid (Grid hextris)
 * \brief    Cette focntion desalloue l'espace allouee par la composante carte de la grille en entree
 * \param    Grid hextris: la grille que l'on souhaite detruire
 */
void freeGrid (Grid hextris)
{
	int i;
	for (i=0;i<hextris.HAUTEUR;i++)
		free(hextris.carte[i]);
	free(hextris.carte);
}