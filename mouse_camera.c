#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_opengl.h>

#include "al_engine.h"
#define new_max(x,y) ((x) >= (y)) ? (x) : (y)
engine *new_engine;
vector pos;

void glSetup(int r, int g, int b, int extra){
		// Window background color

		glClearColor(r, g, b, extra);
		// Clear a window

		// Initializes coordinate system of projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
}
void draw_opengl(float r_x,float r_y,engine * check_engine)
{
		r_x*=1000;
		r_y*=1000;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// printf("x: %f, y: %f\n",r_x,r_y);

		glRotatef(r_y, 1.0f, 0.0f, 0.0f);
		glRotatef(-r_x, 0.0f, 1.0f, 0.0f);
		// Volume Visualization (xMin, xMax, yMin, yMax, zMin, zMax)
		int max=new_max(check_engine->width, check_engine->height);
		glOrtho(-check_engine->width, check_engine->width, -check_engine->height, check_engine->height, -max, max);

		float eye[2]={1.0, 1.0, 1.0}; //Specifies the position of the eye point.
		float center[2]={20.0, 0.0, 0.0}; //Specifies the position of the reference point.
		float up[2]={0, 1, 0}; //Specifies the direction of the up vector.

		// Initializes the coordinate system
		gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2],   up[0],up[1],up[2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(10);


		glBegin(GL_QUADS);
		// top
		glColor3f(100.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 300.0f);
		glVertex3f(-300.0f, 300.0f, 300.0f);
		glVertex3f(300.0f, 300.0f, 300.0f);
		glVertex3f(300.0f, 300.0f, -300.0f);
		glVertex3f(-300.0f, 300.0f, -300.0f);


		// bottom
		glColor3f(100.0f, 0.0f, 0.0f);
		glVertex3f(300.0f, -300.0f, 300.0f);
		glVertex3f(-300.0f, -300.0f, 300.0f);
		glVertex3f(-300.0f, -300.0f, -300.0f);
		glVertex3f(300.0f, -300.0f, -300.0f);


		// front
		glColor3f(100.0f, 0.0f, 0.0f);
		glVertex3f(300.0f, -300.0f, 300.0f);
		glVertex3f(300.0f, 300.0f, 300.0f);
		glVertex3f(-300.0f, 300.0f, 300.0f);
		glVertex3f(-300.0f, -300.0f, 300.0f);


		// back
		glColor3f(100.0f, 0.0f, 0.0f);
		glVertex3f(300.0f, 300.0f, -300.0f);
		glVertex3f(300.0f, -300.0f, -300.0f);
		glVertex3f(-300.0f, -300.0f, -300.0f);
		glVertex3f(-300.0f, 300.0f, -300.0f);

		// right
		glColor3f(100.0f, 0.0f, 0.0f);
		glVertex3f(300.0f, 300.0f, -300.0f);
		glVertex3f(300.0f, 300.0f, 300.0f);
		glVertex3f(300.0f, -300.0f, 300.0f);
		glVertex3f(300.0f, -300.0f, -300.0f);


		// left
		glColor3f(100.0f, 0.0f, 0.0f);
		glVertex3f(-300.0f, -300.0f, 300.0f);
		glVertex3f(-300.0f, 300.0f, 300.0f);
		glVertex3f(-300.0f, 300.0f, -300.0f);
		glVertex3f(-300.0f, -300.0f, -300.0f);

		glEnd();


}
int main() {



		al_set_new_display_flags(ALLEGRO_OPENGL);
		new_engine = createEngine(new_engine);
		engineInit(new_engine,"ohWindow myWindow",600,600,0,0,0,72);
		float x=0.0;
		float y=0.0;
		float x_origin = 1;
		float y_origin = 1;
		float x_pos =0;
		float y_pos =0;
		while(new_engine->exit_status) {

				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}

				if(mouseButtonUp(0,new_engine)) {
						x_origin = new_engine->mouse_pos.x;
						y_origin = new_engine->mouse_pos.y;
				}
				if(mouseCursorMoving(0,new_engine) && mouseButtonDown(0,new_engine)) {
						x_origin = new_engine->mouse_pos.x;
						y_origin = new_engine->mouse_pos.y;
						x_pos+=x_origin-x;
						y_pos+=y_origin-y;
				}
				float new_x_pos= x_pos/1000;
				float new_y_pos= y_pos/1000;

				glSetup(0,0,0,1);
				draw_opengl(new_x_pos,new_y_pos,new_engine);

				printf("x: %f, y: %f\n",new_x_pos,new_y_pos );

				updatedisplay(60);
				if(mouseButtonDown(0,new_engine)) {
						x = new_engine->mouse_pos.x;
						y = new_engine->mouse_pos.y;


				}
				// clearDisplay(0,0,0);

		}

		engineQuit(new_engine);
		return 0;
}
