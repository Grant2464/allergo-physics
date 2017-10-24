#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define MOUSE_MIDDLE 3
typedef struct _vector {
		float x;
		float y;
} vector;
typedef struct _engine {
		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_EVENT event;
		bool exit_status;
		int width;
		int height;
} engine;
/*
   What I want:
    while loop
    exitCheck(engine)


 */
vector createVector(float x, float y);
vector mousePos(engine * check_engine);
bool mouseButtonDown(int button,engine * check_engine);
void init(engine * setup,int w, int h);
void delay(int sec);
void eventCheck(engine * new_engine);
void exitEngine(engine * check_engine);
bool keyDown(int keycode);
bool keyUp(int keycode);
