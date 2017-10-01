#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
vector create_vector(float x,float y);
vector vector_sum(vector a, vector b);
engine init(int w, int h);
void delay(int sec);
void event_check();
extern engine good_engine;
