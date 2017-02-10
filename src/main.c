#include "image.h"
#include "menu.h"

void chargebackmain();
/*
typedef de Mix_Chunk { 
    int alloué ; 
    Uint8 * abuf ; 
    Uint32 Alen ; 
    Uint8 le volume ; / * Volume par échantillon, 0-128 * / 
} Mix_Chunk;
*/



char monprog[]= "HEXPUZZ"; //non du programme

char etatjeu= 0;

Image hexpuzz;
Image icone;

int test;
//SDL_Rect listesprite[ 14 ];     //sprite d'une image


/**
 * \fn       int main (int argc, char **argv)
 * \brief    Fonction principale du jeu.
 * \details  Fonction initialisant le jeu et les valeurs des différentes variables globales.
 * \param    int argc: Le nombre d'arguments passés au démarage du jeu.
 * \param    char **argv: le tableau de chaînes de caractères contenant les arguments passés au démarage du jeu.
 * \return   0
*/
int main()
{	//initialisation des valleur;
	WIDTH = 1200;
	HEIGHT = 700;
	BPP = 24;
	fps = 0;
	gticks = 0;
	gticksf = 0;
	clickdroit=0;
	Volume=64;
	chanson=2;
	lock=0;
	mute=0;
	tfps=NULL;
	tstart=NULL;
	formegrid=0;
	xtaillegrid=8;
	ytaillegrid=8;
	hexMax=5;
	hexMin=3;
	lol=1;
	gametype=0;
	difficulter=0;

	srand(time(NULL));
	int loop = 1;
	int clignotement=1;
	//-----------------------------------initialisation chargement SDL--------------------------------------------------

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)!=0)
    {
        printf("Initialisation impossible!!!");
        return 0;
    }
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1) {
    	printf("Erreur durant l'initialisation des sons!");
    	printf("%s", Mix_GetError());
    	return 0;
    }

    if ( !( chargeMusic() ) ) {
    	printf("Erreur de chargement de la musique\n");
    	return 0;
    }
    Mix_VolumeMusic(Volume);

	TTF_Init(); //taille écriture
	SDL_WM_SetCaption(monprog, NULL);
	icone=initimage("BMP/hexaicone2.png",0, 0);
	SDL_WM_SetIcon(icone.image, NULL);
    screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_DOUBLEBUF | SDL_HWSURFACE);
	

	fond=initimage("BMP/fondecran.png",1200, 750);
	hexpuzz=initimage("BMP/hexpuzz.png",900, 169);


	colorkey = SDL_MapRGB(screen->format, 255, 255, 255);
	back = SDL_AllocSurface(SDL_HWSURFACE, WIDTH, HEIGHT, BPP, 0, 0, 0, 0);
	puttext(&tfps, "0 fps", 16, 160, 0, 0);
	puttext(&tstart, "Appuyer sur SPACE pour jouer", 50, 255, 0, 0);
	//création du fond
	chargebackmain();

	if(screen==NULL) {
		loop = 0;
		printf("erreur on screen\n");
	}
	while(loop)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                	loop = 0;
                	break;
                case SDL_KEYDOWN:
                	if(event.key.keysym.sym == SDLK_ESCAPE) loop = 0;
					
					if(event.key.keysym.sym == SDLK_SPACE)
					{
						if(!menu())loop=0;
						chargebackmain();
					}
					break;
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
		if((SDL_GetTicks() - startticks) >= 500)
		{
			SDL_BlitSurface(back, NULL, screen, NULL);
			if(clignotement<3){
				setrect(&rtmp, WIDTH/2-450, 400, 0, 0);
				SDL_BlitSurface(tstart, NULL, screen, &rtmp);
				clignotement++;
			}
			else{
				clignotement=0;
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
	libMusic(Playlist);
	Mix_CloseAudio();
    SDL_Quit();
    SDL_FreeSurface(tfps);SDL_FreeSurface(back);SDL_FreeSurface(fond.image);SDL_FreeSurface(tstart);
    SDL_FreeSurface(hexpuzz.image); SDL_FreeSurface(icone.image);
    printf("Fin programme\n");
    return 0;
}

/**
 * \fn       void chargebackmain ()
 * \brief    Charge le fond d'écran de démarage du jeu.
 * \details  Charge le fodn d'écran de démarage du jeu.
 * \return   void
*/
void chargebackmain(){
	setrect(&rtmp, 0, 0, 0, 0);
	SDL_BlitSurface(fond.image, NULL, back, &rtmp);
	setrect(&rtmp, 100, 200, 0, 0);
	SDL_BlitSurface(hexpuzz.image, NULL, back, &rtmp);



}
