#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "al_engine.h"

engine *new_engine;
vector pos;
int x=300;
int y=300;
int main() {
		new_engine = createEngine();
		engineInit(new_engine,600,600,0,0,0);

		while(new_engine->exit_status) {
				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(23,new_engine) || keyDown(17,new_engine)) ))) {
						exitEngine(new_engine);
				}

				clearDisplay(0,0,0);
				printf("out: %i\n",mouseButtonPressed(0,new_engine));
				updatedisplay(60);
		}

		engineQuit(new_engine);
		return 0;
}
