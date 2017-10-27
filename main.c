#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro_opengl.h>

#include "al_engine.h"
engine *new_engine;
vector pos;
int x=300;
int y=300;

int main() {
		new_engine = createEngine(new_engine);
		engineInit(new_engine,"ohWindow myWindow",600,600,0,0,0,72);
		float r_x=0.0;
		float r_y=0.0;


		while(new_engine->exit_status) {
				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}
				clearDisplay(0,0,0);
				if(new_engine->focused) {
						text(255,255,255, 200,200, "Dog", new_engine);
						circle(new_engine->width/2,new_engine->height/2,(new_engine->width+new_engine->height)/50,255,255,255,10);
				}
				updatedisplay(60);

		}

		engineQuit(new_engine);
		return 0;
}
