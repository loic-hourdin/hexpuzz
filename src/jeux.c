#include "jeux.h"
#include "solveur.h"
 
Image hexagone,iwin,ilose;
SDL_Surface *fondavecgrille, *twin, *carretimer, *ttimer, *tlost, *tplus, *tmoin, *tpassoluce, *tx;
SDL_Rect spritehex[11];


piece ptest;
int xtmp,ytmp;




/**
 * \fn       int quit ()
 * \brief    Fonction d'affichage du menun pause en jeu
 * \details  Affiche le menu pause du jeu quand le joueur appuie sur 'esc', lui permettant de quitter la partie, de modifier les options, de recommencer une partie ou de reprendre le jeu
 * \param    void
 * \return   Un booléen, normalement toujours FALSE(0)
 */
int quit (){

	Bouton bquit3,bnewgame,boption,bretourgame;
	SDL_Surface *fondquit,*backquit;
	backquit = SDL_AllocSurface(SDL_HWSURFACE, 1200, 750, BPP, 0, 0, 0, 0);
	int loop=1;
	int etat=1;
	bquit3=initbouton(500,400,200,75, "Retour menu",255, 255, 255);
	bnewgame=initbouton(500,200,200,75, "newgame",  255, 255, 255);
	bretourgame=initbouton(500,100,200,75, "Retour",  255, 255, 255);
	boption=initbouton(500,300,200,75, "option",  255, 255, 255);
	//????????????????
	fondquit = SDL_AllocSurface(SDL_HWSURFACE, 300, 500, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 300, 500);
	SDL_FillRect(fondquit, &rtmp, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_SetAlpha(fondquit, SDL_SRCALPHA, 90);

	setrect(&rtmp, 0, 0, 0, 0);
	SDL_BlitSurface(screen, NULL, backquit, &rtmp);
	setrect(&rtmp, 450, 50, 0, 0);
	SDL_BlitSurface(fondquit, NULL, backquit, &rtmp);
	while(loop){
		while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                	loop = 0;
                	etat=0;
                	break;
                case SDL_KEYDOWN:
                	if(event.key.keysym.sym == SDLK_ESCAPE) loop = 0;
	
					if(event.key.keysym.sym == SDLK_m) 
					{
						if(mute==1)
						{
							mute=0;
							Mix_VolumeMusic(Volume);
						}
						else
						{
							mute=1;
							Mix_VolumeMusic(0);
						}
					}
					break;
				 case SDL_MOUSEBUTTONUP:
				 	if (event.button.button == SDL_BUTTON_LEFT) {
				 		if(testbouton(boption) && !clickdroit){
				 			if(!option()){
				 				etat=0;
				 				loop=0;
				 			}
				 			
				 		}
				 		else if(testbouton(bretourgame)&& !clickdroit){
				 			loop=0;
				 		}
				 		if(testbouton(bquit3) && !clickdroit){
				 			loop=0;
				 			etat=2;
				 		}
				 		if(testbouton(bnewgame) && !clickdroit){
				 			loop=0;
				 			etat=3;
				 		} 
				 		
				 		clickdroit=1;
				 	}
				 	break;
				 case SDL_MOUSEBUTTONDOWN:
				 	if (event.button.button == SDL_BUTTON_LEFT) {
				 		clickdroit=0;
				 	}
				 	break;

				case SDL_MOUSEMOTION:
           			souris.x = event.motion.x;
           	 		souris.y = event.motion.y;
           	 		break;
				default:
                	break;
            }
        }
		
		if(!gticks)
		{
			startticks = SDL_GetTicks();  //Renvoie le nombre de millisecondes écoulées depuis la bibliothèque SDL initialisation. Cette valeur entoure si le programme dure plus de 49,7 jours.
			gticks = 1;
		}
		if((SDL_GetTicks() - startticks) >= 10)
		{	
			SDL_BlitSurface(backquit, NULL, screen, NULL);
			affbouton(&bquit3);
			affbouton(&bretourgame);
			affbouton(&boption);
			affbouton(&bnewgame);
			
			gticks = 0;		
				
		}
		fps++;
		if(gticksf == 0) 
		{	
			startticksf = SDL_GetTicks();
			gticksf = 1;
		}	
		if(SDL_GetTicks() - startticksf >= 1000)
		{
			gticksf = 0;
			sprintf(cfps, "%d fps", fps);
			puttext(&tfps, cfps, 16, 160, 0, 0);
			fps = 0;
		}
		setrect(&rtmp, 1100, 10, 0, 0);
		SDL_BlitSurface(tfps, NULL, screen, &rtmp);

		

		SDL_Flip(screen);


	}
	SDL_FreeSurface(fondquit);SDL_FreeSurface(backquit);
	freebouton(bquit3);freebouton(bnewgame);freebouton(boption);freebouton(bretourgame);
	return(etat);
}


