#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <iostream>
#include "struttureDati.h"
using namespace std;


void InitGiocatore(Giocatore &player,float x, float y, float width, float height)
{
  player.posX = x;
  player.posY = y;
  player.width = width;
  player. height = height;
  player.curFrame = 0;
  player.maxFrame = 28;
  player.frameCount = 0;
  player.frameDelay = 3;
}

void LoadImmaginiG(Giocatore &player)
{
  //non orizzontali
  player.image[0] = al_load_bitmap("immagini/0.png");
	player.image[1] = al_load_bitmap("immagini/1.png");
	player.image[2] = al_load_bitmap("immagini/2.png");
	player.image[3] = al_load_bitmap("immagini/3.png");
	player.image[4] = al_load_bitmap("immagini/4.png");
	player.image[5] = al_load_bitmap("immagini/5.png");
	player.image[6] = al_load_bitmap("immagini/6.png");
	player.image[7] = al_load_bitmap("immagini/7.png");
	player.image[8] = al_load_bitmap("immagini/8.png");
	player.image[9] = al_load_bitmap("immagini/9.png");
	player.image[10] = al_load_bitmap("immagini/10.png");
	player.image[11] = al_load_bitmap("immagini/11.png");
	player.image[12] = al_load_bitmap("immagini/12.png");
	player.image[13] = al_load_bitmap("immagini/13.png");
	//orizzontali

	player.image[14] = al_load_bitmap("immagini/0s.png");
	player.image[15] = al_load_bitmap("immagini/1s.png");
	player.image[16] = al_load_bitmap("immagini/2s.png");
	player.image[17] = al_load_bitmap("immagini/3s.png");
	player.image[18] = al_load_bitmap("immagini/4s.png");
	player.image[19] = al_load_bitmap("immagini/5s.png");
	player.image[20] = al_load_bitmap("immagini/6s.png");
	player.image[21] = al_load_bitmap("immagini/7s.png");
	player.image[22] = al_load_bitmap("immagini/8s.png");
	player.image[23] = al_load_bitmap("immagini/9s.png");
	player.image[24] = al_load_bitmap("immagini/10s.png");
	player.image[25] = al_load_bitmap("immagini/11s.png");
	player.image[26] = al_load_bitmap("immagini/12s.png");
	player.image[27] = al_load_bitmap("immagini/13s.png");

}

void InitBackground(Background &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image)
{
	back.posX = x;
	back.posY = y;
	back.velX = velx;
	back.velY = vely;
	back.width = width;
	back.height = height;
	back.dirX = dirX;
	back.dirY = dirY;
	back.image = image;
}
//Aggiorna la struttura
void UpdateBackground(Background &back)
{
	back.posX += back.velX * back.dirX;
	if(back.posX + back.width <= 0)
		back.posX = 0;
}
//funzione che disegna su schermo
void DrawBackground(Background & back)
{
	al_draw_bitmap(back.image, back.posX, back.posY, 0);
//Questa condizione fa si che le stelle vengano disegnate in loop
	if(back.posX + back.width < 1200)
		al_draw_bitmap(back.image, (back.posX + back.width)-65, back.posY, 0);

}
