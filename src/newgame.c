#include "newgame.h"

//SDL_SetAlpha(zozor, SDL_SRCALPHA, 128);  transparence
SDL_Surface *tnewgame,*tformegrid,*tvalformegrid, *carreforme,*back2, *ttaillex,*ttailley,*carretaillex,*carretailley,*tvaltaillex,*tvaltailley ;
SDL_Surface *ttaillepiecemax, *ttaillepiecemin, *ttaillevalmax, *ttaillevalmin,*carremax, *carremin, *tmodejeux, *carremode,*tvalmodejeux;
SDL_Surface *tgametype, *tvalgametype, *carregametype, *tdifficulter,*tvaldifficulter, *carredifficulter;


Image iup, idown;
int up;
int down;

/**
 * \fn       int newgame ()
 * \brief    Fonction exécutée quand le bouton jouer est sélectionné sur le menu principal.
 * \details  Cette fonction permet de choisir l'intégralité
 * \return   0
*/
int newgame (){
	tnewgame=NULL;tformegrid=NULL;tvalformegrid=NULL; ttaillex=NULL;ttailley=NULL;;tvaltaillex=NULL;tvaltailley=NULL;;
    ttaillepiecemax=NULL; ttaillepiecemin=NULL; ttaillevalmax=NULL; ttaillevalmin=NULL;tmodejeux=NULL;tvalmodejeux=NULL;
    tgametype=NULL;tvalgametype=NULL;tdifficulter=NULL;tvaldifficulter=NULL;

    int option=0;

	char ctaillex[10];
	char ctailley[10];
	char ctaillemin[10];
	char ctaillemax[10];
	char* forme[4];
	forme[0]="rectangle";
	forme[1]="triangle";
	forme[2]="triangleinverse";
	forme[3]="hexagone";
	int modif=0;
	char* taillex[4];
	taillex[0]="largeur:";
	taillex[1]="taille:";
	taillex[2]="taille:";
	taillex[3]="taille:";

	char* mode[3];
	mode[1]="undo possible";
	mode[2]="poser c'est poser";
	mode[0]="poser puis valider";

	char* game[2];
	game[0]="Standard";
	game[1]="Time Attack";

	char* diffi[6];
	diffi[0]="easy";
	diffi[1]="medium";
	diffi[2]="hard";
	diffi[3]="extreme";
	diffi[4]="hard extreme";
	diffi[5]="impossible!!!";







	Bouton bok, boption1, boption2;
	int loop=1;
	int etat=1;
	puttext(&tnewgame, "OPTION NEWGAME", 60, 255, 255, 255);
	puttext(&tformegrid, "forme de la grille :", 30, 255, 0, 0);
	puttext(&tgametype, "mode de jeux :", 30, 255, 0, 0);
	setrect(&rtmp, 0, 0, 0, 0);
	puttext(&ttaillex, taillex[formegrid], 30, 255, 0, 0);
	puttext(&ttailley, "hauteur:", 30, 255, 0, 0);
	puttext(&ttaillepiecemax, "taille piece max:", 30, 255, 0, 0);
	puttext(&ttaillepiecemin, "taille piece min:", 30, 255, 0, 0);
	puttext(&tmodejeux, "mode de validation :", 30, 255, 0, 0);
	puttext(&tdifficulter, "difficulter:", 30, 255, 0, 0);




	sprintf(ctaillex, "%d",xtaillegrid);
	sprintf(ctailley, "%d",ytaillegrid);
	puttext(&tvaltaillex, ctaillex, 20, 0, 0, 0);
	puttext(&tvaltailley, ctailley, 20, 0, 0, 0);

	sprintf(ctaillemin, "%d",hexMin);
	sprintf(ctaillemax, "%d",hexMax);
	puttext(&ttaillevalmax, ctaillemax, 20, 0, 0, 0);
	puttext(&ttaillevalmin, ctaillemin, 20, 0, 0, 0);

	
	back2 = SDL_AllocSurface(SDL_HWSURFACE, 1200, 750, BPP, 0, 0, 0, 0);
	iup=initimage("BMP/icone-flechedroite.png",38, 38);
	idown=initimage("BMP/icone-flechegauche.png",38, 38);
	bok=initbouton(500,600,400,75, "LANCER LA PARTIE",  255, 255, 255);
	boption1=initbouton(100,600,200,75, "option+",  255, 100, 100);
	boption2=initbouton(100,600,200,75, "option+",  100, 255, 100);


	carreforme = SDL_AllocSurface(SDL_HWSURFACE, 200, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 200, 50);
	SDL_FillRect(carreforme, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carreforme, SDL_SRCALPHA, 128);

	carretaillex = SDL_AllocSurface(SDL_HWSURFACE, 100, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 100, 50);
	SDL_FillRect(carretaillex, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carretaillex, SDL_SRCALPHA, 128);

	carretailley = SDL_AllocSurface(SDL_HWSURFACE, 100, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 100, 50);
	SDL_FillRect(carretailley, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carretailley, SDL_SRCALPHA, 128);

	carremax = SDL_AllocSurface(SDL_HWSURFACE, 100, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 100, 50);
	SDL_FillRect(carremax, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carremax, SDL_SRCALPHA, 128);

	carremin = SDL_AllocSurface(SDL_HWSURFACE, 100, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 100, 50);
	SDL_FillRect(carremin, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carremin, SDL_SRCALPHA, 128);

	carremode = SDL_AllocSurface(SDL_HWSURFACE, 250, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 250, 50);
	SDL_FillRect(carremode, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carremode, SDL_SRCALPHA, 128);

	carredifficulter = SDL_AllocSurface(SDL_HWSURFACE, 200, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 200, 50);
	SDL_FillRect(carredifficulter, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carredifficulter, SDL_SRCALPHA, 128);

	carregametype = SDL_AllocSurface(SDL_HWSURFACE, 200, 50, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 200, 50);
	SDL_FillRect(carregametype, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carregametype, SDL_SRCALPHA, 128);

	chargebacknewgame(option);
	SDL_BlitSurface(back, NULL, back2, NULL);
	puttext(&tvalformegrid, forme[formegrid], 20, 0, 0, 0);
	setrect(&rtmp, 610, 150, 0, 0);
	SDL_BlitSurface(tvalformegrid, NULL, back2, &rtmp);
	puttext(&ttaillex, taillex[formegrid], 30, 255, 0, 0);
	sprintf(ctaillex, "%d",xtaillegrid);
	puttext(&tvaltaillex, ctaillex, 20, 0, 0, 0);
	setrect(&rtmp, 300, 230, 0, 0);
	SDL_BlitSurface(ttaillex, NULL, back2, &rtmp);
	setrect(&rtmp, 630, 232, 0, 0);
	SDL_BlitSurface(tvaltaillex, NULL, back2, &rtmp);

	sprintf(ctaillemin, "%d",hexMin);
	sprintf(ctaillemax, "%d",hexMax);
	puttext(&ttaillevalmax, ctaillemax, 20, 0, 0, 0);
	puttext(&ttaillevalmin, ctaillemin, 20, 0, 0, 0);

	setrect(&rtmp, 630, 382, 0, 0);
	SDL_BlitSurface(ttaillevalmax, NULL, back2, &rtmp);
	setrect(&rtmp, 630, 460, 0, 0);
	SDL_BlitSurface(ttaillevalmin, NULL, back2, &rtmp);

	puttext(&tvalmodejeux, mode[lol], 20, 0, 0, 0);
	setrect(&rtmp, 610, 528, 0, 0);
	SDL_BlitSurface(tvalmodejeux, NULL, back2, &rtmp);
	
	if(formegrid==0){
		sprintf(ctailley, "%d",ytaillegrid);
		puttext(&tvaltailley, ctailley, 20, 0, 0, 0);
		setrect(&rtmp, 600, 290, 0, 0);
		SDL_BlitSurface(carretailley, NULL, back2, &rtmp);
		setrect(&rtmp, 300, 300, 0, 0);
		SDL_BlitSurface(ttailley, NULL, back2, &rtmp);
		setrect(&rtmp, 630, 300, 0, 0);
		SDL_BlitSurface(tvaltailley, NULL, back2, &rtmp);
		setrect(&rtmp, 705, 295, 0, 0);
		SDL_BlitSurface(iup.image, NULL, back2, &rtmp);
	
		setrect(&rtmp, 560, 295, 0, 0);
		SDL_BlitSurface(idown.image, NULL, back2, &rtmp);

	}

	if(!lock) Mix_FadeInMusic(Playlist[1],-1, 3000);

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
                		loop =0;
                		etat=2;
                	}

	
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
				 		
				 		if(testbouton(bok) && !clickdroit){
				 			loop=0;
				 		} 
				 		if(testbouton(boption1) && !clickdroit){
				 			if(option){
				 				option=0;
				 				modif=1;
				 				chargebacknewgame(option);
				 			}
				 			else{
				 				option=1;
				 				modif=1;
				 				chargebacknewgame(option);
				 			}
				 		}
				 		if(option==0){
				 			if(souris.x>805 && souris.x<843 && souris.y>145 && souris.y<183 && !clickdroit){
					 			formegrid=(formegrid+1)%4;
					 			


					 			if(xtaillegrid>10 && formegrid==3){
					 				xtaillegrid=10;
					 			}
					 			if(xtaillegrid>15 && (formegrid==2||formegrid==1)){
					 				xtaillegrid=15;
					 			}
					 			if(xtaillegrid>17 && formegrid==0){
					 				xtaillegrid=17;
					 			}
					 			
					 			if(ytaillegrid>22 && formegrid==0){
					 					ytaillegrid=22;
					 			}
					 			if(hexMax>xtaillegrid*ytaillegrid/2 && formegrid==0){
					 				hexMax=xtaillegrid*ytaillegrid/2;
					 			}
					 			if(hexMax>xtaillegrid*xtaillegrid/2 && (formegrid==2||formegrid==1||formegrid==3)){
					 				hexMax=xtaillegrid*xtaillegrid/2;
					 			}
					 			if(hexMin>hexMax){
					 				hexMin=hexMax;
					 				}
					 			modif=1;
					 		}
					 		if(souris.x>560 && souris.x<598 && souris.y>145 && souris.y<183 && !clickdroit){
					 			formegrid=(formegrid+3)%4;
					 			
					 			if(xtaillegrid>10 && formegrid==3){
					 				xtaillegrid=10;
					 			}
					 			if(xtaillegrid>15 && (formegrid==2||formegrid==1)){
					 				xtaillegrid=15;
					 			}
					 			if(xtaillegrid>17 && formegrid==0){
					 				xtaillegrid=17;
					 			}



					 			if(ytaillegrid>22 && formegrid==0){
					 				ytaillegrid=22;
					 			}
					 			if(hexMax>xtaillegrid*ytaillegrid/2 && formegrid==0){
					 				hexMax=xtaillegrid*ytaillegrid/2;
					 			}
					 			if(hexMax>xtaillegrid*xtaillegrid/2 && (formegrid==2||formegrid==1||formegrid==3)){
					 				hexMax=xtaillegrid*xtaillegrid/2;
					 			}
					 			if(hexMin>hexMax){
					 				hexMin=hexMax;
					 				}

					 			modif=1;
					 		}
					 		if(souris.x>705 && souris.x<743 && souris.y>215 && souris.y<253 && !clickdroit){
					 			xtaillegrid++;
					 			if(xtaillegrid>10 && formegrid==3){
					 				xtaillegrid=10;
					 			}
					 			if(xtaillegrid>15 && (formegrid==2||formegrid==1)){
					 				xtaillegrid=15;
					 			}
					 			if(xtaillegrid>17 && formegrid==0){
					 				xtaillegrid=17;
					 			}

					 			if(hexMax>xtaillegrid*ytaillegrid/2 && formegrid==0){
					 				hexMax=xtaillegrid*ytaillegrid/2;
					 			}
					 			if(hexMax>xtaillegrid*xtaillegrid/2 && (formegrid==2||formegrid==1||formegrid==3)){
					 				hexMax=xtaillegrid*xtaillegrid/2;
					 			}
					 			if(hexMin>hexMax){
					 				hexMin=hexMax;
					 				}
					 			modif=1;
					 		}
					 		if(souris.x>560 && souris.x<598 && souris.y>215 && souris.y<253 && !clickdroit){
					 			xtaillegrid--;
					 			if(xtaillegrid<3){
					 				xtaillegrid=3;
					 			}
					 			
					 			if(ytaillegrid>22 && formegrid==0){
					 				ytaillegrid=22;
					 			}
					 			if(hexMax>xtaillegrid*ytaillegrid/2 && formegrid==0){
					 				hexMax=xtaillegrid*ytaillegrid/2;
					 			}
					 			if(hexMax>xtaillegrid*xtaillegrid/2 && (formegrid==2||formegrid==1||formegrid==3)){
					 				hexMax=xtaillegrid*xtaillegrid/2;
					 			}
					 			if(hexMin>hexMax){
					 				hexMin=hexMax;
					 				}
					 			modif=1;
					 		}



					 		if(souris.x>705 && souris.x<743 && souris.y>370 && souris.y<408 && !clickdroit){
					 			hexMax++;
					 			if(hexMax>xtaillegrid*ytaillegrid/2 && formegrid==0){
					 				hexMax=xtaillegrid*ytaillegrid/2;
					 			}
					 			if(hexMax>xtaillegrid*xtaillegrid/2 && (formegrid==2||formegrid==1||formegrid==3)){
					 				hexMax=xtaillegrid*xtaillegrid/2;
					 			}
					 			modif=1;
					 		}
					 		if(souris.x>560 && souris.x<598 && souris.y>370 && souris.y<408 && !clickdroit){
					 			hexMax--;
					 			if(hexMax<hexMin){
					 				hexMax=hexMin;
					 			}
					 			
					 			modif=1;
					 		}

					 		if(souris.x>705 && souris.x<743 && souris.y>450 && souris.y<488 && !clickdroit){
					 			hexMin++;
					 			if(hexMin>hexMax){
					 				hexMin=hexMax;
					 			}
					 			
					 			modif=1;
					 		}
					 		if(souris.x>560 && souris.x<598 && souris.y>450 && souris.y<488 && !clickdroit){
					 			hexMin--;
					 			if(hexMin<1){
					 				hexMin=1;
					 			}
					 			
					 			modif=1;
					 		}


					 		if(formegrid==0){
					 			if(souris.x>705 && souris.x<743 && souris.y>295 && souris.y<333 && !clickdroit){
					 				ytaillegrid++;
					 				if(ytaillegrid>22 && formegrid==0){
					 					ytaillegrid=22;
					 				}
					 				if(hexMax>xtaillegrid*ytaillegrid/2 && formegrid==0){
					 				hexMax=xtaillegrid*ytaillegrid/2;
						 			}
						 			if(hexMax>xtaillegrid*xtaillegrid/2 && (formegrid==2||formegrid==1||formegrid==3)){
						 				hexMax=xtaillegrid*xtaillegrid/2;
						 			}
						 			if(hexMin>hexMax){
					 				hexMin=hexMax;
					 				}
					 				modif=1;
					 			}
					 			if(souris.x>560 && souris.x<598 && souris.y>295 && souris.y<333 && !clickdroit){
					 				ytaillegrid--;
					 				if(ytaillegrid<3){
					 					ytaillegrid=3;
					 				}
					 				if(ytaillegrid>22 && formegrid==0){
					 				ytaillegrid=22;
						 			}
						 			if(hexMax>xtaillegrid*ytaillegrid/2 && formegrid==0){
						 				hexMax=xtaillegrid*ytaillegrid/2;
						 			}
						 			if(hexMax>xtaillegrid*xtaillegrid/2 && (formegrid==2||formegrid==1||formegrid==3)){
						 				hexMax=xtaillegrid*xtaillegrid/2;
						 			}
						 			if(hexMin>hexMax){
						 				hexMin=hexMax;
						 				}
					 				modif=1;
					 			}
					 		}




					 		if(souris.x>855 && souris.x<893 && souris.y>525 && souris.y<563 && !clickdroit){
					 			lol=(lol+1)%3;
					 			
					 			modif=1;
					 		}
					 		if(souris.x>560 && souris.x<598 && souris.y>525 && souris.y<563 && !clickdroit){
					 			lol=(lol+2)%3;
					 			
					 				modif=1;
					 		}

				 		}
				 		else{
				 			if(souris.x>805 && souris.x<843 && souris.y>145 && souris.y<183 && !clickdroit){
					 			gametype=(gametype+1)%2;
					 			
					 			modif=1;
					 		}
					 		if(souris.x>560 && souris.x<598 && souris.y>145 && souris.y<183 && !clickdroit){
					 			gametype=(gametype+1)%2;
					 			modif=1;
					 		}
					 		if(gametype){
					 			if(souris.x>805 && souris.x<843 && souris.y>215 && souris.y<253 && !clickdroit){
						 			difficulter=(difficulter+1)%6;
						 			
						 			modif=1;
						 		}
						 		if(souris.x>560 && souris.x<598 && souris.y>215 && souris.y<253 && !clickdroit){
						 			difficulter=(difficulter+5)%6;
						 			modif=1;
						 		}

					 		}
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
		if(modif){
			modif=0;

			SDL_BlitSurface(back, NULL, back2, NULL);
			if(option==0){
				puttext(&tvalformegrid, forme[formegrid], 20, 0, 0, 0);
				setrect(&rtmp, 610, 150, 0, 0);
				SDL_BlitSurface(tvalformegrid, NULL, back2, &rtmp);
				puttext(&ttaillex, taillex[formegrid], 30, 255, 0, 0);
				sprintf(ctaillex, "%d",xtaillegrid);
				puttext(&tvaltaillex, ctaillex, 20, 0, 0, 0);
				setrect(&rtmp, 300, 230, 0, 0);
				SDL_BlitSurface(ttaillex, NULL, back2, &rtmp);
				setrect(&rtmp, 630, 232, 0, 0);
				SDL_BlitSurface(tvaltaillex, NULL, back2, &rtmp);

				sprintf(ctaillemin, "%d",hexMin);
				sprintf(ctaillemax, "%d",hexMax);
				puttext(&ttaillevalmax, ctaillemax, 20, 0, 0, 0);
				puttext(&ttaillevalmin, ctaillemin, 20, 0, 0, 0);

				setrect(&rtmp, 630, 382, 0, 0);
				SDL_BlitSurface(ttaillevalmax, NULL, back2, &rtmp);
				setrect(&rtmp, 630, 460, 0, 0);
				SDL_BlitSurface(ttaillevalmin, NULL, back2, &rtmp);

				puttext(&tvalmodejeux, mode[lol], 20, 0, 0, 0);
				setrect(&rtmp, 610, 528, 0, 0);
				SDL_BlitSurface(tvalmodejeux, NULL, back2, &rtmp);

				
				if(formegrid==0){
					sprintf(ctailley, "%d",ytaillegrid);
					puttext(&tvaltailley, ctailley, 20, 0, 0, 0);
					setrect(&rtmp, 600, 290, 0, 0);
					SDL_BlitSurface(carretailley, NULL, back2, &rtmp);
					setrect(&rtmp, 300, 300, 0, 0);
					SDL_BlitSurface(ttailley, NULL, back2, &rtmp);
					setrect(&rtmp, 630, 300, 0, 0);
					SDL_BlitSurface(tvaltailley, NULL, back2, &rtmp);
					setrect(&rtmp, 705, 295, 0, 0);
					SDL_BlitSurface(iup.image, NULL, back2, &rtmp);
				
					setrect(&rtmp, 560, 295, 0, 0);
					SDL_BlitSurface(idown.image, NULL, back2, &rtmp);

				}

			}
			else{
				puttext(&tvalgametype, game[gametype], 20, 0, 0, 0);
				setrect(&rtmp, 610, 150, 0, 0);
				SDL_BlitSurface(tvalgametype, NULL, back2, &rtmp);
				if(gametype==1){
					puttext(&tvaltailley, diffi[difficulter], 20, 0, 0, 0);
					setrect(&rtmp, 600, 225, 0, 0);
					SDL_BlitSurface(carredifficulter, NULL, back2, &rtmp);
					setrect(&rtmp, 100, 230, 0, 0);
					SDL_BlitSurface(tdifficulter, NULL, back2, &rtmp);
					setrect(&rtmp, 630, 230, 0, 0);
					SDL_BlitSurface(tvaltailley, NULL, back2, &rtmp);
					setrect(&rtmp, 805, 225, 0, 0);
					SDL_BlitSurface(iup.image, NULL, back2, &rtmp);
				
					setrect(&rtmp, 560, 225, 0, 0);
					SDL_BlitSurface(idown.image, NULL, back2, &rtmp);

				}
			}
			
			
		}
		if((SDL_GetTicks() - startticks) >= 10)
		{	
			setrect(&rtmp, 0, 0, 0, 0);
			SDL_BlitSurface(back2, NULL, screen, &rtmp);
			affbouton(&bok);
			if(option){
				affbouton(&boption1);
			}
			else{
				affbouton(&boption2);
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
			sprintf(cfps, "%d fps", fps);
			puttext(&tfps, cfps, 16, 160, 0, 0);
			fps = 0;
		}
		setrect(&rtmp, 1100, 10, 0, 0);
		SDL_BlitSurface(tfps, NULL, screen, &rtmp);

		

		SDL_Flip(screen);


	}
	SDL_FreeSurface(tnewgame);SDL_FreeSurface(tformegrid);SDL_FreeSurface(tvalformegrid);SDL_FreeSurface(carreforme);SDL_FreeSurface(back2);
	SDL_FreeSurface(ttaillex);SDL_FreeSurface(ttailley);SDL_FreeSurface(carretaillex);SDL_FreeSurface(carretailley);
	SDL_FreeSurface(tvaltaillex);SDL_FreeSurface(tvaltailley);SDL_FreeSurface(tvalmodejeux);SDL_FreeSurface(tdifficulter);
	SDL_FreeSurface(ttaillepiecemax); SDL_FreeSurface(ttaillepiecemin); SDL_FreeSurface(ttaillevalmax); SDL_FreeSurface(ttaillevalmin); SDL_FreeSurface(tmodejeux);
	SDL_FreeSurface(carremax); SDL_FreeSurface(carremin);SDL_FreeSurface(carremode);SDL_FreeSurface(carregametype);SDL_FreeSurface(carredifficulter);
	SDL_FreeSurface(tvalgametype);SDL_FreeSurface(tgametype);
	SDL_FreeSurface(iup.image);SDL_FreeSurface(idown.image);
	freebouton(bok);freebouton(boption1);freebouton(boption2);
	return(etat);

}

