#include "solveur.h"


/*
	TATATATATATATATATATATATATATA TAAAAAAAAAAAAAAAAAAAAAAA
	Solveur 1.0 qui peut resoudre des puzzle, mais il ne fonctionne pas tout le temps et prend très longtemps a resoudre.
	Donc y a encore de l'optimisation a faire.
	Source d'erreur possible: A la fin de la recherche, on a deux fois la même piece dans le selecteur
	Ordre d'idée: Pour une grille de taille 4*4 avec 9 pieces, taille allant de 3 à 1, il faut 31182 appels récursives
*/

/**
 * \fn       int stack()
 * \brief    Permet de retirer la limite sur la quantité de mémoire que l'on peut allouer
 * \details  La variable static appel permet de voir si on a déjà lancer la commande execlp, puisqu'elle n'a besoin d'être lancer plus de 2 fois.
 			 On peut aussi voir si l'appel precédent avais réussi ou pas.
 * \return   Renvoie TRUE(1) si la commande a bien été lancer ou déjà été lancer, FALSE(0) sinon
 */
int stack()
{
	static int appel = 1;
	int res = 0;
	if (appel) {
		int ret = execlp("/", "ulimit -s unlimited", NULL);
		if (ret == -1) {
			perror("[Error: ps] execlp");
		}
		else
			res = 1;
			appel = 0;
		}
	else
		res = 1;
	return res;
}


int nbsolveur = 0;
//extern int p1,p2,p3, positionlistepiece, piecemv;

/**
 * \fn       void printGrid(Grid hextris)
 * \brief    Permet d'afficher une grille sur le terminal
 * \param    Grid hextris: la grille a afficher
 */
void printGrid(Grid hextris)
{
	int i,j;
	//printf("Figure\n");
	for (i=0;i<hextris.HAUTEUR;i++){
		if (i%2 == 1)
			//printf(" ");
		for(j=0;j<hextris.LARGEUR;j++){
			//printf("%2d",hextris.carte[i][j]);
		}
		//printf("\n");
	}
}


/**
 * \fn       int poserLaPiece(piece piece,Grid car,int x,int y, int pospiece, Listecoup *l)
 * \brief    cf testpiecesurgrille: le fonctionnement est le même
 * \param    piece piece: la piece que l'on souhaite voir si 'lon peut poser, si c'est le cas, on la pose
 * \param    Grid car: la grille sur laquelle on travaille
 * \param    int x: abscisse du premier hex de la piece sur la grille 
 * \param    int y: ordonnée du premier hex de la piece sur la grille 
 * \param    int pospiece quelle piece on deplace p1 p2 ou p3
 * \param    Listecoup* l la liste de coups joués
 * \return   Renvoie TRUE(1) si la pièce peut être posée effectivement, FALSE(0) sinon.
 */
int poserLaPiece(piece piece,Grid car,int x,int y, int pospiece, Listecoup *l){
	////printf("	x=%d  y=%d\n",x,y);
	int xx=piece.Coord[0].x;
	int yy=piece.Coord[0].y;
	int i;
	int qs,bb;
	for (i=0;i<piece.nbHex;i++){
		qs=piece.Coord[i].y-yy+x-((xx%2)*((piece.Coord[i].x-xx+10000)%2))+((y%2)*((piece.Coord[i].x-xx+10000)%2));
		bb=piece.Coord[i].x-xx+y;
		if(!(bb>=0 && bb<car.HAUTEUR && qs>=0 && qs<car.LARGEUR && car.carte[bb][qs]==1)){
			////printf("	fail pose\n");
			return(0);
		}
	}
	for (i=0;i<piece.nbHex;i++){
		qs=piece.Coord[i].y-yy+x-((xx%2)*((piece.Coord[i].x-xx+10000)%2))+((y%2)*((piece.Coord[i].x-xx+10000)%2));
		bb=piece.Coord[i].x-xx+y;
		if((bb>=0 && bb<car.HAUTEUR && qs>=0 && qs<car.LARGEUR && car.carte[bb][qs]==1)){
			car.carte[bb][qs]=piece.couleur;
		}
	}
	//printf("%d,%d\n",x,y);
	//printf("pospiece=%d\n", pospiece);
	*l = cons(*l, x, y, pospiece);
	////printf("pose success\n");
	return(1);
}

/**
 * \fn       int solveur(Grid hextris, liste puzzle, Listecoup soluce)
 * \brief    Fonction recursive pour résoudre le puzzle
 * \details  Avec une triple boucle for (on choisit le selecteur, l'abscisse et l'ordonnée), on essaie de poser la piece, si l'on peut, boucle récursive.
 			 Si en parcourant tout le selecteur et la grille on ne peut pas poser la piece, on appuie sur undo (cf jeux.c) et on continue.
 * \param    Grid hextris: grille sur laquelle on travaille, ou l'on va poser les pieces
 * \param    liste puzzle: liste de pieces associé à la grille que l'on va poser
 * \param    Listecoup soluce: liste de coups que l'on met a jour, qui servira de soluce
 * \return   Renvoie TRUE(1) si on trouve une solution, FALSE(0) sinon
 */
