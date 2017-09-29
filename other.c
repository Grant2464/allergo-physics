#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"


void delay(int sec){
		int ms = 1000 * sec;
		clock_t start = clock();
		while (clock() < start + ms) ;
}
int init(int w, int h) {
		engine test_engine =create_engine(w,h);
		if(!al_init()) {
				fprintf(stderr, "Failed to initialize Allegro.\n");
				return -1;
		}
		if(!al_init_primitives_addon()) {
				fprintf(stderr,"Couldn't initialize primitives addon!\n");
				return -1;
		}

		test_engine.display=al_create_display(test_engine.width,test_engine.height);
		if(!test_engine.display) {
				fprintf(stderr,"Couldn't create allegro display!\n");
				return -1;
		}


}
