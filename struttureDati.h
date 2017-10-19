#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <iostream>
using namespace std;

struct Giocatore
{
  float posX,posY,width,height;
  ALLEGRO_BITMAP *immagine;
  int curFrame; //frame corrente
  int maxFrame; // Numero immagini per l'animazione
  int frameCount;
  int frameDelay; //ritardo animazione--forse non utile--
  ALLEGRO_BITMAP **image; //array che contine le immagini del drago
};
struct Background{
//Posizione iniziale
	float posX;
	float posY;
//Indicatore della velocità
	float velX;
	float velY;
//Indicatore della direzione
	int dirX;
	int dirY;

	int width;
	int height;
 //Puntatore per un immagine di tipo ALLEGRO_BITMAP
	ALLEGRO_BITMAP *image;
};
struct Piattaforme
{
  /*
   *
   Work in Progress
   *
   */
};

void InitGiocatore(Giocatore&,float, float, float, float);
void LoadImmaginiG(Giocatore&);
void InitBackground(Background &, float , float , float , float ,int , int , int , int , ALLEGRO_BITMAP *);
void UpdateBackground(Background &);
void DrawBackground(Background &);
