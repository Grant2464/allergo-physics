#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_opengl.h>
#include <stdio.h>

#include <math.h>
#include <assert.h>

#define MOUSE_LEFT 0
#define MOUSE_RIGHT 1
#define MOUSE_MIDDLE 2
#define FIXED 0
#define RESIZEABLE 1
#define createEngine(the_engine) malloc(sizeof *the_engine)
#define rgb(r, g, b) al_map_rgb( r,  g,  b)
#define clearDisplay(r,g,b) al_clear_to_color(al_map_rgb(r,g,b))
#define updatedisplay(sec)  al_flip_display()
typedef struct _VectorF {
		float x;
		float y;
} VectorF;
typedef struct _VectorI {
		int x;
		int y;
} VectorI;
typedef struct _engine {
		int width;
		int height;
		bool win_size;
		bool exit_status;
		ALLEGRO_FONT *font;

		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_EVENT event;
		bool focused;
		bool keys[ ALLEGRO_KEY_MAX ];
		bool last_keys[ ALLEGRO_KEY_MAX ];
		ALLEGRO_MOUSE_STATE mouse_state;
		bool mouse_buttons[3];
		bool last_mouse_buttons[3];
		VectorI mouse_pos;
		VectorI last_mouse_pos;
		VectorI wheel_pos;
} engine;

typedef struct _MouseButtons {
		bool left;
		bool right;
		bool middle;
} MouseButtons;

//////////////////////////NON-ENGINE RELATED//////////////////////////
void delay (int sec);
VectorI createVectorI(int x, int y);
VectorF createVectorF(float x, float y);


////////////////////////////////ENGINE////////////////////////////////
void engineInit(engine * new_engine, const char *title,int w, int h,bool resizeable,int r,int g,int b,int pt);
void engineQuit(engine * to_exit);
void glSetup(int r, int g, int b, int extra);

////////////////////////////////EVENTS////////////////////////////////
void eventCheck(engine * new_engine);
void exitEngine(engine * check_engine);

////////////////////////////////INPUT/////////////////////////////////
bool keyDown(int keycode,engine * new_engine);
bool keyUp(int keycode,engine * new_engine );
bool keyPressed(int keycode,engine * check_engine);
bool keyReleased(int keycode,engine * check_engine);


bool mouseCursorMoving(engine * check_engine);
bool mouseButtonDown(int button,engine * check_engine);
bool mouseButtonUp(int button,engine * check_engine);
bool mouseButtonPressed(int button,engine * check_engine);
bool mouseButtonReleased(int button,engine * check_engine);
