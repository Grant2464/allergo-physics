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


/*
   typedef struct _good_engine {
   ALLEGRO_EVENT_QUEUE *event_queue; - done
   ALLEGRO_DISPLAY *display; - done
   bool exit_status;
   pthread_t draw_thread;
   bool get_keys[ ALLEGRO_KEY_MAX ];
   ALLEGRO_MOUSE_STATE mouse_state;
   ALLEGRO_EVENT ev_catcher;
   void (*draw_function)(struct _good_engine *);
   } good_engine;
 */

node* shapes=NULL;
engine good_engine;

int main() {
		ALLEGRO_EVENT_QUEUE *event_queue=NULL;
		time_t t;
		srand((unsigned)time(&t));
		int width=600;
		int height=600;
		good_engine=init(width,height);


		// add_circle(pos_x1,pos_y1,vel_x,vel_y,accel_x,accel_y,radius,r,g,b);
		// add_rect(pos_x1,pos_y1,pos_x2,pos_y2,vel_x,vel_y,accel_x,accel_y,r,g,b);
		// add_line(pos_x1,pos_y1,pos_x2,pos_y2,vel_x,vel_y,accel_x,accel_y,r,g,b);
		add_circle("dog", 0,0,1,1,0.1,0.1,15,255,255,255);
		add_rect("cat", 0,0,30,30,2,2,0.1,0.1,255,255,255);
		add_circle("hey", 0,0,3,3,0.1,0.1,15,255,255,255);
		add_rect("ho", 0,0,30,30,4,4,0.1,0.1,255,255,255);

		while(good_engine.exit_status) {
				event_check();
				al_clear_to_color(al_map_rgb(0,0,0));
				physics();
				draw();
				al_flip_display();
				delay(1000/100);
		}
		al_destroy_event_queue(good_engine.event_queue);
		al_destroy_display(good_engine.display);
		return 0;
}