int solveur(Grid hextris, liste puzzle, Listecoup *soluce)
{
	
	nbsolveur++;
	printf("solveur tourne No d'appel: %d\n", nbsolveur);
	//printGrid(hextris);
	short i,j,k,select;
	////printf("Piece dans SELECTEUR %d %d %d\n",p1,p2,p3);

	for (k=1;k<4;k++)
	{
		////printf("%d\n",k);
		if (k == 1)
			select = p1;
		else if (k == 2)
			select = p2;
		else if (k == 3)
			select = p3;
		piecemv = k;
		////printf("SOLVEUR Select: %d\n",select);
		if (positionlistepiece < puzzle.nbPieces+1)
		{
			for (i=0;i<hextris.HAUTEUR;i++){
				for (j=0;j<hextris.LARGEUR;j++){
					if (poserLaPiece(puzzle.donnee[select],hextris,j,i,select,soluce))
					{
						//printf("Piece nb %d\n", positionlistepiece);
						//printf("Piece dans SELECTEUR %d %d %d  piecemv=%d\n",p1,p2,p3,piecemv);

						if (piecemv==1){
							p1 = positionlistepiece;
							positionlistepiece++;
						}
						if (piecemv==2){
							p2 = positionlistepiece;
							positionlistepiece++;
						}
						if (piecemv==3){
							p3 = positionlistepiece;
							positionlistepiece++;
						}
						//printf("Piece dans SELECTEUR modif %d %d %d\n",p1,p2,p3);
						if (testgridwin(hextris)){
							/*if (*soluce == NULL)
								//printf("On va renvoyer une liste nulle\n");
							else
								//printf("la soluce n'est pas nulle\n");*/
							return 1;
						}
						if (solveur(hextris,puzzle,soluce)){
							/*if ((*soluce) == NULL)
								//printf("On va renvoyer une liste nulle\n");
							else
								//printf("la soluce n'est pas nulle\n");*/
							return 1;	
						}
						////printf("piece retire\n");
						if((*soluce)==NULL){
							//printf("lololololo\n");
							return 0;
						}
						undo(soluce,hextris,puzzle);
						piecemv = k;
						//printf("SELECTEUR apres UNDO:%d %d %d\n",p1,p2,p3);
					}
				}
			}
		}
	}
	return 0;
}

/**
 * \fn       Listecoup copie (Listecoup l, Listecoup l1)
 * \brief    Copie le maillon d'une liste dans l'autre
 * \param    Listecoup l: liste de coup dont on ajoute un maillon
 * \param    Listecoup l1: liste de coup dont on copie le maillon
 * \return   Listecoup l mis a jour
 */
Listecoup copie (Listecoup l, Listecoup l1){
	Listecoup p;
	p = malloc(sizeof(struct maillon));
	p->x = l1->x;
	p->y = l1->y;
	p->piecemv = l1->piecemv;
	p->pospiece = l1->pospiece;
	p->suivant=l;
return(p);
}


/**
 * \fn       Listecoup lancement (Grid hextris, liste puzzle)
 * \brief    Fonction a lancer pour recuperer la liste de coup a faire pour gagner
 * \details  Vu le nombre de variables globales utilisées dans le jeu et le solveur, il faut enregister ces valeurs avant l'utilisation du solveur pour permettre l'utilisation du jeu et du solveur a la fois (d'ou le tableau TMP)
 			 On copie aussi la grille.
 			 A la fin, si on a une solution, comme listecoup une pile, on copie le continu de la solution dans une nouvelle variable Listecoup pour avoir l'ensemble de coups dans l'ordre dont on a besoin.
 			 Si on a pas de solution, on desalloue l'espace et on renvoie NULL;
 * \param    Grid hextris: grille sur laquelle on souhaite poser les pieces
 * \param    liste puzzle: les pieces que l'on veut poser
 * \return   Listecoup: Non-NULL si on aune solution, NULL s'il y en a pas
 */
Listecoup lancement (Grid hextris, liste puzzle)
{
	stack();
	nbsolveur=0;
	Listecoup solv = NULL;
	int TMP[5];
	TMP[0] = p1; TMP[1] = p2; TMP[2] = p3;
	TMP[3] = positionlistepiece; TMP[4] = piecemv;
	Grid hex = copyGrid(hextris);

	int res = solveur(hex,puzzle,&solv);
	//printf("Résultat recherche %d\n",res);

	p1 = TMP[0]; p2 = TMP[1]; p3 = TMP[2];
	positionlistepiece = TMP[3]; piecemv = TMP[4];
	printGrid(hex);
	freeGrid(hex);

	if (res == 1)
	{
		Listecoup soluce = NULL;
		while (solv != NULL){
			soluce = copie(soluce,solv);
			solv = retour(solv);
		}
		return soluce;
	}

	else 
		while(solv != NULL)
			solv = retour(solv);
		return NULL;
}