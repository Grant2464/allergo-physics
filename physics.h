#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265
#define DEG 3.14159265/180
void physics_ball();
void physics_rect();
void physics_line();
void physics(char *id);

void move_ball(float x, float y);
void move_rect(float x, float y);
void move_line(float x, float y);
void move(char *id,float x, float y);
vector center(vector p1, vector p2);
void rotate_ball(float degrees);
void rotate_rect(float degrees);
void rotate_line(float degrees);
void rotate(char *id,float degrees);
vector spin(float degrees,vector point,vector mid);