/*
typedef struct {
	int LARGEUR;
	int HAUTEUR;
	int **carte;
} Grid;*/

/**
 * \fn       int jeux ()
 * \brief    Fonction de gestion d'une partie.
 * \details  Gestion de l'écran de jeu, ainsi que des actions permettant à l'utilisateur de jouer au jeu.
 * \return   Renvoie la valeur de la variable locale 'etat', qui doit systématiquement valoir à l'arrêt du programme 0.
 */

int jeux (){
	int hh=1;
	int bb,qs;
	liste lpiece;
	Grid carte;
	Listecoup listecoup;
	Listecoup listehint=NULL;
	int win,timewin,setwin;
	int timer=0;
	int timerhint=0;
	printf("dif%d\n",difficulter);
	
	int etattimer=0;
	int timeplus;
	int timemoin;
	{
		/* data */
	};
	twin=NULL;
	tlost=NULL;
	tplus=NULL;
	tmoin=NULL;
	tpassoluce=NULL;
	ttimer=NULL;
	tx=NULL;
	setwin=1;
	win=0;
	char ctimer[10];
	

	listecoup=NULL;
	int validation=0;
	Bouton bvalid,bannul,bhint;
	
	int loop=1;
	int etat=1;
	int i;
	switch (newgame()){
		case 0:
			etat=0;
			loop=0;
			break;
		case 2:
			loop=0;
			break;
	}

	switch (difficulter){
		case 0:
			timer=999;
			break;
		case 1:
			timer=100;
			break;
		case 2:
			timer=60;
			break;
		case 3:
			timer=30;
			break;
		case 4:
			timer=10;
			break;
		case 5:
			timer=1;
			break;
	}

	carretimer = SDL_AllocSurface(SDL_HWSURFACE, 100, 80, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 100, 80);
	SDL_FillRect(carretimer, &rtmp, SDL_MapRGB(screen->format, 100, 100, 100));
	SDL_SetAlpha(carretimer, SDL_SRCALPHA, 128);


	puttext(&tplus, "+10", 20, 0, 160, 0);
	puttext(&tmoin, "-10", 20, 160, 0, 0);
	puttext(&tlost, "GAME OVER", 150, 255, 0, 0);
	puttext(&twin, "WIN", 300, 255, 0, 0);
	puttext(&tx, "X", 30, 255, 0, 0);
	puttext(&tpassoluce, "aucune solution", 70, 255, 0, 0);
	fondavecgrille = SDL_AllocSurface(SDL_HWSURFACE, 1200, 750, BPP, 0, 0, 0, 0);
	bvalid=initbouton(650,650,200,75, "Valider",100, 255, 100);
	bannul=initbouton(950,650,200,75, "Undo",255, 100, 100);
	bhint=initbouton(875,650,50,75, "?",100, 100, 100);
	SDL_BlitSurface(back, NULL, screen, NULL);
	if(!lock) Mix_FadeInMusic(Playlist[0], -1, 3000);
	iwin=initimage("BMP/ecran_win.jpeg",1200, 700);
	ilose=initimage("BMP/ecran_lose.png",1200, 700);
	hexagone=initimage("BMP/hexagonecolor.png",400, 40);
	for(i=0;i<10;i++){
		setrect(&spritehex[i+1],i*40,0,40,40);
	}
	
	hexagone.sprite=spritehex;
	printf("%d\n",formegrid);
	if(formegrid==0){
		carte=creatGridInit1 (ytaillegrid,xtaillegrid);
	}
	else if(formegrid==1){
		carte=grilleTriangle(xtaillegrid);
	}
	else if(formegrid==2){
		carte=grilleTriangleInverse(xtaillegrid);
	}
	else if(formegrid==3){
		carte=grilleHexagone(xtaillegrid);
	}

	lpiece=decoupage(carte);
	desordreListe (&lpiece);
	p1=0;
	p2=1;
	p3=2;
	positionlistepiece=3;
	piecemv=0;


	ptest.Coord[0].x=0;	
	ptest.Coord[0].y=0;
	ptest.couleur=9;
	ptest.nbHex=1;
	clickdroit=0;

	//test1(carte,lpiece);
	chargebackjeu();
	affichegrid(carte,300,350);

	while(loop){
		while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                	loop = 0;
                	etat=0;
                	break;
                case SDL_KEYDOWN:
                	if(event.key.keysym.sym == SDLK_ESCAPE) {
                		switch (quit()){
							case 0:
								etat=0;
								loop=0;
								break;
							case 2:
								loop=0;
								break;
							case 3:
								loop=0;
								win=3;
								break;
						}

                	}
					
					if(event.key.keysym.sym == SDLK_l)
					{
						carte=test1(carte,lpiece);
						setrect(&rtmp, 0, 0, 0, 0);
						SDL_BlitSurface(back, NULL, fondavecgrille, &rtmp);
						affichegrid(carte, 300, 350);
						printf("c pas bien de tricher\n");
					}
					if(event.key.keysym.sym == SDLK_m) 
					{
						if(Volume==0)
						{
							Volume=64;
							Mix_VolumeMusic(Volume);
						}
						else
						{
							Volume=0;
							Mix_VolumeMusic(Volume);
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
				 	if (event.button.button == SDL_BUTTON_LEFT) {
				 		if(clickdroit && piecemv!=0 && validation==0){
				 			if(piecemv==1 && testpiecesurgrille(lpiece.donnee[p1],carte,900,200,300,350,souris.x-xtmp,souris.y-ytmp, p1,&listecoup)){
				 				validation=1;
				 				setrect(&rtmp, 0, 0, 0, 0);
								SDL_BlitSurface(back, NULL, fondavecgrille, &rtmp);
								affichegrid(carte, 300, 350);
								if (gametype==1){
									timer=timer+10;
									etattimer=1;
									sprintf(ctimer, "%d", timer);
									puttext(&ttimer, ctimer, 30, 160, 160, 160);
									timeplus=SDL_GetTicks();
								}
								hh=1;
				 			}
				 			else if(piecemv==2 && testpiecesurgrille(lpiece.donnee[p2],carte,900,350,300,350,souris.x-xtmp,souris.y-ytmp, p2,&listecoup)){
				 				validation=1;
				 				setrect(&rtmp, 0, 0, 0, 0);
								SDL_BlitSurface(back, NULL, fondavecgrille, &rtmp);
								affichegrid(carte, 300, 350);
								if (gametype==1){
									timer=timer+10;
									etattimer=1;
									sprintf(ctimer, "%d", timer);
									puttext(&ttimer, ctimer, 30, 160, 160, 160);
									timeplus=SDL_GetTicks();
								}
								hh=1;
				 			}
				 			else if(piecemv==3 && testpiecesurgrille(lpiece.donnee[p3],carte,900,500,300,350,souris.x-xtmp,souris.y-ytmp, p3,&listecoup)){
				 				validation=1;
				 				setrect(&rtmp, 0, 0, 0, 0);
								SDL_BlitSurface(back, NULL, fondavecgrille, &rtmp);
								affichegrid(carte, 300, 350);
								if (gametype==1){
									timer=timer+10;
									etattimer=1;
									sprintf(ctimer, "%d", timer);
									puttext(&ttimer, ctimer, 30, 160, 160, 160);
									timeplus=SDL_GetTicks();

								}
								hh=1;
				 			}
				 			else{
				 				piecemv=0;
				 			}
				 			if(lol){
				 				if(piecemv==1){
				 					p1=positionlistepiece;
				 					positionlistepiece++;
				 				}
				 				if(piecemv==2){
				 					p2=positionlistepiece;
				 					positionlistepiece++;
				 				}
				 				if(piecemv==3){
				 					p3=positionlistepiece;
				 					positionlistepiece++;
				 				}
				 				validation=0;
				 				piecemv=0;
				 			}
				 			if(testgridwin(carte)){
				 				win=1;
				 				setwin=1;
				 			}
				 		}
				 		clickdroit=0;			
				 	}
				 	break;

				 case SDL_MOUSEBUTTONDOWN:
				 	if (event.button.button == SDL_BUTTON_LEFT) {
				 		if(piecemv==0){
				 			hexamv=0;
							if((hexamv=testpiece(lpiece.donnee[p1],900,200))) {
								piecemv=1;
							}
							if((hexamv=testpiece(lpiece.donnee[p2],900,350))) {
								if(piecemv!=0){
									if(rando(2)){
										piecemv=2;
									}
								}
								else{
									piecemv=2;
								}								
							}
							if((hexamv=testpiece(lpiece.donnee[p3],900,500))){
								if(piecemv!=0){
									if(rando(2)){
										piecemv=3;
									}
								}
								else{
									piecemv=3;
								}
							}
							xtmp=souris.x;
							ytmp=souris.y;
				 		}
				 		if(validation && testbouton(bvalid) && !clickdroit){
				 			if(piecemv==1){
				 				p1=positionlistepiece;
				 				positionlistepiece++;
				 			}
				 			if(piecemv==2){
				 				p2=positionlistepiece;
				 				positionlistepiece++;
				 			}
				 			if(piecemv==3){
				 				p3=positionlistepiece;
				 				positionlistepiece++;
				 			}
				 			validation=0;
				 			piecemv=0;
				 		}
				 		if(lol==1 && testbouton(bannul) && !clickdroit && listecoup!=NULL){
				 			undo(&listecoup,carte,lpiece);
				 			printf("coucou\n");
				 			piecemv=0;
				 			setrect(&rtmp, 0, 0, 0, 0);
							SDL_BlitSurface(back, NULL, fondavecgrille, &rtmp);
							affichegrid(carte, 300, 350);
							if (gametype==1){
								timer=timer-10;
								etattimer=1;
								sprintf(ctimer, "%d", timer);
								puttext(&ttimer, ctimer, 30, 160, 160, 160);
								timemoin=SDL_GetTicks();
								
							}
							hh=1;
				 		}
				 		if(validation && testbouton(bannul) && !clickdroit){
				 			undo(&listecoup,carte,lpiece);
				 			validation=0;
				 			piecemv=0;
				 			setrect(&rtmp, 0, 0, 0, 0);
							SDL_BlitSurface(back, NULL, fondavecgrille, &rtmp);
							affichegrid(carte, 300, 350);
							if (gametype==1){
								timer=timer-10;
								etattimer=1;
								sprintf(ctimer, "%d", timer);
								puttext(&ttimer, ctimer, 30, 160, 160, 160);
								timemoin=SDL_GetTicks();
							}
							hh=1;
				 		}
				 		if(testbouton(bhint) && !clickdroit){
				 			printf("hint!!!\n");
				 			if(hh){
				 				listehint=lancement(carte,lpiece);
				 				hh=0;
				 			}
				 			
				 			
				 			timerhint=SDL_GetTicks();
				 		}				 		
				 		clickdroit=1;
				 		
				 	}
				 	break;

				case SDL_MOUSEMOTION:
           			souris.x = event.motion.x;
           	 		souris.y = event.motion.y;
           	 		break;
				default:
                	break;
            }
        }
		
		if(!gticks)
		{
			startticks = SDL_GetTicks();  //Renvoie le nombre de millisecondes écoulées depuis la bibliothèque SDL initialisation. Cette valeur entoure si le programme dure plus de 49,7 jours.
			gticks = 1;
		}
		if((SDL_GetTicks() - startticks) >= 10)
		{	SDL_BlitSurface(fondavecgrille, NULL, screen, NULL);

			if(piecemv != 1){
				affichepiece(lpiece.donnee[p1],900,200);
			}
			if(piecemv != 2){
				affichepiece(lpiece.donnee[p2],900,350);
			}
			if(piecemv != 3){
				affichepiece(lpiece.donnee[p3],900,500);
			}

			if(piecemv == 1 && validation==0){
				affichepiece(lpiece.donnee[p1],souris.x-xtmp+900,souris.y-ytmp+200);
			}
			if(piecemv == 2 && validation==0){
				affichepiece(lpiece.donnee[p2],souris.x-xtmp+900,souris.y-ytmp+350);
			}
			if(piecemv == 3 && validation==0){
				affichepiece(lpiece.donnee[p3],souris.x-xtmp+900,souris.y-ytmp+500);
			}
			if(lol==0 || lol==1){
				affbouton(&bannul);
			}
			if(lol==0){
				affbouton(&bvalid);
			}
			affbouton(&bhint);
			if(win>0){
				printf("win1\n");
				
				if(setwin){
					printf("yepyep\n");
					timewin=SDL_GetTicks();
					setwin=0;
				}
				if(win!=3){
					printf("affiche win\n");
					setrect(&rtmp, 0, 0, 0, 0);
					SDL_BlitSurface(iwin.image, NULL, screen, &rtmp);
				}
				

				if(SDL_GetTicks()-timewin>2000 && clickdroit){	
					loop=0;
					win=2;
				}
			}
			if(win<0){
				
				if(setwin){
					timewin=SDL_GetTicks();
					setwin=0;
				}
		
				setrect(&rtmp, 0, 0, 0, 0);
				SDL_BlitSurface(ilose.image, NULL, screen, &rtmp);

				

				if(SDL_GetTicks()-timewin>2000 && clickdroit){	
					loop=0;
					win=-2;
				}
			}
				
			


			gticks = 0;		
				
		}
		fps++;
		if(gticksf == 0) 
		{	
			startticksf = SDL_GetTicks();
			gticksf = 1;
		}
		if(SDL_GetTicks() - startticksf >= 1000)
		{
			gticksf = 0;
			if(gametype==1){
				
				if(timer>0){
					if(etattimer==1){
						timer--;
					}
				}
				else if(win==0){
					win=-1;
				}
				sprintf(ctimer, "%d", timer);
				puttext(&ttimer, ctimer, 30, 160, 160, 160);
			}
			sprintf(cfps, "%d fps", fps);
			puttext(&tfps, cfps, 16, 160, 0, 0);
			fps = 0;
		}


		if(gametype==1){
			if(SDL_GetTicks() - timeplus <= 1000)
			{
				setrect(&rtmp, 720, 50, 0, 0);
				SDL_BlitSurface(tplus, NULL, screen, &rtmp);			
			}
			if(SDL_GetTicks() - timemoin <= 1000)
			{
				setrect(&rtmp, 720, 50, 0, 0);
				SDL_BlitSurface(tmoin, NULL, screen, &rtmp);			
			}			
		}

		if(SDL_GetTicks() - timerhint <= 1500)
		{
			if(listehint==NULL){
				setrect(&rtmp, 200, 200, 0, 0);
				SDL_BlitSurface(tpassoluce, NULL, screen, &rtmp);
			}
			else{
				//printf("hint :x=%d y=%d\n nb:%d i:%d",listehint->x,listehint->y,lpiece.donnee[listehint->pospiece].nbHex,listehint->pospiece );
				for(i=0;i<lpiece.donnee[listehint->pospiece].nbHex;i++){
					qs=lpiece.donnee[listehint->pospiece].Coord[i].y-lpiece.donnee[listehint->pospiece].Coord[0].y+listehint->x-((lpiece.donnee[listehint->pospiece].Coord[0].x%2)*((lpiece.donnee[listehint->pospiece].Coord[i].x-lpiece.donnee[listehint->pospiece].Coord[0].x+10000)%2))+((listehint->y%2)*((lpiece.donnee[listehint->pospiece].Coord[i].x-lpiece.donnee[listehint->pospiece].Coord[0].x+10000)%2));
					bb=lpiece.donnee[listehint->pospiece].Coord[i].x-lpiece.donnee[listehint->pospiece].Coord[0].x+listehint->y;
					//printf("hint :qs=%d bb=%d\n",qs,bb );
					if(!(bb>=0 && bb<carte.HAUTEUR && qs>=0 && qs<carte.LARGEUR && carte.carte[bb][qs]==1)){
						printf("ERROR::Hint	fail pose\n");
						return(0);
					}
					else{
						setrect(&rtmp, 10+(qs-carte.LARGEUR/2)*32+300+(((bb-carte.HAUTEUR/2)+(carte.HAUTEUR/2))%2)*16, 5+(bb-carte.HAUTEUR/2)*30+350, 0, 0);
						SDL_BlitSurface(tx, NULL, screen, &rtmp);

					}

				}
			}			
		}
		
		setrect(&rtmp, 1100, 10, 0, 0);
		SDL_BlitSurface(tfps, NULL, screen, &rtmp);
		setrect(&rtmp, 720, 10, 0, 0);
		SDL_BlitSurface(ttimer, NULL, screen, &rtmp);

		SDL_Flip(screen);


	}
	SDL_FreeSurface(hexagone.image);SDL_FreeSurface(iwin.image);SDL_FreeSurface(ilose.image);	
	SDL_FreeSurface(fondavecgrille);SDL_FreeSurface(tpassoluce);
	SDL_FreeSurface(twin);SDL_FreeSurface(ttimer);SDL_FreeSurface(carretimer);SDL_FreeSurface(tplus);SDL_FreeSurface(tmoin);SDL_FreeSurface(tlost);SDL_FreeSurface(tx);

	freebouton(bannul);freebouton(bvalid);freebouton(bhint);
	freeGrid (carte);
	if(win==2 || win==3  || win==-1 || win==-2){
		etat=99;
	}
	printf("etat=%d\n", etat);
	return(etat);
}

