#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_opengl.h>

#include "core/graphics.h"


engine *new_engine;
Triangle* triangles;

int main () {
		triangles=createTriangle(triangles);



		// appendVertex(300,300,300,&triangles);
		// appendVertex(-0,-300,-300,&triangles);
		// appendVertex(-300,300,-300,&triangles);
		//
		appendVertex(300,300,100,&triangles);
		appendVertex(-300,300,300,&triangles);
		appendVertex(-300,-300,200,&triangles);
		appendVertex(300,-300,300,&triangles);



		new_engine = createEngine(new_engine);
		engineInit(new_engine,"ohWindow myWindow",600,600,0,0,0,0,72);
		while(new_engine->exit_status) {

				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}
				// clearDisplay(0,0,0);

				glSetup(0,0,0,1);
				draw_opengl(triangles,new_engine);
				updatedisplay(60);


		}
		freeTriangle(triangles);
		engineQuit(new_engine);
		return 0;
}
