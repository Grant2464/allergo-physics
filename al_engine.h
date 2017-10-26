#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#include <math.h>
#include <assert.h>

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2
#define createEngine(the_engine) malloc(sizeof *the_engine)
#define rgb(r, g, b) al_map_rgb( r,  g,  b)
#define clearDisplay(r,g,b) al_clear_to_color(al_map_rgb(r,g,b))
#define updatedisplay(sec)  al_flip_display(); delay(1000/sec)
typedef struct _vector {
		float x;
		float y;
} vector;
typedef struct _engine {
		int width;
		int height;
		bool exit_status;

		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_EVENT event;

		bool keys[ ALLEGRO_KEY_MAX ];
		bool last_keys[ ALLEGRO_KEY_MAX ];
		ALLEGRO_MOUSE_STATE mouse_state;
		bool mouse_buttons[2];
		bool last_mouse_buttons[3];
		vector mouse_pos;
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

////////////////////////////////EVENTS////////////////////////////////
void eventCheck(engine * new_engine);
void exitEngine(engine * check_engine);

////////////////////////////////INPUT/////////////////////////////////
bool keyDown(int keycode,engine * new_engine);
bool keyUp(int keycode,engine * new_engine );
bool keyPressed(int keycode,engine * check_engine);

vector mousePos(engine * check_engine);
bool mouseButtonDown(int button,engine * check_engine);
bool mouseButtonUp(int button,engine * check_engine);
bool mouseButtonPressed(int button,engine * check_engine);

///////////////////////////////DRAWING////////////////////////////////
void circle(int x, int y, int r, int color_r,int color_g, int color_b,int stroke);
void rectangle(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke);
void line(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke);

vector pixel2coord(engine * canvas,float x, float y);