/**
 * \fn       void affichegrid( Grid grid, int x, int y)
 * \brief    affiche la grille 
 * \details  Fonction d'affichage de la grille (=plateau de jeu)
 * \param    grid est la grille a afficher
 * \param    int x: position x de la grille
 * \param    int y: position y de la grille
 * \return   void
*/
void affichegrid( Grid grid, int x, int y){
	int l,h,i,j,a;
	l=grid.LARGEUR;
	h=grid.HAUTEUR;
	for (i=-(h/2);i<(h/2)+(h%2);i++){
		for (j=-(l/2);j<(l/2)+(l%2);j++){
			a=grid.carte[i+(h/2)][j+(l/2)];
			if(a!=0){
				setrect(&rtmp, j*32+x+((i+(h/2))%2)*16, i*30+y, 0, 0);
				SDL_BlitSurface(hexagone.image, &spritehex[a], fondavecgrille, &rtmp);
			}
			
		}
	}
}


/**
 * \fn       void affichepiece (piece piece,int x,int y)
 * \brief    Affiche d'une pièce
 * \details  Fonction permettant d'afficher une pièce passée en argument, à l'aide de ses coordonnées, aussi passées en argument.
 * \param    piece piece est la piece a afficher
 * \param    int x: position x de la piece
 * \param    int y: position y de la piece
 * \return   void
*/
void affichepiece(piece piece,int x,int y){
	int taille=piece.nbHex;
	int color=piece.couleur;
	int xx=piece.Coord[0].x;
	int yy=piece.Coord[0].y;
	int i;
	for (i=0;i<taille;i++){
		setrect(&rtmp, (piece.Coord[i].y-yy)*32+((piece.Coord[i].x)%2)*16+x-16*(xx%2),(piece.Coord[i].x-xx)*30+y, 0, 0);
		SDL_BlitSurface(hexagone.image, &spritehex[color], screen, &rtmp);
	}
} 


