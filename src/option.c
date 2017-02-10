#include "option.h"

//SDL_SetAlpha(zozor, SDL_SRCALPHA, 128);  transparence
SDL_Surface *toption,*tvolume, *carrevolume, *tvolumelv, *tost, *tchanson, *carrechanson;

Image sonup, sondown, reset;
char cvolume[10];
int up;
int down;


/**
 * \fn       int option ()
 * \brief    Fonction de gestion de l'écran des options du jeu.
 * \details  Focntion gérant l'intégralité de l'écran des options du jeu, en faisant appel aux différentes fonctions de gestion des paramètres.
 * \return   Renvoie la valeur de la variable locale 'etat', valant systématiquement 0 à l'arrêt de la fonction.
*/
int option (){
	Bouton bmuteon,bmuteoff,bquit2;
	toption=NULL;tvolume=NULL; carrevolume=NULL; tvolumelv=NULL; tost=NULL; tchanson=NULL;
	int loop=1;
	int etat=1;
	puttext(&toption, "OPTION", 60, 255, 255, 255);
	puttext(&tvolume, "volume musique :", 30, 0, 0, 0);
	setrect(&rtmp, 0, 0, 0, 0);
	puttext(&tost, "Musique :", 30, 0, 0, 0);
	
	

	sonup=initimage("BMP/icone-flechedroite.png",38, 38);
	sondown=initimage("BMP/icone-flechegauche.png",38, 38);
	reset=initimage("BMP/reset.png",114,50);
	bmuteon=initbouton(500,200,200,75, "Mute ON",0, 255, 0);
	bmuteoff=initbouton(500,200,200,75, "Mute OFF",  255, 0, 0);
	bquit2=initbouton(500,600,200,75, "Quitter",  255, 255, 255);
	puttext(&tvolumelv, "0", 20, 0, 0, 0);
	//????????????????
	carrevolume = SDL_AllocSurface(SDL_HWSURFACE, 150, 60, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 150, 60);
	SDL_FillRect(carrevolume, &rtmp, SDL_MapRGB(screen->format, 10, 200, 10));
	SDL_SetAlpha(carrevolume, SDL_SRCALPHA, 128);

	carrechanson = SDL_AllocSurface(SDL_HWSURFACE, 312, 60, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, 312, 60);
	SDL_FillRect(carrechanson, &rtmp, SDL_MapRGB(screen->format, 100, 10, 100));
	SDL_SetAlpha(carrechanson, SDL_SRCALPHA, 128);

	chargebackoption();
	SDL_BlitSurface(back, NULL, screen, NULL);
	//????????????????

	if(!lock) Mix_FadeInMusic(Playlist[2],-1,2000);


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
				 		if(testbouton(bmuteon)&& mute && !clickdroit){
				 			mute=0;
				 			Mix_VolumeMusic(Volume);
				 		}
				 		else if(testbouton(bmuteoff)&& !mute && !clickdroit){
				 			mute=1;
							Mix_VolumeMusic(0);
				 		}
				 		if(testbouton(bquit2) && !clickdroit){
				 			loop=0;
				 		} 
				 		// ??????
				 		if(souris.x>800 && souris.x<838 && souris.y>320 && souris.y<358 && !clickdroit){
				 			plusMusic();
				 							 		}
				 		if(souris.x>600 && souris.x<638 && souris.y>320 && souris.y<358 && !clickdroit){
				 			minusMusic();
				 		}
				 		// ??????
				 		if(souris.x>950 && souris.x<988 && souris.y>410 && souris.y<448 && !clickdroit){
				 			Mix_HaltMusic();
				 			chanson=(chanson+1)%5;
				 			Mix_FadeInMusic(Playlist[chanson],-1,2000);
				 			lock=1;
				 		}
				 		if(souris.x>600 && souris.x<638 && souris.y>410 && souris.y<448 && !clickdroit){
				 			Mix_HaltMusic();
				 			chanson=(chanson-1+5)%5;
				 			Mix_FadeInMusic(Playlist[chanson],-1,2000);
				 			lock=1;
				 		}
				 		if(souris.x>1000 && souris.x<1114 && souris.y>575 && souris.y<625 && !clickdroit){
				 			Mix_HaltMusic();
				 			chanson=2;
				 			while (Volume/8 != 8) {
				 				if (Volume/8<8) {
				 				plusMusic();
				 				}
				 				else {
				 					minusMusic();
				 				}
				 			}
				 			mute=0;
				 			Mix_FadeInMusic(Playlist[chanson],-1,2000);
				 			lock=0;
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
			SDL_BlitSurface(back, NULL, screen, NULL);
			affchanson();
			if (mute){
				affbouton(&bmuteon);
			}
			else{
				affbouton(&bmuteoff);
			}	
			
			affbouton(&bquit2);
			sprintf(cvolume, "%d", Volume/8);
			puttext(&tvolumelv, cvolume, 20, 0, 0, 0);
			setrect(&rtmp, 710, 330, 0, 0);
			SDL_BlitSurface(tvolumelv, NULL, screen, &rtmp);



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
	SDL_FreeSurface(toption);SDL_FreeSurface(tvolume);SDL_FreeSurface(tvolumelv);SDL_FreeSurface(carrevolume);
	SDL_FreeSurface(sonup.image);SDL_FreeSurface(sondown.image);SDL_FreeSurface(reset.image);SDL_FreeSurface(tchanson);SDL_FreeSurface(tost);
	freebouton(bmuteon);freebouton(bmuteoff);freebouton(bquit2);
	return(etat);

}

/**
 * \fn       void chargebackoption ()
 * \brief    Affichage du menu option.
 * \details  Affiche l'intégralité du fond d'écran du menu des options, en faisant un appel des fonctions 'SDL_BlitSurface' et 'setrect'.
 * \return   void
*/
void chargebackoption(){
	setrect(&rtmp, 0, 0, 0, 0);
	SDL_BlitSurface(fond.image, NULL, back, &rtmp);

	setrect(&rtmp, 645, 310, 0, 0);
	SDL_BlitSurface(carrevolume, NULL, back, &rtmp);

	setrect(&rtmp, 645, 400, 0, 0);
	SDL_BlitSurface(carrechanson, NULL, back, &rtmp);

	setrect(&rtmp, WIDTH/2-100, 100, 0, 0);
	SDL_BlitSurface(toption, NULL, back, &rtmp);

	setrect(&rtmp, 240, 320, 0, 0);
	SDL_BlitSurface(tvolume, NULL, back, &rtmp);

	setrect(&rtmp, 800, 320, 0, 0);
	SDL_BlitSurface(sonup.image, NULL, back, &rtmp);

	setrect(&rtmp, 600, 320, 0, 0);
	SDL_BlitSurface(sondown.image, NULL, back, &rtmp);

	setrect(&rtmp, 950, 410, 0, 0);
	SDL_BlitSurface(sonup.image, NULL, back, &rtmp);

	setrect(&rtmp, 600, 410, 0, 0);
	SDL_BlitSurface(sondown.image, NULL, back, &rtmp);

	setrect(&rtmp, 350, 400, 0, 0);
	SDL_BlitSurface(tost, NULL, back, &rtmp);

	setrect(&rtmp, 1000, 575, 0, 0);
	SDL_BlitSurface(reset.image, NULL, back, &rtmp);

}

/**
 * \fn       void affchanson()
 * \brief    Affichage du nom de la piste.
 * \details  Affichage du nom de la piste actuellement en cours de lecture, dans le menu Option. Les fonctions 'SDL_BlitSurface', 'setrect' et 'puttext' sont utilisées.
 * \return   void
*/
void affchanson() {
	if (chanson==0){
		setrect(&rtmp, 645, 410, 0, 0);
		SDL_BlitSurface(tchanson, NULL, screen, &rtmp);
		puttext(&tchanson, "Nice Music", 30, 0, 0, 0);
	}
	if (chanson==1) {
		setrect(&rtmp, 645, 410, 0, 0);
		SDL_BlitSurface(tchanson, NULL, screen, &rtmp);
		puttext(&tchanson, "Disfigure", 30, 0, 0, 0);	
	}
	if (chanson==2) {
		setrect(&rtmp, 645, 410, 0, 0);
		SDL_BlitSurface(tchanson, NULL, screen, &rtmp);
		puttext(&tchanson, "Mexican Hat...", 30, 0, 0, 0);
	}
	if (chanson==3) {
		setrect(&rtmp, 645, 410, 0, 0);
		SDL_BlitSurface(tchanson, NULL, screen, &rtmp);
		puttext(&tchanson, "Seasons Die...", 30, 0, 0, 0);
	}
	if (chanson==4) {
		setrect(&rtmp, 645, 410, 0, 0);
		SDL_BlitSurface(tchanson, NULL, screen, &rtmp);
		puttext(&tchanson, "Dear You", 30, 0, 0, 0);
	}

}
