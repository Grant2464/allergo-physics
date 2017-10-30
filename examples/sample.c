#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro_opengl.h>
#include "core/graphics.h"

engine *new_engine;

int main(){

		new_engine = createEngine(new_engine);
		engineInit(new_engine,"ohWindow myWindow",600,600,FIXED,0,0,0,72);

		while(new_engine->exit_status) {

				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}

				clearDisplay(0,0,0);
				updatedisplay(60);
		}

		engineQuit(new_engine);
		return 0;
}
