#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include <errno.h>
#include "image.h"
#include "option.h"
#include "decoupage.h"
#include "grid.h"
#include "newgame.h"
#include "menu.h"
#include "jeux.h"

int test_puttext();
int test_setrect();
int test_initimage();
int test_initbouton();
int test_libMusic();
int test_plusMusic();
int test_minusMusic();
int test_affbouton();
int test_testbouton();
int test_freebouton();

int test_jeux ();
int test_affichegrid ();
int test_chargebackjeu ();
int test_affichepiece();
int test_testpiece ();
int test_testpiecesurgrille ();
int test_undo();

void testimage(){
	int reussite=0;
	int b;
	printf("--------------------------------------------------------------------------------\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("|                         IMAGE TEST UNITAIRE                                  |\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n");
	printf("IMAGE:\n");
	printf("1-void puttext(SDL_Surface **surface, char *text, int size, int r, int g, int b);\n");
	printf("2-void setrect(SDL_Rect *rect, int x, int y, int w, int h);\n");
	printf("3-Image initimage(char* adresse,int w,int h);\n");
	printf("4-Bouton initbouton(int x, int y, int w, int h, char* text, int r, int v, int b);\n");
	printf("5-void affbouton(Bouton *b);\n");
	printf("6-int testbouton(Bouton b);\n");
	printf("7-void freebouton(Bouton b);\n");
	printf("8-void chargeMusic();\n");
	printf("9-void libMusic();\n");
	printf("10-void plusMusic ();\n");
	printf("11-void minusMusic ();\n");
	printf("0-tout tester;\n");
	printf("12-quitter\n");
	printf("\n");
	do {
		scanf("%d",&b);
	} while (b<0 && b>12);
	if(b==0 || b==1){
		reussite+=test_puttext();
	}
	if(b==0 || b==2){
		reussite+=test_setrect();
	}
	if(b==0 || b==3){
		reussite+=test_initimage();
	}
	if(b==0 || b==4){
		reussite+=test_initbouton();
	}
	if(b==0 || b==5){
		reussite+=test_affbouton();
	
	}
	if(b==0 || b==6){
		reussite+=test_testbouton();
	}
	if(b==0 || b==7){
		reussite+=test_freebouton();
	
	}

	if(b==0 || b==8){
		printf("Test de la fonction de chargement de la musique\n");
		if ( chargeMusic() ) {printf("Résultat : OK\n");
		reussite+=1;}
		else {printf("Résultat : ERREUR\n");}

	}

	if(b==0 || b==10){
		reussite+=test_plusMusic();
	}
	if(b==0 || b==11){
		reussite+=test_minusMusic();
	}

	if (reussite==11) {
		printf("--------------------------------------------------------------------------------\n");
		printf("|                         IMAGE OK                                             |\n");
		printf("--------------------------------------------------------------------------------\n");
	}
	else {
		printf("--------------------------------------------------------------------------------\n");
		printf("|                       IMAGE ERREUR                                           |\n");
		printf("--------------------------------------------------------------------------------\n");	
	}
}

int test_libMusic() {
	Mix_Music* song=NULL;
	printf("Chargement de la piste \"mex_hat_dance.mp3\" du fichier sound_samples\n");
	Mix_LoadMUS("sound_samples/mex_hat_dance.mp3");
	printf("La musique va maintenant démarrer, puis sera libérée.\n");
	printf("Si la musique est correctement libérée, elle s'arrêtera et \"Résultat : OK\" devra apparaître\n");
	printf("Démarrage\n");
	Mix_PlayMusic(song,1);
	printf("Arrêt\n");
	Mix_FreeMusic(song);
	if (!(Mix_PlayingMusic()) ) {
		printf("Résultat : OK\n");
		return 1;
	}
	else {
		printf("Résultat : ERREUR\n");
		return 0;
	}
}

int test_plusMusic() {
	int vol, temoin;
	printf("La fonction plusMusic utilise la fonction de SDL_Mixer \"Mix_VolumeMusic.\"");
	printf("Cette fonction change le volume du son et renvoie la valeur du réglage PRÉCÉDENT.\n");
	printf("Initialisez un volume compris entre 0 et 63 : ");
	scanf("%d",&vol);
	temoin=vol;
	printf("\nDémarrage de Mix_volumeMusic\n");
	Mix_VolumeMusic(vol);
	printf("On actualise désormais cette valeur à la valeur 64\n");
	if (Mix_VolumeMusic(64)==temoin) {
		printf("Résultat : OK\n");
		return 1;
	}
	else {
		printf("Résultat : ERREUR\n");
		return 0;
	}
}

int test_minusMusic() {
	int vol, temoin;
	printf("La fonction minusMusic utilise la fonction de SDL_Mixer \"Mix_VolumeMusic.\"");
	printf("Cette fonction change le volume du son et renvoie la valeur du réglage PRÉCÉDENT.\n");
	printf("Initialisez un volume compris entre 65 et 128 : ");
	scanf("%d",&vol);
	temoin=vol;
	printf("\nDémarrage de Mix_volumeMusic\n");
	Mix_VolumeMusic(vol);
	printf("On actualise désormais cette valeur à la valeur 64\n");
	if (Mix_VolumeMusic(64)==temoin) {
		printf("Résultat : OK\n");
		return 1;
	}
	else {
		printf("Résultat : ERREUR\n");
		return 0;
	}
}

void testmenu() {
	printf("--------------------------------------------------------------------------------\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("|                         MENU TEST UNITAIRE                                   |\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n");
	printf("La fonction int menu() est simialire à la fonction int jeux(), testée dans la section jeux\n");
	printf("La fonction void chargebackmenu() est similaire à void chargebackjeux(), testée dans la section jeux\n");

	
}

void testjeux() {
	int reussite=0;
	int b;
	printf("--------------------------------------------------------------------------------\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("|                         JEUX TEST UNITAIRE                                   |\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n");
	printf("JEUX:\n");
	printf("1-int jeux ();\n");
	printf("2-void affichegrid( Grid grid, int x, int y);\n");
	printf("3-void chargebackjeu();\n");
	printf("4-void affichepiece(piece piece,int x,int y);\n");
	printf("5-int testpiece(piece piece,int x,int y);\n");
	printf("6-int testpiecesurgrille(piece piece,Grid car,int xpiece,int ypiece,int xgrid,int ygrid,int deplacementx, int  deplacementy, int pospiece,Listecoup* l);\n");
	printf("7-int undo(Listecoup *listecoup,Grid carte);\n");
	printf("8-Listecoup cons (Listecoup l, int x, int y, int pospiece);\n");
	printf("9-Listecoup retour (Listecoup l);\n");
	printf("10-int testgridwin(Grid map);\n");
	printf("11-quitterint test_affichegrid ()\n");
	printf("0-tout tester;\n");
	printf("\n");
	do {
		scanf("%d",&b);
	} while (b<0 && b>11);

	if(b==0 || b==1){
		reussite+=test_jeux();
	}
	if(b==0 || b==2){
		reussite+=test_affichegrid();
	}
	if(b==0 || b==3){
		reussite+=test_chargebackjeu ();
	}
	if(b==0 || b==4){
		reussite+=test_affichepiece();
	}
	if(b==0 || b==5){
		reussite+=test_testpiece ();
	
	}
	if(b==0 || b==6){
		reussite+=test_testpiecesurgrille ();
	}
	if(b==0 || b==7){
		reussite+=test_undo();
	
	}

	
	

	printf("Travaille en cours \n");

	if (reussite) {
		printf("--------------------------------------------------------------------------------\n");
		printf("|                       JEUX OK                                                |\n");
		printf("--------------------------------------------------------------------------------\n");
	}
	else {
		printf("--------------------------------------------------------------------------------\n");
		printf("|                       JEUX ERREUR                                           |\n");
		printf("--------------------------------------------------------------------------------\n");	
	}
}

void testnewgame() {
	printf("--------------------------------------------------------------------------------\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("|                       NEWGAME TEST UNITAIRE                                  |\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n");


	printf("La fonction int newgame() est similaire à int jeux(), testée dans la section jeux\n");
	printf("La fonction void chargebacknewgame() est similaire à void chargebackjeux(), testée dans la section jeux\n");

}

void test_affchanson() {
	printf("Début du test de affchanson\n");
	SDL_Surface *tchanson, *screen;
	SDL_Rect rtmp;
	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	
	setrect(&rtmp, 645, 410, 0, 0);
	SDL_BlitSurface(tchanson, NULL, screen, &rtmp);
	puttext(&tchanson, "Nice Music", 30, 255, 255, 255);
	
	printf("Si Nice Music à été affiché, la fonction affchanson fonctionne correctement.\n");
	SDL_FreeSurface(tchanson);SDL_FreeSurface(screen);
}

void testoption() {
	int continuer=0;
	printf("--------------------------------------------------------------------------------\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("|                        OPTION TEST UNITAIRE                                  |\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n");
	printf("La seule fonction à tester est void affchanson(), les deux autres fonctions sont similaires à des fonctions testées dans la section jeux\n");
	printf("ATTENTION : Le test unitaire de cette fonction n'est pas encore totalement fonctionnel. Il est déconseillé de poursuivre. Continuer tout de même ? OUI=1, NON=0.\n");
	scanf("%d",&continuer);
	
	if (continuer) {
		test_affchanson();
	}
}

int testCorrespondance()
{
	int value = 0, test = 0;
	couple couple1, couple2, coupleTMP;
	printf("On va tester sur le couple 4.3 et ses voisins puis le couple 5.6\n");

	// Test sur le premier couple
	couple1.x = 4; couple1.y = 3;

	couple2.x = 3; couple2.y = 2;
	coupleTMP = correspondance(HAUT_GAUCHE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;
	
	couple2.x = 3; couple2.y = 3;
	coupleTMP = correspondance(HAUT_DROITE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	couple2.x = 4; couple2.y = 2;
	coupleTMP = correspondance(GAUCHE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	couple2.x = 4; couple2.y = 4;
	coupleTMP = correspondance(DROITE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	couple2.x = 5; couple2.y = 2;
	coupleTMP = correspondance(BAS_GAUCHE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;
	
	couple2.x = 5; couple2.y = 3;
	coupleTMP = correspondance(BAS_DROITE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	//Test sur le second couple
	couple1.x = 5; couple1.y = 6;

	couple2.x = 4; couple2.y = 6;
	coupleTMP = correspondance(HAUT_GAUCHE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;
	
	couple2.x = 4; couple2.y = 7;
	coupleTMP = correspondance(HAUT_DROITE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	couple2.x = 5; couple2.y = 5;
	coupleTMP = correspondance(GAUCHE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	couple2.x = 5; couple2.y = 7;
	coupleTMP = correspondance(DROITE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	couple2.x = 6; couple2.y = 6;
	coupleTMP = correspondance(BAS_GAUCHE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;
	
	couple2.x = 6; couple2.y = 7;
	coupleTMP = correspondance(BAS_DROITE,couple1);
	coupleTMP.x += couple1.x;
	coupleTMP.y += couple1.y;
	if (coupleTMP.x == couple2.x && coupleTMP.y == couple2.y)
		test ++;

	if (test == 12)
		value = 1;
	return value;
}

int testPiece()
{
	int val = 0,i,j,k, voisins = 0;
	couple hex1, hex2, hexTMP;
	hex1.x = 5;
	hex1.y = 7;
	Grid hextris = creatGridInit1(8,8);
	piece test = decoupagePiece(hextris,5,hex1);
	for (i=0;i<test.nbHex;i++){
		hex1 = test.Coord[i];
		for (j=i+1;j<test.nbHex;j++){
			hex2 = test.Coord[j];
			for (k=0;k<6;k++)
			{
				hexTMP = correspondance(i,hex1);
				hexTMP.x += hex1.x;
				hexTMP.y += hex1.y;
				if (hexTMP.x == hex2.x && hexTMP.y == hex2.y)
					voisins++;
			}
		}
	}
	if (voisins >= test.nbHex)
		val = 1;

	freeGrid(hextris);
	return val;
}

int compareGrid(Grid carte1,Grid carte2)
{
	int i,j;
	if (!(carte1.HAUTEUR == carte2.HAUTEUR && carte1.LARGEUR == carte2.LARGEUR))
		return 0;
	for (i=0;i<carte1.HAUTEUR;i++){
		for (j=0;j<carte1.LARGEUR;j++){
			if (carte1.carte[i][j] != carte2.carte[i][j])
				return 0;
		}
	}
	return 1;
}

int testDecoupage()
{
	hexMax = 5;
	hexMin = 2;
	Grid hextris1;
	int i,j,x,y;
	hextris1 = creatGridInit1(5,5);
	liste res = decoupage(hextris1);
	Grid hextris2 = creatGrid(hextris1.HAUTEUR,hextris1.LARGEUR);

	for (i=0;i<res.nbPieces;i++)
	{
		for (j=0;j<res.donnee[i].nbHex;j++){
			x = res.donnee[i].Coord[j].x;
			y = res.donnee[i].Coord[j].y;
			hextris2.carte[x][y] = 1;
		}
	}

	int val = compareGrid(hextris1,hextris2);
	freeGrid(hextris1);
	freeGrid(hextris2);

	return val;
}

void testdecoupage() {
	printf("--------------------------------------------------------------------------------\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("|                       DECOUPAGE TEST UNITAIRE                                |\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n");
	printf("Test de la fonction des voisins\n");
	if ( (testCorrespondance()) ) {
		printf("Résultat : OK\n");
	}
	else {
		printf("Résultat : ERREUR\n");
	}
	printf("Test de la fonction découper une pièce\n"); 
	if ( (testPiece()) ) {
		printf("Résultat : OK\n"/*,testPiece()/*/);
	}  // erreur a modifier
	else {
		printf("Résultat : ERREUR\n");
	}
	printf("Test de la fonction découper toute la grille\n");
	if ( (testDecoupage()) ) {
		printf("Résultat : OK\n");
	}
	else {
		printf("Résultat : ERREUR\n");
	}
}

int main() {
	printf("--------------------------------------------------------------------------------\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("|                         HEXTRIS TEST UNITAIRE                                |\n");
	printf("|                                                                              |\n");
	printf("|                                                                              |\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("\n\n");
	printf("MENU:\n");
	printf("1-image\n");
	printf("2-menu\n");
	printf("3-jeux\n");
	printf("4-newgame\n");
	printf("5-option\n");
	printf("6-grid\n");
	printf("7-decoupage\n");
	printf("8-\n");
	printf("0-tout tester\n");
	printf("9-quitter\n");
	printf("\n");
	int a;
	do {
		scanf("%d",&a);
	} while (a<0 && a>9);
	
	do {
		if(a==1) {
			testimage();
		}

		if (a==2) {
			testmenu();
		}

		if (a==3) {
			testjeux();
		}

		if (a==4) {
			testnewgame();
		}

		if (a==5) {
			testoption();
		}

		if (a==6) {
			printf("Rien à tester dans le fichier grid.c\n");
		}

		if (a==7) {
			testdecoupage();
		}

		if (a==0) {
			testimage();
			testmenu();
			testjeux();
			testnewgame();
			testoption();
			testdecoupage();
			return 1;
		}
		printf("\n\n");
		printf("MENU:\n");
		printf("1-image\n");
		printf("2-menu\n");
		printf("3-jeux\n");
		printf("4-newgame\n");
		printf("5-option\n");
		printf("6-grid\n");
		printf("7-decoupage\n");
		printf("8-\n");
		printf("0-tout tester\n");
		printf("9-quitter\n");
		printf("\n");
		scanf("%d",&a);
	} while(a!=9);
	
	return 1;
}

int test_puttext(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :void puttext(SDL_Surface **surface, char *text, int size, int r, int g, int b)\n");
	SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
    int continuer = 1;
    TTF_Init();
    SDL_Surface *testtexte;
    testtexte=NULL;
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_Event eve;
    setrect(&rtmp, 0, 0, 0, 0);
    puttext(&testtexte, "test de puttext", 60, 255, 0, 0);
    if(SDL_BlitSurface(testtexte, NULL, screen, &rtmp)==-1){
    	printf("--------------------------------------------------------------------------------\n");
		printf("|                    erreur puttext: erreur d'affichage                        |\n");
		printf("--------------------------------------------------------------------------------\n");
		SDL_FreeSurface(screen);SDL_FreeSurface(testtexte);
    	SDL_Quit(); // Arrêt de la SDL
		return(0);
    }
	
    while (continuer)
    {
    	
        SDL_WaitEvent(&eve);
        switch(eve.type){
            case SDL_QUIT:
         	   continuer = 0;
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(screen);SDL_FreeSurface(testtexte);
    SDL_Quit(); // Arrêt de la SDL
    printf("Si \"test de puttext\" s'est affiché, la fonction marche\n");
    return 1; // Fermeture du programme
}

int test_setrect(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :void setrect(SDL_Rect *rect, int x, int y, int w, int h)\n");
	printf("Fonction simple, inutile de tester.\n");
	return 1;
}

int test_initimage(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :Image initimage(char* adresse,int w,int h);\n");
	SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
    int continuer = 1;
    TTF_Init();
    Image test;
    screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    SDL_Event eve;
    test=initimage("BMP/icône-fleche->.png",38, 38);

    setrect(&rtmp, 0, 0, 0, 0);
    
    if(SDL_BlitSurface(test.image, NULL, screen, &rtmp)==-1){
    	printf("--------------------------------------------------------------------------------\n");
		printf("|                    erreur initimage: erreur d'affichage                        |\n");
		printf("--------------------------------------------------------------------------------\n");
		SDL_FreeSurface(screen);SDL_FreeSurface(test.image);
    	SDL_Quit(); // Arrêt de la SDL
		return(0);
    }
	
    while (continuer)
    {
    	
        SDL_WaitEvent(&eve);
        switch(eve.type){
            case SDL_QUIT:
         	   continuer = 0;
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(screen);SDL_FreeSurface(test.image);
    SDL_Quit(); // Arrêt de la SDL
    printf("si la flèche s'est affichée, la fonction marche\n");
    return 1; // Fermeture du programme
}

int test_initbouton(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :Bouton initbouton(int x, int y, int w, int h, char* text, int r, int v, int b);\n");

	if(!test_puttext())return(0);
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 0;
    }
	TTF_Init(); //taille écriture
 	screen = SDL_SetVideoMode(600, 600, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
    int continuer = 1;
    TTF_Init();
    Bouton test;
    SDL_Event eve;
    test=initbouton(100,100,200,100,"test",255, 255, 255);
    setrect(&rtmp, 0, 0, 0, 0);
    
    if(SDL_BlitSurface(test.im, NULL, screen, &rtmp)==-1){
    	perror("SDL_BlitSurface");
    	printf("--------------------------------------------------------------------------------\n");
		printf("|                    erreur initbouton: erreur d'affichage                     |\n");
		printf("--------------------------------------------------------------------------------\n");
		SDL_FreeSurface(screen);
		freebouton(test);
    	SDL_Quit(); // Arrêt de la SDL
		return(0);
    }
	
    while (continuer)
    {
    	
        SDL_WaitEvent(&eve);
        switch(eve.type){
            case SDL_QUIT:
         	   continuer = 0;
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(screen);freebouton(test);
    SDL_Quit(); // Arrêt de la SDL
    printf("si le bouton avec écrit test s'est affiché, la fonction marche\n");
    return 1; // Fermeture du programme
}

int test_affbouton(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :int testbouton(Bouton b)\n");

	if(!test_puttext())return(0);
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 0;
    }
	TTF_Init(); //taille écriture
 	screen = SDL_SetVideoMode(600, 600, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
    int continuer = 1;
    TTF_Init();
    Bouton test;
    SDL_Event eve;
    test=initbouton(100,100,200,100,"test",255, 255, 255);
    setrect(&rtmp, 0, 0, 0, 0);
    
    
	
    while (continuer)
    {
    	
        SDL_WaitEvent(&eve);
        affbouton(&test);
        switch(eve.type){
            case SDL_QUIT:
         	   continuer = 0;
        }
        SDL_Flip(screen);
    }
    SDL_FreeSurface(screen);freebouton(test);
    SDL_Quit(); // Arrêt de la SDL
    printf("Si le bouton avec écrit test s'est affiché la fonction marche\n");
    return 1; // Fermeture du programme
}

int test_testbouton(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :int testbouton(Bouton b)\n");

	Bouton test;

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 0;
    }
	TTF_Init(); //taille écriture
 	screen = SDL_SetVideoMode(600, 600, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
    TTF_Init();

	test=initbouton(0,0,100,100,"test",255,255,255);
	souris.x=10;
	souris.y=10;
	if(!testbouton(test)){
		printf("--------------------------------------------------------------------------------\n");
		printf("|      erreur testbouton: erreur curseur sur bouton ne marche pas              |\n");
		printf("--------------------------------------------------------------------------------\n");
		return(0);
	}
	souris.x=1000;
	souris.y=10;
	if(testbouton(test)){
		printf("--------------------------------------------------------------------------------\n");
		printf("|  erreur testbouton: erreur curseur non sur bouton détecter comme sur bouton  |\n");
		printf("--------------------------------------------------------------------------------\n");
		return(0);
	}
	freebouton(test);
	SDL_FreeSurface(screen);
	SDL_Quit();
	
	printf("testbouton marche\n");
    return 1; // Fermeture du programme
}


int test_freebouton(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :void freebouton(Bouton b);\n");
	Bouton test;
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 0;
    }
	TTF_Init(); //taille écriture
 	screen = SDL_SetVideoMode(600, 600, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
    TTF_Init();

	test=initbouton(0,0,100,100,"test",255,255,255);
	printf("Si une erreur de segmentation apparaît, la fonction ne marche pas");
	freebouton(test);
	SDL_FreeSurface(screen);
	SDL_Quit();
	
	printf("freebouton marche\n");
    return 1; // Fermeture du programme
}



int test_jeux (){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :int jeux ();\n");
	
	printf("Lancer le jeu pour tester cette fonction\n");
    return 1; // Fermeture du programme
}
Image hexagone;


SDL_Surface *fondavecgrille;
SDL_Rect spritehex[11];

int test_affichegrid (){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :void affichegrid( Grid grid, int x, int y);\n");
	Grid carte;
	int i;

	for(i=0;i<10;i++){
		setrect(&spritehex[i+1],i*40,0,40,40);
	}
	hexagone=initimage("BMP/hexagonecolor.png",400, 40);
	for(i=0;i<10;i++){
		setrect(&spritehex[i+1],i*40,0,40,40);
	}
	setrect(&spritehex[0],0,0,0,0);
	hexagone.sprite=spritehex;


	printf("Lancer le jeu pour tester cette fonction\n");

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 0;
    }
	TTF_Init(); //taille écriture
 	fondavecgrille = SDL_SetVideoMode(600, 600, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	colorkey = SDL_MapRGB(fondavecgrille->format, 255, 255, 255);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
    int continuer = 1;
    TTF_Init();
    carte=creatGridInit1(8,8);
    SDL_FillRect(fondavecgrille, NULL, SDL_MapRGB(fondavecgrille->format, 17, 206, 112));
    
    carte.carte[2][2]=3;
    carte.carte[3][2]=1;
    carte.carte[4][2]=2;
    carte.carte[3][3]=2;
    carte.carte[4][4]=5;
    carte.carte[5][7]=1;
    carte.carte[5][8]=0;
    affichegrid(carte, 300 , 300);
    SDL_Event eve;
    

    while (continuer)
    {
        SDL_WaitEvent(&eve);
        switch(eve.type){
            case SDL_QUIT:
         	   continuer = 0;
        }
        SDL_Flip(fondavecgrille);
    }

    SDL_FreeSurface(fondavecgrille);SDL_FreeSurface(hexagone.image);
	SDL_Quit();

	printf("Si la grille s'affiche avec quelques piècs, la fonction marche\n");
    return 1; // Fermeture du programme
}

int test_chargebackjeu (){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :void chargebackjeu();\n");
	
	printf("fonction qui charge les images du jeux\n");
    return 1; // Fermeture du programme
}


int test_affichepiece(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :void affichepiece(piece piece,int x,int y);\n");
	
	printf("Fonction qui affiche une pièce\n");

	piece piece;
	piece.nbHex=5;
	piece.couleur=5;
	piece.Coord[0].x=0;
	piece.Coord[0].y=0;
	piece.Coord[1].x=1;
	piece.Coord[1].y=0;
	piece.Coord[2].x=1;
	piece.Coord[2].y=1;
	piece.Coord[3].x=2;
	piece.Coord[3].y=0;
	piece.Coord[4].x=3;
	piece.Coord[4].y=0;
	piece.Coord[5].x=0;
	piece.Coord[5].y=1;

	int i;

	for(i=0;i<10;i++){
		setrect(&spritehex[i+1],i*40,0,40,40);
	}
	hexagone=initimage("BMP/hexagonecolor.png",400, 40);
	for(i=0;i<10;i++){
		setrect(&spritehex[i+1],i*40,0,40,40);
	}
	setrect(&spritehex[0],0,0,0,0);
	hexagone.sprite=spritehex;



	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 0;
    }
	TTF_Init(); //taille écriture
 	screen = SDL_SetVideoMode(600, 600, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
    int continuer = 1;
    TTF_Init();
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 17, 206, 112));
    affichepiece(piece, 300 , 300);
    SDL_Event eve;
    

    while (continuer)
    {
        SDL_WaitEvent(&eve);
        switch(eve.type){
            case SDL_QUIT:
         	   continuer = 0;
        }
        SDL_Flip(screen);
    }

    SDL_FreeSurface(screen);SDL_FreeSurface(hexagone.image);
	SDL_Quit();

	printf("Si la piece s'affiche avec quelques pièces, la fonction marche\n");
    return 1; // Fermeture du programme
}


int test_testpiece (){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :int testpiece(piece piece,int x,int y);\n");
	
	printf("fonction qui teste si la souris est sur la pièce à la position x y \n");

	piece piece;
	piece.nbHex=5;
	piece.couleur=5;
	piece.Coord[0].x=0;
	piece.Coord[0].y=0;
	piece.Coord[1].x=1;
	piece.Coord[1].y=0;
	piece.Coord[2].x=1;
	piece.Coord[2].y=1;
	piece.Coord[3].x=2;
	piece.Coord[3].y=0;
	piece.Coord[4].x=3;
	piece.Coord[4].y=0;
	piece.Coord[5].x=0;
	piece.Coord[5].y=1;

	int test=1;

	souris.x=210;
	souris.y=210;
	if (!testpiece(piece,200,200))
	{
		test=0;
		printf("--------------------------------------------------------------------------------\n");
		printf("|  erreur testpiece: erreur curseur non détecté comme étant sur la pièce       |\n");
		printf("--------------------------------------------------------------------------------\n");

	}
	if (testpiece(piece,0,0))
	{
		test=0;
		printf("--------------------------------------------------------------------------------\n");
		printf(" erreur testpiece: erreur curseur hors de la piece détecté sur la piece        |\n");
		printf("--------------------------------------------------------------------------------\n");

	}


    return test; // Fermeture du programme
}

int test_testpiecesurgrille (){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :int testpiecesurgrille(piece piece,Grid car,int xpiece,int ypiece,int xgrid,int ygrid,int deplacementx, int  deplacementy, int pospiece,Listecoup* l);\n");
	
	Grid carte;



	piece piece;
	piece.nbHex=5;
	piece.couleur=5;
	piece.Coord[0].x=0;
	piece.Coord[0].y=0;
	piece.Coord[1].x=1;
	piece.Coord[1].y=0;
	piece.Coord[2].x=1;
	piece.Coord[2].y=1;
	piece.Coord[3].x=2;
	piece.Coord[3].y=0;
	piece.Coord[4].x=3;
	piece.Coord[4].y=0;
	piece.Coord[5].x=0;
	piece.Coord[5].y=1;

	carte=creatGridInit1(8,8);

	int test=1;
	Listecoup l=NULL;

	if(!testpiecesurgrille(piece,carte,0,0,0,0,0,0,1,&l)){
		test=0;
		printf("-----------------------------------------------------------------------------------------------\n");
		printf("|  erreur testpiecesurgrille: erreur pièce pouvant être placée est détectée comme implaçable  |\n");
		printf("-----------------------------------------------------------------------------------------------\n");
	}

	if(testpiecesurgrille(piece,carte,2000000,30000,0,0,0,0,1,&l)){
		test=0;
		printf("-----------------------------------------------------------------------------------------------\n");
		printf("|  erreur testpiecesurgrille: erreur pièce ne pouvant pas être placée est placée sur la grille|\n");
		printf("-----------------------------------------------------------------------------------------------\n");
	}
    return test; // Fermeture du programme
}

int p1,p2,p3,positionlistepiece;
int test_undo(){
	printf("----------------------------------------------------------------------------------------------------------------------------------\n");
	printf("TEST :int undo(Listecoup *listecoup,Grid carte,liste llpiece);\n");
	p1=1;
	p2=2;
	p3=3;
	positionlistepiece=4;
	Listecoup l=NULL;


	piece piece;
	piece.nbHex=5;
	piece.couleur=5;
	piece.Coord[0].x=0;
	piece.Coord[0].y=0;
	piece.Coord[1].x=1;
	piece.Coord[1].y=0;
	piece.Coord[2].x=1;
	piece.Coord[2].y=1;
	piece.Coord[3].x=2;
	piece.Coord[3].y=0;
	piece.Coord[4].x=3;
	piece.Coord[4].y=0;
	piece.Coord[5].x=0;
	piece.Coord[5].y=1;

	liste llpiece;
	llpiece.nbPieces=1;
	llpiece.donnee[0]=piece;

	Grid carte;
	carte=creatGridInit1(8,8);
	testpiecesurgrille(piece,carte,0,0,0,0,0,0,1,&l);

	int test=1;

	if(!undo(&l,carte,llpiece)){
		test=0;
		printf("-----------------------------------------------------------------------------------------------\n");
		printf("|  erreur undo: incapable de défaire le dernier coup, alors qu'il devrait pouvoir             |\n");
		printf("-----------------------------------------------------------------------------------------------\n");
	}

	if(undo(&l,carte,llpiece)){
		test=0;
		printf("-----------------------------------------------------------------------------------------------\n");
		printf("|  erreur undo: réussi à défaire le dernier coup qui n'existe pas encore                      |\n");
		printf("-----------------------------------------------------------------------------------------------\n");
	}

	return test;

}