/**
 * \fn       void chargebackjeu ()
 * \brief    Charge le fond du jeux
 * \details  Affichage du fond d'écran du jeu, en utilisant 'SDL_BlitSurface' et 'setrect'
 * \return   void
*/
void chargebackjeu(){
	setrect(&rtmp, 0, 0, 0, 0);
	SDL_BlitSurface(fond.image, NULL, back, &rtmp);
	if(gametype!=0){
		setrect(&rtmp, 700, 0, 0, 0);
	SDL_BlitSurface(carretimer, NULL, back, &rtmp);
	}
	setrect(&rtmp, 0, 0, 0, 0);
	SDL_BlitSurface(back, NULL, fondavecgrille, &rtmp);
}

/**
 * \fn       void test1(Grid grid, liste l)
 * \brief    
 * \details
 * \param    Grid grid: 
 * \param    liste l:   
 * \return   void
*/
Grid test1(Grid grid,liste l){
	int i,j;
	for(i=0;i<l.nbPieces;i++){
		for(j=0;j<l.donnee[i].nbHex;j++){
			if(i==p1){
				grid.carte[l.donnee[i].Coord[j].x][l.donnee[i].Coord[j].y]=1;
			}
			else if(i==p2){
				grid.carte[l.donnee[i].Coord[j].x][l.donnee[i].Coord[j].y]=1;
			}
			else if(i==p3){
				grid.carte[l.donnee[i].Coord[j].x][l.donnee[i].Coord[j].y]=1;
			}
			else{
				grid.carte[l.donnee[i].Coord[j].x][l.donnee[i].Coord[j].y]=l.donnee[i].couleur;

			}
			
		}
	}
	return(grid);
}