/**
 * \fn       void chargebacknewgame ()
 * \brief    Fonction d'affichage du fond du menu newgame
 * \details  Affichage des éléments du fond d'écran du menu newgame
 * \param    void
 * \return   void
 */
void chargebacknewgame(int option){
	setrect(&rtmp, 0, 0, 0, 0);
	SDL_BlitSurface(fond.image, NULL, back, &rtmp);

	setrect(&rtmp, 200, 25, 0, 0);
	SDL_BlitSurface(tnewgame, NULL, back, &rtmp);

	if(option==0){
		setrect(&rtmp, 600, 140, 0, 0);
		SDL_BlitSurface(carreforme, NULL, back, &rtmp);


		setrect(&rtmp, 100, 150, 0, 0);
		SDL_BlitSurface(tformegrid, NULL, back, &rtmp);

		setrect(&rtmp, 805, 145, 0, 0);
		SDL_BlitSurface(iup.image, NULL, back, &rtmp);

		setrect(&rtmp, 560, 145, 0, 0);
		SDL_BlitSurface(idown.image, NULL, back, &rtmp);

		setrect(&rtmp, 600, 210, 0, 0);
		SDL_BlitSurface(carretaillex, NULL, back, &rtmp);

		setrect(&rtmp, 705, 215, 0, 0);
		SDL_BlitSurface(iup.image, NULL, back, &rtmp);

		setrect(&rtmp, 560, 215, 0, 0);
		SDL_BlitSurface(idown.image, NULL, back, &rtmp);

		setrect(&rtmp, 600, 360, 0, 0);
		SDL_BlitSurface(carremax, NULL, back, &rtmp);
		setrect(&rtmp, 600, 440, 0, 0);
		SDL_BlitSurface(carremin, NULL, back, &rtmp);

		setrect(&rtmp, 100, 370, 0, 0);
		SDL_BlitSurface(ttaillepiecemax, NULL, back, &rtmp);
		setrect(&rtmp, 100, 450, 0, 0);
		SDL_BlitSurface(ttaillepiecemin, NULL, back, &rtmp);

		setrect(&rtmp, 705, 370, 0, 0);
		SDL_BlitSurface(iup.image, NULL, back, &rtmp);
		setrect(&rtmp, 560, 370, 0, 0);
		SDL_BlitSurface(idown.image, NULL, back, &rtmp);
		setrect(&rtmp, 705, 450, 0, 0);
		SDL_BlitSurface(iup.image, NULL, back, &rtmp);
		setrect(&rtmp, 560, 450, 0, 0);
		SDL_BlitSurface(idown.image, NULL, back, &rtmp);

		setrect(&rtmp, 600, 520, 0, 0);
		SDL_BlitSurface(carremode, NULL, back, &rtmp);
		setrect(&rtmp, 100, 530, 0, 0);
		SDL_BlitSurface(tmodejeux, NULL, back, &rtmp);
		setrect(&rtmp, 855, 530, 0, 0);
		SDL_BlitSurface(iup.image, NULL, back, &rtmp);
		setrect(&rtmp, 560, 530, 0, 0);
		SDL_BlitSurface(idown.image, NULL, back, &rtmp);

	}
	else{
		setrect(&rtmp, 600, 140, 0, 0);
		SDL_BlitSurface(carregametype, NULL, back, &rtmp);


		setrect(&rtmp, 100, 150, 0, 0);
		SDL_BlitSurface(tgametype, NULL, back, &rtmp);

		setrect(&rtmp, 805, 145, 0, 0);
		SDL_BlitSurface(iup.image, NULL, back, &rtmp);

		setrect(&rtmp, 560, 145, 0, 0);
		SDL_BlitSurface(idown.image, NULL, back, &rtmp);
	}
	

}
