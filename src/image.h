#ifndef LOL
#define LOL

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include <errno.h>

int WIDTH;
int HEIGHT;
int BPP;

SDL_Event event;

SDL_Color textcolor;
TTF_Font *font;


SDL_Surface *tfps, *tstart, *screen, *back;
SDL_Rect rtmp;  //rame tmp

SDL_Rect souris;

int clickdroit;

Uint32 colorkey;  //int sur 32 bit

int fps;
int startticks, startticksf;

char gticks;
char gticksf;
char cfps[100];  //string

Mix_Music* Playlist[5];
int Volume;
int mute;
int lock;
int chanson;

typedef struct{
	int w;  //longueur
	int h;  //largeur
	SDL_Surface* image;
	SDL_Rect* sprite;
}Image;

typedef struct {
	int x;
	int y;
	int w;
	int h;
	SDL_Surface* im;
	SDL_Surface* im2;
	int tauxtransparence;
}Bouton;

Image fond; 
int formegrid;
int xtaillegrid;
int ytaillegrid;
int hexMax;
int hexMin;
int lol;
int gametype;
int difficulter;

int p1,p2,p3,positionlistepiece,piecemv,hexamv;

void puttext(SDL_Surface **surface, char *text, int size, int r, int g, int b);
void setrect(SDL_Rect *rect, int x, int y, int w, int h);
void aplliquesprite( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
Image initimage(char* adresse,int w,int h);

Bouton initbouton(int x, int y, int w, int h, char* text, int r, int v, int b);
void affbouton(Bouton *b);
int testbouton(Bouton b);
void freebouton(Bouton b);
int chargeMusic();
void libMusic();
void plusMusic ();
void minusMusic ();


#endif