/**
 * \fn       void affichepiece(piece piece,int x,int y)
 * \brief    Affichage d'une pièce
 * \details  
 * \param    piece piece est la piece a afficher
 * \param    int x: position x de la piece
 * \param    int y: position y de la piece
 * \return   Renvoie un booléen TRUE(1) si la pièce est affichée aux coordonnées où se trouve le pointeur de la souris, ou FALSE(0) sinon.
*/
int testpiece(piece piece,int x,int y){
	int tmp=0;
	int taille=piece.nbHex;
	int xx=piece.Coord[0].x;
	int yy=piece.Coord[0].y;
	int i;
	int qs,bb;
	for (i=0;i<taille;i++){
		qs=(piece.Coord[i].y-yy)*32+((piece.Coord[i].x)%2)*16+x-16*(xx%2);
		bb=(piece.Coord[i].x-xx)*30+y;
		if(qs<souris.x && qs+35>souris.x && bb<souris.y && bb+40>souris.y){
			tmp=1;
		}
	}
	return(tmp);
}


/**
 * \fn       int testpiecesurgrille(piece piece,Grid car,int xpiece,int ypiece,int xgrid,int ygrid,int deplacementx, int  deplacementy, int pospiece, Listecoup* l)
 * \brief    Teste si une piece peut être placée sur la grille.
 * \details  Teste si une pièce de coordonnées passées en argument peut être posée sur la grille, en fonction du déplacement qu'elle a effectuée.
 * \param    piece piece est la piece a placer
 * \param    Grid car la grille ou on veut placer la piece
 * \param    int xpiece la position en x de la piece
 * \param    int ypiece la position en y de la piece
 * \param    int xgrid la position en x de la grille
 * \param    int ygrid la position en y de la grille
 * \param    int deplacementx le deplacement en x de la piece
 * \param    int  deplacementy le deplacement en y de la piece
 * \param    int pospiece quelle piece on deplace p1 p2 ou p3
 * \param    Listecoup* l la liste de coups jouer
 * \return   Renvoie TRUE(1) si la pièce peut être posée effectivement, FALSE(0) sinon.
*/
int testpiecesurgrille(piece piece,Grid car,int xpiece,int ypiece,int xgrid,int ygrid,int deplacementx, int  deplacementy, int pospiece, Listecoup* l){
	int x,y;
	y=((car.HAUTEUR/2)*30+10+deplacementy+ypiece-ygrid)/30;
	x=(11+deplacementx+xpiece-xgrid+(car.LARGEUR/2)*32-(16*(y%2)))/32;
	printf("x=%d  y=%d\n",x,y);
	int xx=piece.Coord[0].x;
	int yy=piece.Coord[0].y;
	int i;
	int qs,bb;
	for (i=0;i<piece.nbHex;i++){
		qs=piece.Coord[i].y-yy+x-((xx%2)*((piece.Coord[i].x-xx+10000)%2))+((y%2)*((piece.Coord[i].x-xx+10000)%2));
		bb=piece.Coord[i].x-xx+y;
		if(!(bb>=0 && bb<car.HAUTEUR && qs>=0 && qs<car.LARGEUR && car.carte[bb][qs]==1)){
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
	*l= cons(*l, x, y, pospiece);
	return(1);
}

/**
 * \fn       int undo(Listecoup* listecoup, Grid carte,liste llpiece)
 * \brief    Défait le dernier coup effectué.
 * \details  Défait le dernier coup effectué, et replace la pièce concernée dans le sélecteur.
 * \param    Listecoup* listecoup
 * \param    Grid carte
 * \param    liste llpiece
 * \return   Un booléen, TRUE si on a réussi à défaire le dernier coup, FALSE sinon
*/
int undo(Listecoup* listecoup, Grid carte,liste llpiece){
	int i;
	
	int qs,bb;
	int xx=llpiece.donnee[(*listecoup)->pospiece].Coord[0].x;
	int yy=llpiece.donnee[(*listecoup)->pospiece].Coord[0].y;
	int x=(*listecoup)->x;
	int y=(*listecoup)->y;
	//printf("%d  %d \n",x, y);
	for (i=0;i<llpiece.donnee[(*listecoup)->pospiece].nbHex;i++){
		qs=llpiece.donnee[(*listecoup)->pospiece].Coord[i].y-yy+x-((xx%2)*((llpiece.donnee[(*listecoup)->pospiece].Coord[i].x-xx+10000)%2))+((y%2)*((llpiece.donnee[(*listecoup)->pospiece].Coord[i].x-xx+10000)%2));
		bb=llpiece.donnee[(*listecoup)->pospiece].Coord[i].x-xx+y;
		//printf(" lol %d  %d \n",bb, qs);
		if((bb>=0 && bb<carte.HAUTEUR && qs>=0 && qs<carte.LARGEUR && carte.carte[bb][qs]!=0)){
			carte.carte[bb][qs]=1;

		}
	}
	if((*listecoup)->piecemv==1){
		positionlistepiece--;
		p1=(*listecoup)->pospiece;
	}
	else if((*listecoup)->piecemv==2){
		positionlistepiece--;
		p2=(*listecoup)->pospiece;
	}
	else if((*listecoup)->piecemv==3){
		positionlistepiece--;
		p3=(*listecoup)->pospiece;
	}
	else{
		perror("ERROR : incorrect value of \'(*listecoup)->piecemv\'");
		return(0);
	}
	(*listecoup)= retour((*listecoup));

	//printf("lol2\n");
	return(1);
}

/**
 * \fn       Listecoup cons (Listecoup l, int x, int y, int pospiece)
 * \brief    Fonction d'initialisation d'une structure Listecoup
 * \details  Alloue la mémoire pour une structure Listecoup et initialise ses valeurs avec les éléments passés en arguments de la fonction
 * \param    Listecoup l: La structure Listecoup s'apparentant à une liste chaînée, (l) est le pointeur du chaînon suivant
 * \param    int x: La position en x de la pièce courante
 * \param    int y: La position en y de la pièce courante
 * \param    int pospiece: Le numéro du sélecteur d'où la pièce est issue
 * \return   Renvoie une structure de type Listecoup, initialisée avec les éléments passés en paramètres
 */
Listecoup cons (Listecoup l, int x, int y, int pospiece){
	Listecoup p;
	p = malloc(sizeof(struct maillon));
	p->x = x;
	p->y = y;
	p->piecemv = piecemv;
	p->pospiece = pospiece;
	p->suivant=l;
return(p);
}

/**
 * \fn       Listecoup retour (Listecoup l)
 * \brief    Fonction de retour en arrière dans la structure Listecoup
 * \details  Free l'élément courant et fait pointer vers le coup précédent
 * \param    Listecoup l: L'élément courant à 'remettre' dans la liste des pièces
 * \return   Le coup précédent
 */
Listecoup retour (Listecoup l){
	//printf("retour\n");
	Listecoup p=l->suivant;
	free (l);
return(p);
}

/**
 * \fn       int testgridwin(Grid map)
 * \brief    Fonction de test de la condition de victoire
 * \details  Vérifie que chaque case du plateau de jeu est remplie
 * \param    Grid map: Le plateau de jeu à tester
 * \return   Un booléen, TRUE si le plateau est gagnant, FALSE sinon
 */
int testgridwin(Grid map){
	int i,j;
	for(j=0;j<map.HAUTEUR;j++){
		for(i=0;i<map.LARGEUR;i++){
			if(map.carte[j][i]==1)return(0);
		}
	}
	return(1);
}

// atention x et y son inversés par raport a la grille pour les pieces

