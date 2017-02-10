#include "image.h"

/**
 * \fn       void puttext(SDL_Surface **surface, char *text, int size, int r, int g, int b)
 * \brief    écrie du text dans l'image surface
 * \details  
 * \param    SDL_Surface **surface: Un pointeur vers une image
 * \param    char *text: le texte qu' on veut ècrir
 * \param    int size: taille de la police
 * \param    int r: taux de rouge
 * \param    int g: taux de vert
 * \param    int b: taux de bleu
 * \return   void
 */
void puttext(SDL_Surface **surface, char *text, int size, int r, int g, int b)
{
	textcolor.r = r;
	textcolor.g = g;
	textcolor.b = b;
	font = TTF_OpenFont("Roman.ttf", size);
	if(surface!=NULL){
		SDL_FreeSurface(*surface);
	}
	*surface = TTF_RenderText_Solid(font, text, textcolor);
	TTF_CloseFont(font);
}

/**
 * \fn       void setrect(SDL_Rect *rect, int x, int y, int w, int h)
 * \brief    entre les valeurs x, y, x ,h dans le SDL_rect
 * \details  
 * \param    SDL_Rect *rect: le SDL_rectangle qu'on veut modifier
 * \param    int x: position x du rectangle
 * \param    int y: position y du rectangle
 * \param    int w: largeur du rectangle
 * \param    int h: hauteur du rectangle
 * \return   void
 */
