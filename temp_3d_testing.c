
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>


ALLEGRO_EVENT_QUEUE *event_queue;

double rotate_y=0;
double rotate_x=0;



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
		// front
		glColor3f(100.0f, 0.0f, 0.0f);
		glNormal3f(0.0f, 0.0f, 100.0f);
		glVertex3f(50.0f, -50.0f, 50.0f);
		glVertex3f(50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, 50.0f, 50.0f);
		glVertex3f(-50.0f, -50.0f, 50.0f);

		glEnd();
}


int main(void)
{
		al_init();

		al_set_new_display_flags(ALLEGRO_OPENGL);

		ALLEGRO_DISPLAY *display = al_create_display(500, 500);

		float c=1;
		float i=1;

		while (true) {

				draw_opengl(i);
				i++;
				al_flip_display();
		}

		return 0;
}
