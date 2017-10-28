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

		int *win_x;
		int *win_y;

		win_x = malloc(sizeof *win_x);
		win_y = malloc(sizeof *win_y);

		while(new_engine->exit_status) {

				eventCheck(new_engine);
				al_get_window_position(new_engine->display,win_x,win_y);
				// printf("x: %i, y: %i\n", *win_x,*win_y);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}
				clearDisplay(0,0,0);
				printf("w: %f, z: %f\n",new_engine->wheel_pos.x, new_engine->wheel_pos.y);
				// printf("moving: %i\n",mouseWheelMoving(2,new_engine));

				if(new_engine->focused) {
						text(255,255,255, 200,200, "Dog", new_engine);
						circle(new_engine->width/2,new_engine->height/2,(new_engine->width+new_engine->height)/50,255,255,255,10);
				}
				updatedisplay(60);

		}

		engineQuit(new_engine);
		return 0;
}
