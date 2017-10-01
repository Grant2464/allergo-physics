#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
typedef struct  _vector {
		float x;
		float y;
} vector;
typedef struct _ball {
		vector pos1;
		int radius,r,g,b;
} ball;
typedef struct _rect {
		vector pos1, pos2;
		int r,g,b;
} rect;
typedef struct _line {
		vector pos1, pos2;
		int r,g,b;
} line;
typedef struct _shape {
		char *id;
		rect shape_rect;
		ball shape_ball;
		line shape_line;
		vector vel,accel;
		void (*draw)(struct _shape);
		void (*physics)(char *id);
		void (*move)(float x, float y);
		void (*rotate)(char *id,float degrees);
} shape;
typedef struct node {
		shape data;
		struct node* next;
} node;
typedef struct _engine {
		ALLEGRO_DISPLAY *display;
		ALLEGRO_EVENT_QUEUE *event_queue;
		ALLEGRO_EVENT event;
		bool exit_status;
		int width;
		int height;
} engine;

int append(shape data,node* head);
void add_circle(char *id,int pos_x1,int pos_y1,float vel_x,float vel_y,float accel_x,float accel_y,int radius,int r,int g, int b);
void add_rect(char *id,int pos_x1,int pos_y1,int pos_x2,int pos_y2,float vel_x,float vel_y,float accel_x,float accel_y,int r,int g, int b);
void add_line(char *id,int pos_x1,int pos_y1,int pos_x2,int pos_y2,float vel_x,float vel_y,float accel_x,float accel_y,int r,int g, int b);
node* find_by_id(char *id );

extern node* shapes;
