#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"




node* shapes=NULL;







int main() {
		time_t t;
		srand((unsigned)time(&t));
		int width=600;
		int height=600;
		init(width,height);

		// add_circle(pos_x1,pos_y1,vel_x,vel_y,accel_x,accel_y,radius,r,g,b);
		// add_rect(pos_x1,pos_y1,pos_x2,pos_y2,vel_x,vel_y,accel_x,accel_y,r,g,b);
		// add_line(pos_x1,pos_y1,pos_x2,pos_y2,vel_x,vel_y,accel_x,accel_y,r,g,b);
		add_circle("dog", 0,0,1,1,0.1,0.1,10,255,255,255);

		while(1) {
				al_clear_to_color(al_map_rgb(0,0,0) );

				physics();
				draw();
				al_flip_display();
				delay(1000/100);
		}
}
