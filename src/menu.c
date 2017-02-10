#include "menu.h"
#include "jeux.h"

//SDL_SetAlpha(zozor, SDL_SRCALPHA, 128);  transparence
SDL_Surface *tmenu;
Bouton bplay,bquit,boption;

int menu (){
	int tmp=99;
	tmenu=NULL;
	int loop=1;
	int etat=1;
	tmenu=NULL;
	puttext(&tmenu, "MENU", 60, 255, 255, 255);

	SDL_BlitSurface(back, NULL, screen, NULL);
	bplay=initbouton(500,200,200,75, "Play",255, 255, 255);
	boption=initbouton(500,400,200,75, "Option",  255, 255, 255);
	bquit=initbouton(500,600,200,75, "Quitter",  255, 255, 255);
	chargebackmenu();

	if(!lock) Mix_FadeInMusic(Playlist[1], -1, 3000);

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
						if(Volume==0)
						{
							Volume=64;
							mute=0;
							Mix_VolumeMusic(Volume);
						}
						else
						{
							Volume=0;
							mute=1;
							Mix_VolumeMusic(Volume);
						}
					}
					break;
				 case SDL_MOUSEBUTTONUP:
				 	if (event.button.button == SDL_BUTTON_LEFT) {
				 		if(testbouton(bplay) && !clickdroit){
				 			if(!lock) Mix_HaltMusic();
				 			tmp=99;
				 			gametype=0;
				 			while(tmp==99){
				 				tmp=jeux();
				 			}
				 			printf("tmp=%d\n",tmp);
				 			if(tmp==0){
				 				loop=0;
				 				etat=0;
				 			}
				 			if(!lock) Mix_FadeInMusic(Playlist[1], -1, 3000);
				 			chargebackmenu();

				 		}
				 		if(testbouton(boption) && !clickdroit){
				 			if(!lock) Mix_HaltMusic();
				 			if(!option()){
				 				loop=0;
				 				etat=0;
				 			}
				 			if(!lock) Mix_FadeInMusic(Playlist[1], -1, 3000);
				 			chargebackmenu();

				 		}
				 		if(testbouton(bquit) && !clickdroit){
				 			loop=0;
				 			etat=0;
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
			affbouton(&bplay);
			affbouton(&bquit);
			affbouton(&boption);
			




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
	SDL_FreeSurface(tmenu);
	freebouton(bplay);freebouton(bquit);freebouton(boption);
	return(etat);
}

/**
 * \fn       vopid chargebackmenu ()
 * \brief    Fonction d'affichage du fond du menu
 * \details  Fonction permettant d'afficher le fond d'écran du menu du jeu
 * \param    void
 * \return   void
 */
void chargebackmenu(){
	setrect(&rtmp, 0, 0, 0, 0);
	SDL_BlitSurface(fond.image, NULL, back, &rtmp);

	setrect(&rtmp, WIDTH/2-100, 100, 0, 0);
	SDL_BlitSurface(tmenu, NULL,  back, &rtmp);



}
