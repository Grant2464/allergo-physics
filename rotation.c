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
		float r_x=0.0;
		float r_y=0.0;
		int x=300;
		int y=300;
		float deltaAngleX = 0.0f;
		float angleX = 0.0f;

		int xOrigin = -1;

		float deltaAngleY = 0.0f;
		float angleY = 0.0f;

		int yOrigin = -1;
		float lx;
		float lz;
		while(new_engine->exit_status) {
				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}

				if(mouseButtonDown(0,new_engine)) {
						xOrigin = new_engine->mouse_pos.x;
						yOrigin = new_engine->mouse_pos.y;

				}
				if(mouseButtonUp(0,new_engine)) {
						angleX += deltaAngleX;
						xOrigin = -1;
						angleY += deltaAngleY;
						yOrigin = -1;
				}
				if(mouseMoving(new_engine)) {
						printf("hey\n");
						if (xOrigin >= 0 || yOrigin >= 0) {

								// update deltaAngleX
								deltaAngleX = (x - xOrigin) * 0.001f;
								deltaAngleY = (y - yOrigin) * 0.001f;

								// update camera's direction
								lx = sin(angleX + deltaAngleX);
								lz = -cos(angleY + deltaAngleY);
						}
				}


				glSetup(0,0,0,1);
				draw_opengl(lx,lz,new_engine);

				printf("x: %f, y: %f\n",lx,lz );

				updatedisplay(60);

				// clearDisplay(0,0,0);

		}

		engineQuit(new_engine);
		return 0;
}


/*
   GLuint pid;
   ALLEGRO_DISPLAY *d;
   assert(!al_init());

   al_set_new_display_flags(ALLEGRO_OPENGL);
   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);
   d = al_create_display(WINDOW_W, WINDOW_H);
   assert(!d);

   al_get_display_option(d, ALLEGRO_SAMPLE_BUFFERS);

   if (al_get_opengl_extension_list()->ALLEGRO_GL_ARB_multisample) {
        glEnable(GL_MULTISAMPLE_ARB);
   }

   if (!al_get_opengl_extension_list()->ALLEGRO_GL_ARB_vertex_program) {
        assert(1);
   }

   glEnable(GL_DEPTH_TEST);
   glShadeModel(GL_SMOOTH);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glDisable(GL_CULL_FACE);

   //  Setup projection and modelview matrices
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0, WINDOW_W/(float)WINDOW_H, 0.1, 100.0);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   //  Position the camera to look at our mesh from a distance
   gluLookAt(0.0f, 20.0f, -45.0f, 0.0f, 0.0f, 0.0f, 0, 1, 0);

   create_mesh();

   //  Define the vertex program
   glEnable(GL_VERTEX_PROGRAM_ARB);
   glGenProgramsARB(1, &pid);
   glBindProgramARB(GL_VERTEX_PROGRAM_ARB, pid);
   glGetError();

   if (al_get_opengl_extension_list()->ALLEGRO_GL_NV_vertex_program2_option) {
        glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
                           strlen(program_nv), program_nv);
   }
   else {
        glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
                           strlen(program), program);
   }

   //  Check for errors
   if (glGetError()) {
        const char *pgm = al_get_opengl_extension_list()->ALLEGRO_GL_NV_vertex_program2_option
                          ? program_nv : program;
        GLint error_pos;
        const GLubyte *error_str = glGetString(GL_PROGRAM_ERROR_STRING_ARB);
        glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &error_pos);

        assert(1);

   }*/
