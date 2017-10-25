#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "al_engine.h"

engine *good_engine;

int main() {
		good_engine = malloc(sizeof(engine));
		engineInit(good_engine,1000,1000,0,0,0);

		while(good_engine->exit_status) {
				eventCheck(good_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE) || (keyDown(217) && ((keyDown(23) || keyDown(17)) ))) {
						exitEngine(good_engine);
				}

				clearDisplay(0,0,0);
				vector pos=mousePos(good_engine);
				circle(pos.x,pos.y,10,255,255,255,10);
				//Put stuff here

				updateDisplay(60);
		}

		engineQuit(good_engine);
		return 0;
}
