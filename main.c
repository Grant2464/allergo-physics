#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"
#define PI 3.14159265
#define DEG 3.14159265/180

node* shapes=NULL;
engine good_engine;

int main() {
		ALLEGRO_EVENT_QUEUE *event_queue=NULL;
		time_t t;
		srand((unsigned)time(&t));
		int width=600;
		int height=600;
		good_engine=init(width,height);



		// add_circle("dog", 0,0,1,1,0.02,0.02,15,255,255,255);
		add_rect("cat", 100,100,150,150,2,2,0.02,0.02,255,255,255);
		add_circle("hey", 0,0,3,3,0.02,0.02,15,255,255,255);
		add_line("ho", 0,0,20,20,1,1,0.1,0.1,255,255,255);
		// add_line("foo", 20,20,50,50,2,1,0.01,0.05,255,255,255);

		while(good_engine.exit_status) {

				event_check();

				al_clear_to_color(al_map_rgb(0,0,0));
				draw();
				al_flip_display();
				delay(1000/60);


		}
		al_destroy_event_queue(good_engine.event_queue);
		al_destroy_display(good_engine.display);
		return 0;
}