void setrect(SDL_Rect *rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

/**
 * \fn       Image initimage(char* adresse,int w,int h)
 * \brief    initialise une image
 * \details  charge une image et sauvegarde la hauteur et la largeur de l'image
 * \param    char* adresse: l'adresse de l'image
 * \param    int w: largeur du rectangle
 * \param    int h: hauteur du rectangle
 * \return   on renvoie un pointeur vers une image dont la mémoire a été alouée
 */
Image initimage(char* adresse,int w,int h){
	Image image;
	SDL_Surface *im;
	if((im = IMG_Load(adresse))==NULL){
		perror("IMG_Load");
		printf("erreur de lecture %s\n",adresse);
		exit(1);
	}
	image.w=w;
	image.h=h;
	image.image=im;
	image.sprite=NULL;
	return(image);
}

/**
 * \fn       Bouton initbouton(int x, int y, int w, int h, char* text, int r, int v, int b)
 * \brief    initialise un bouton
 * \details  crée un bouton a la position x y et de largeur w et hauteur h avec du text a l'interieur et avec une sertaine couleur
 * \param    char* adresse: l'adresse de l'image
 * \param    int x: position x du bouton
 * \param    int y: position y du bouton
 * \param    int w: largeur du bouton
 * \param    int h: hauteur du bouton
 * \param    char* text: text du bouton
 * \param    int r: taux de rouge
 * \param    int g: taux de vert
 * \param    int b: taux de bleu
 * \return   on renvoie un bouton dont la mémoire à été allouée
 */
Bouton initbouton(int x, int y, int w, int h, char* text, int r, int v, int b){
	SDL_Surface *im, *ttext,*im2;
	ttext=NULL;
	im = SDL_AllocSurface(SDL_HWSURFACE, w, h, BPP, 0, 0, 0, 0);
	im2 = SDL_AllocSurface(SDL_HWSURFACE, w, h, BPP, 0, 0, 0, 0);
	setrect(&rtmp, 0, 0, w, h);
	SDL_FillRect(im, &rtmp, SDL_MapRGB(screen->format, r, v, b));
	puttext(&ttext, text, 25, 0, 0, 0);
	setrect(&rtmp, 10, 10, 0, 0);
	SDL_BlitSurface(ttext, NULL, im, &rtmp);
	SDL_FreeSurface(ttext);
	Bouton bout;
	bout.x=x;
	bout.y=y;
	bout.w=w;
	bout.h=h;
	bout.im=im;
	bout.im2=im2;
	bout.tauxtransparence=100;
	return(bout);
}

/**
 * \fn       void affbouton(Bouton *b)
 * \brief    affiche le bouton
 * \details  affiche un bouton de plus en plus opaque en fonction du temps que le curseur est sur le bouton
 * \param    Bouton *b: le bouton qu'on cherche a afficher
 * \return   void
 */
void affbouton(Bouton *b){
	if(souris.x>b->x && souris.x<b->x+b->w && souris.y>b->y && souris.y<b->y+b->h){
		if(b->tauxtransparence<255){
			b->tauxtransparence=b->tauxtransparence+5;
		}
	}
	else{
		b->tauxtransparence=100;
	}
	setrect(&rtmp,0 , 0, 0, 0);
	SDL_BlitSurface(b->im, NULL, b->im2, &rtmp);
	SDL_SetAlpha(b->im2, SDL_SRCALPHA, b->tauxtransparence);
	setrect(&rtmp, b->x, b->y, 0, 0);
	SDL_BlitSurface(b->im2, NULL, screen, &rtmp);
}


/**
 * \fn       testbouton(Bouton b)
 * \brief    test si le curseur est sur le bouton
 * \details  
 * \param    Bouton *b: le bouton qu'on cherche a tester
 * \return   renvoie un booléen
 */
int testbouton(Bouton b){
	if(souris.x>b.x && souris.x<b.x+b.w && souris.y>b.y && souris.y<b.y+b.h){
		return(1);
	}
	return(0);

}

/**
 * \fn       void freebouton(Bouton b)
 * \brief    libère la memoire allouée par le bouton
 * \details  
 * \param    Bouton *b: le bouton qu'on cherche a free
 * \return   void
 */
void freebouton(Bouton b){
	SDL_FreeSurface(b.im2);
	SDL_FreeSurface(b.im);

}

/**
 * \fn       int chargeMusic ()
 * \brief    Cette fonction alloue la mémoire aux pistes musicales.
 * \details  Cette focntion remplit un tableau statique de pointeurs, tout en les testant, quittant le programme dans le cas d'une erreur. Elle fait appel à la focntion de SDLMixer 'Mix_LoadMUS'
 * \param    void
 * \return   Renvoie un booléen TRUE(1) si l'intégralité des pistes à été allouée, FALSE(0) sinon.
 */
int chargeMusic() {
	if ( (Playlist[0]=Mix_LoadMUS("sound_samples/mus1.mp3"))==NULL ) {return 0;}
	if ( (Playlist[1]=Mix_LoadMUS("sound_samples/mus2.mp3"))==NULL ) {return 0;}
	if ( (Playlist[2]=Mix_LoadMUS("sound_samples/mex_hat_dance.mp3"))==NULL ) {return 0;}
	if ( (Playlist[3]=Mix_LoadMUS("sound_samples/amazarashi_seasons_die_one_after_another.mp3"))==NULL ) {return 0;}
	if ( (Playlist[4]=Mix_LoadMUS("sound_samples/Dear_you.mp3"))==NULL ) {return 0;}
	return 1;
}

/**
 * \fn       void libMusic ()
 * \brief    Cette fonction libère la mémoire allouée aux pointeurs des pistes musicales.
 * \details  Cette fonction libère les pointeurs alloués par 'chargeMusic' dans le tableau statique de pointeurs. Elle fait appel la fonction de SDLMixer 'Mix_FreeMusic'.
 * \param    void
 * \return   void
 */
void libMusic () {
	Mix_FreeMusic(Playlist[0]);
	Mix_FreeMusic(Playlist[1]);
	Mix_FreeMusic(Playlist[2]);
	Mix_FreeMusic(Playlist[3]);
	Mix_FreeMusic(Playlist[4]);
}

/**
 * \fn       void plusMusic ()
 * \brief    Cette fonction augmente le volume.
 * \details  Cette fonction augmente le volume du jeu, en faisant appel à la fonction interne de SDLMixer 'Mix_VolumeMusic' et en modifiant la variable globale 'Volume'.
 * \param    void
 * \return   void
 */
void plusMusic () {
	if (Volume<128) {
		Volume+=8;
		Mix_VolumeMusic(Volume);
	}
}

/**
 * \fn       void minusMusic ()
 * \brief    Cette fonction diminue le volume.
 * \details  Cette fonction augmente le volume du jeu, en faisant appel à la fonction interne de SDLMixer 'Mix_VolumeMusic' et en modifiant la variable globale 'Volume'.
 * \param    void
 * \return   void
 */
void minusMusic () {
	if (Volume>0) {
		Volume-=8;
		Mix_VolumeMusic(Volume);
	}
}

/*
Les musiques se traitent dans des pointeurs type : Mix_Music *musique;

Charger une musique : musique = Mix_LoadMUS("musique.'format'")

Libérer le pointeur : Mix_FreeMusic (musique)

Jouer une musique : int Mix_PLayMusic(Mix_Music *musique, int loops) loops=-1 pour un nombre infini de boucles

Volume musique : Mix_VolumeMusic(int volume) => 0 pour mute, MIX_MAX_VOLUME pour max, de base on va initialiser a MIX_MAX_VOLUME/2

Pause musique : Mix_PauseMusic()

Reprendre musique : Mix_ResumeMusic

Redémarrer musique : Mix_RewindMusic()

Arrêter musique : Mix_HaltMusic()

Savoir si musique en pause on vérifie si Mix_PausedMusic()==1

Savoir si musique en train de jouer on vérifie si Mix_PlayingMusic()==1

Ces fonctions agissent sur la musique en cours, à priori il faut peut-être utiliser une fonction pour choisir la musique (VIVA OPTIONS !! :p)
*/
