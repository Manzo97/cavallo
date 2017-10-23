/*g++ allegro.cc -o allegro `pkg-config --cflags --libs allegro-5 allegro_color-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_ttf-5`*/

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"
#include <iostream>
#include "struttureDati.h"


const float FPS = 60;
//const char *image = "tux.png";
enum MYKEYS {
   KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE
};

int main(int argc, char **argv)
{
   int SCREEN_W = 0;
   int SCREEN_H = 0;
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   ALLEGRO_BITMAP *bgimg = NULL;
   Giocatore player;
   Background bg;
   bool key[5] = { false, false, false, false, false };
   bool redraw = true;
   bool doexit = false;
   bool right = false;
   bool left = false;
   bool jump = false;


   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   if(!al_install_keyboard()) {
      fprintf(stderr, "failed to initialize the keyboard!\n");
      return -1;
   }

   if(!al_init_image_addon()){
     fprintf(stderr, "failed to initialize image addon!\n");
     return -1;
   }

   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }
   bgimg = al_load_bitmap("immagini/sfondi1.png");
   SCREEN_W = al_get_bitmap_width(bgimg)-200;
   SCREEN_H = al_get_bitmap_height(bgimg);
   InitBackground(bg, 0, 0, 5, 0, al_get_bitmap_width(bgimg), al_get_bitmap_height(bgimg), -1, 1, bgimg);
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      al_destroy_timer(timer);
      return -1;
   }
   InitGiocatore(player, SCREEN_W/2, (SCREEN_H/3)*2,50,50);
   player.image = new ALLEGRO_BITMAP * [player.maxFrame];
   LoadImmaginiG(player);
   for(int i=0;i < player.maxFrame;i++)
   {
      al_convert_mask_to_alpha(player.image[i],al_map_rgb(0,0,0));
      al_convert_mask_to_alpha(player.image[i],al_map_rgb(255,255,255));
   }

   al_set_target_bitmap(al_get_backbuffer(display));
   event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   //al_clear_to_color(al_map_rgb(0,0,0));

   al_flip_display();
   al_start_timer(timer);

   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);

      if(ev.type == ALLEGRO_EVENT_TIMER) {
        UpdateBackground(bg);
        if(key[KEY_DOWN] && player.posY <= (SCREEN_H/3) * 2.5) {
          key[KEY_UP] = false;
          key[KEY_SPACE] = false;
          if((((SCREEN_H/3) * 2.5)-al_get_bitmap_height(player.image[0]))-player.posY > 15)
            player.posY += 15;
          else
            player.posY += (((SCREEN_H/3) * 2.5)-al_get_bitmap_height(player.image[0]))-player.posY;
          if (player.posY>=((SCREEN_H/3) * 2.5)-al_get_bitmap_height(player.image[0]))
            key[KEY_DOWN] = false;
            jump = false;
        }
         if(key[KEY_UP] && player.posY >= SCREEN_H/10) {
           player.posY -= 10;
         	if (player.posY<=SCREEN_H/10) {
         		key[KEY_UP] = false;
         		key[KEY_DOWN]=true;
          }
         }
         if(key[KEY_SPACE] && player.posY >= SCREEN_H/3) {
           player.posY -= 10;
         	if (player.posY<=SCREEN_H/3) {
         		key[KEY_SPACE] = false;
         		key[KEY_DOWN]=true;
          }
         }
         if(key[KEY_RIGHT]) {
           player.posX += 4.0;
         }
         if(key[KEY_LEFT]) {
           player.posX -= 4.0;
         }

         redraw = true;
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
         break;
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               jump = true;
               key[KEY_UP] = true;
               break;

            case ALLEGRO_KEY_SPACE:
               jump = true;
               key[KEY_SPACE] = true;
               break;

            case ALLEGRO_KEY_LEFT:
               left = true;
               key[KEY_LEFT] = true;
               break;

            case ALLEGRO_KEY_RIGHT:
               right = true;
               key[KEY_RIGHT] = true;
               break;
         }
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
           case ALLEGRO_KEY_UP:
              jump = false;
              key[KEY_DOWN] = true;
              break;

            case ALLEGRO_KEY_SPACE:
              jump = false;
               key[KEY_DOWN] = true;
               break;

            case ALLEGRO_KEY_LEFT:
               left = false;
               key[KEY_LEFT] = false;
               break;

            case ALLEGRO_KEY_RIGHT:
               right = false;
               key[KEY_RIGHT] = false;
               break;

            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;
         }
      }

      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
         al_clear_to_color(al_map_rgb(0,0,0));
         DrawBackground(bg);
         if(right)
         {
           if(++player.frameCount >= player.frameDelay)
             {
               if(++player.curFrame>=player.maxFrame-14)
                 player.curFrame= 0;
               player.frameCount=0;
             }
           al_draw_bitmap(player.image[player.curFrame],player.posX,player.posY,0);
         }
         else if(left)
         {
           if(player.curFrame < 14)
            player.curFrame = 14;

           if(++player.frameCount >= player.frameDelay)
             {
               if(++player.curFrame>=player.maxFrame)
                 player.curFrame= 14; //rimettere il frame da sinistra (13)
               player.frameCount=0;
             }
           al_draw_bitmap(player.image[player.curFrame],player.posX,player.posY,0);
         }
         //else if(jump || key[KEY_DOWN])al_draw_bitmap(player.image[3],player.posX,player.posY,0);
         else
         al_draw_bitmap(player.image[player.curFrame],player.posX,player.posY,0);
         al_flip_display();
      }
   }
   for(int i = 0; i<player.maxFrame; i++)
    al_destroy_bitmap(player.image[i]);
   al_destroy_bitmap(bg.image);
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);

   return 0;
}
