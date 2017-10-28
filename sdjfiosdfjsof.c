#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_opengl.h>

#include "al_engine.h"
#define new_max(x,y) ((x) >= (y)) ? (x) : (y)
engine *new_engine;
vector pos;


int main() {



		new_engine = createEngine(new_engine);
		engineInit(new_engine,"ohWindow myWindow",600,600,0,0,0,72);
		float x=0.0;
		float y=0.0;
		float x_origin = 1;
		float y_origin = 1;
		float x_pos =0;
		float y_pos =0;

		while(new_engine->exit_status) {
				if(mouseButtonDown(0,new_engine)) {
						x = new_engine->mouse_pos.x;
						y = new_engine->mouse_pos.y;


				}
				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}


				if(mouseButtonUp(0,new_engine)) {
						x_origin = new_engine->mouse_pos.x;
						y_origin = new_engine->mouse_pos.y;
				}
				if(mouseMoving(new_engine) && mouseButtonDown(0,new_engine)) {
						x_origin = new_engine->mouse_pos.x;
						y_origin = new_engine->mouse_pos.y;
						x_pos+=x_origin-x;
						y_pos+=y_origin-y;
				}




				printf("x: %f, y: %f\n",x_pos,y_pos );
				updatedisplay(60);

				clearDisplay(0,0,0);

		}

		engineQuit(new_engine);
		return 0;
}
