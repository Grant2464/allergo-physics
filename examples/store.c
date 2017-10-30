#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro_opengl.h>
#include <allegro5/allegro_image.h>
#include "core/graphics.h"

ALLEGRO_BITMAP *image;

engine * new_engine;



int main(){
		new_engine = createEngine(new_engine);

		engineInit(new_engine,"ohWindow myWindow",1000,1000,FIXED,0,0,0,72);
		al_init_image_addon();
		image = al_load_bitmap("data/speech_bubble.png");

		int x=0;
		int y=0;
		while(new_engine->exit_status) {
				eventCheck(new_engine);


				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}


				clearDisplay(0,0,0);
				al_draw_scaled_bitmap(image,0,0,512,512,0,0,400,400,ALLEGRO_FLIP_HORIZONTAL);
				text("Hello",190,30, 0,0,0, new_engine); //5
				text("I superdup",190,110, 0,0,0, new_engine); //9
				text("enjoy the",190,190, 0,0,0, new_engine); //9
				text("dog",190,270, 0,0,0, new_engine); //2

				updatedisplay(60);

				x++,y++;
		}
		al_destroy_bitmap(image);

		engineQuit(new_engine);
		return 0;
}
