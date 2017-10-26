#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro_opengl.h>

#include "al_engine.h"

engine *new_engine;
vector pos;
int x=300;
int y=300;
void draw_opengl(float i)
{
		// Window background color
		glClearColor(0, 0, 0, 1);
		// Clear a window
		glClear(GL_COLOR_BUFFER_BIT);

		// Initializes coordinate system of projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glRotatef( i, 1.0, 1.0, 1.0 );
		// Volume Visualization (xMin, xMax, yMin, yMax, zMin, zMax)
		glOrtho(-120, 120, -120, 120, -120, 120);

		// Initializes the coordinate system

		gluLookAt(20.0,20.0,20.0,   0.0,0.0,0.0,   0,1,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(10);


		glBegin(GL_QUADS);
		// top
		glColor3f(100.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 100.0f, 0.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);

		glEnd();


		glBegin(GL_QUADS);
		// bottom
		glColor3f(50.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, -100.0f, 0.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glEnd();


		glBegin(GL_QUADS);
		// front
		glColor3f(0.0f, 100.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 100.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glEnd();
		glBegin(GL_QUADS);
		// back
		glColor3f(0.0f, 50.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, -100.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);

		glEnd();

		glBegin(GL_QUADS);
		// right
		glColor3f(0.0f, 0.0f, 100.0f);
		glNormal3f(100.0f, 0.0f, 0.0f);
		glVertex3f(50.0f, 50.0f, -50.0f);
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glVertex3f(50.0f, -50.0f, -50.0f);

		glEnd();

		glBegin(GL_QUADS);
		// left
		glColor3f(0.0f, 0.0f, 50.0f);
		glNormal3f(-100.0f, 0.0f, 0.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, -50.0f);
		glVertex3f(-50.0f, -50.0f, -50.0f);

		glEnd();



}
int main() {



		al_set_new_display_flags(ALLEGRO_OPENGL);
		new_engine = createEngine(new_engine);
		engineInit(new_engine,600,600,0,0,0);
		float i=1;
		while(new_engine->exit_status) {
				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(23,new_engine) || keyDown(17,new_engine)) ))) {
						exitEngine(new_engine);
				}
				draw_opengl(i);
				i++;
				updatedisplay(60);

				// clearDisplay(0,0,0);

		}

		engineQuit(new_engine);
		return 0;
}
