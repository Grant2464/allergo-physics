#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
typedef struct  _vector {
		float x;
		float y;
} vector;
typedef struct _ball {
		vector pos1,vel,accel;
		int radius,r,g,b;
} ball;
typedef struct _rect {
		vector pos1, pos2,vel,accel;
		int r,g,b;
} rect;
typedef struct _line {
		vector pos1, pos2,vel,accel;
		int r,g,b;
} line;
typedef struct _shape {
		char *id;
		rect shape_rect;
		ball shape_ball;
		line shape_line;
		void (*draw)(struct _shape);
		void (*physics)(struct _shape);
} shape;
typedef struct node {
		shape data;
		struct node* next;
} node;
typedef struct _engine {
		ALLEGRO_DISPLAY *display;
		int width;
		int height;
} engine;
vector create_vector(float x,float y);
vector vector_sum(vector a, vector b);
engine create_engine(int w,int h);
int append(shape data,node* head);
void add_circle(char *id,int pos_x1,int pos_y1,float vel_x,float vel_y,float accel_x,float accel_y,int radius,int r,int g, int b);
void add_rect(char *id,int pos_x1,int pos_y1,int pos_x2,int pos_y2,float vel_x,float vel_y,float accel_x,float accel_y,int r,int g, int b);
void add_line(char *id,int pos_x1,int pos_y1,int pos_x2,int pos_y2,float vel_x,float vel_y,float accel_x,float accel_y,int r,int g, int b);


extern node* shapes;
