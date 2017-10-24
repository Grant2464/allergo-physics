#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "al_engine.h"

#define PI 3.14159265
#define DEG 3.14159265/180

engine *good_engine;

int main() {
		ALLEGRO_EVENT_QUEUE *event_queue=NULL;
		time_t t;
		srand((unsigned)time(&t));
		good_engine = malloc(sizeof(engine));

		init(good_engine,600,600);
		float x=0;
		float y=0;
		while(good_engine->exit_status) {
				eventCheck(good_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE)) {
						exitEngine(good_engine);
				}
				if(mouseButtonDown(MOUSE_MIDDLE,good_engine)) {
						x=mousePos(good_engine).x;
						y=mousePos(good_engine).y;
				}


				al_clear_to_color(al_map_rgb(0,0,0));
				al_draw_circle(x, y, 50, al_map_rgb_f(1, 0.5, 0), 3);
				al_flip_display();

				delay(1000/60);
		}

		al_destroy_event_queue(good_engine->event_queue);
		al_destroy_display(good_engine->display);
		return 0;
}
