#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_opengl.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "al_engine.h"
#define new_max(n,m) ((n) >= (m)) ? (n) : (m)

#define createTriangle(the_triangle) (Triangle*)malloc(sizeof *the_triangle)


typedef struct _Vertex {
		float x;
		float y;
		float z;
} Vertex;
typedef struct _Triangle {
		struct Triangle* next;
		Vertex data;
} Triangle;
VectorI vectorSumI(VectorI v1, VectorI v2);
VectorF vectorSumF(VectorF v1, VectorF v2);

void circle(int x, int y, int r, int color_r,int color_g, int color_b,int stroke);
void rectangle(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke);
void line(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke);
VectorI pixel2coord(int x, int y, engine * canvas);
void text(char *text,  int x, int y, int r, int g, int b, engine * canvas);

Vertex createVertex(float x, float y, float z);
void makeVertex(Vertex to_make);
void initializeTriangle(Vertex data,Triangle** head);
void appendVertex(float x, float y, float z,Triangle** head);
void drawTriangle(Triangle* head);
void freeTriangle(Triangle* head);
void draw_opengl(Triangle* head,engine * check_engine);
