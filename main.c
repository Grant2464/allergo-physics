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
		new_engine = malloc(sizeof(engine));
		engineInit(new_engine,1000,1000,0,0,0);

		while(new_engine->exit_status) {
				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE) || (keyDown(217) && ((keyDown(23) || keyDown(17)) ))) {
						exitEngine(new_engine);
				}

				clearDisplay(0,0,0);
				circle(100,100,10,255,255,255,10);
				updateDisplay(60);
		}

		engineQuit(new_engine);
		return 0;
}
