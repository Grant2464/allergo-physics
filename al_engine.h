#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
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
typedef struct _MouseButtons {
		bool left;
		bool right;
		bool middle;
} MouseButtons;

//////////////////////////NON-ENGINE RELATED//////////////////////////
void delay (int sec);
vector createVector(float x, float y);

////////////////////////////////ENGINE////////////////////////////////
void engineInit(engine * setup,int w, int h,int r, int g, int b);
void engineQuit(engine * to_exit);
void clearDisplay(int r, int g, int b);
void updateDisplay(int sec);

////////////////////////////////EVENTS////////////////////////////////
void eventCheck(engine * new_engine);
void exitEngine(engine * check_engine);

////////////////////////////////INPUT/////////////////////////////////
bool keyDown(int keycode);
bool keyUp(int keycode);
bool keyPressed(int keycode,engine * check_engine);

vector mousePos(engine * check_engine);
bool mouseButtonDown(int button,engine * check_engine);
bool mouseButtonPressed(int button,engine * check_engine);

///////////////////////////////DRAWING////////////////////////////////
void circle(int x, int y, int r, int color_r,int color_g, int color_b,int stroke);
void rectangle(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke);
void line(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke);
vector pixel2coord(engine * canvas,float x, float y);
