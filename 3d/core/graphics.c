#include "graphics.h"

VectorI vectorSumI(VectorI v1, VectorI v2){
		return createVectorI(v1.x+v2.x,v1.y+v2.y);
}
VectorF vectorSumF(VectorF v1, VectorF v2){


		return createVectorF(v1.x+v2.x, v1.y+v2.y);
}


void circle(int x, int y, int r, int color_r,int color_g, int color_b,int stroke){
		al_draw_circle(x, y, r, al_map_rgb(color_r,color_g,color_b), stroke);
}
void rectangle(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke){
		al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(color_r,color_g,color_b), stroke);
}
void line(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke){
		al_draw_line(x1,y1,x2,y2, al_map_rgb(color_r,color_g,color_b), stroke);
}

VectorI pixel2coord(int x, int y, engine * canvas){
		return createVectorI(x+canvas->height/2,-y+canvas->width/2);
}
void text(char *text,  int x, int y, int r, int g, int b, engine * canvas){
		al_draw_text(canvas->font, al_map_rgb(r, g, b), x, y, 1, text);
}

Vertex createVertex(float x, float y, float z){
		Vertex out;
		out.x=x,out.y=y, out.z=z;
		return out;
}

void initializeTriangle(Vertex data,Triangle** head){
		*head= createTriangle(head);
		(*head)->data=data;
		(*head)->next= createTriangle(head);
}
void appendVertex(float x, float y, float z,Triangle** head){
		Vertex data=createVertex(x,y,z);
		if((*head)==NULL) {
				initializeTriangle(data,head);
				return;
		}
		Triangle* new=&head;

		while(new->next!=NULL) {
				new=new->next;
		}
		new->data=data;
		new->next=createTriangle(new);
		return;
}
void makeVertex(Vertex to_make){
		glVertex3f(to_make.x,to_make.y,to_make.z);
}
void drawTriangle(Triangle* head){
		while(head->next!=NULL) {
				makeVertex(head->data);
				head=head->next;
		}
}
void freeTriangle(Triangle* head){
		Triangle* tmp;
		while(head!=NULL) {
				tmp=head;
				head=head->next;
				free(tmp);
		}
}
void draw_opengl(Triangle* head, engine * check_engine)
{

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// printf("x: %f, y: %f\n",r_x,r_y);

		// Volume Visualization (xMin, xMax, yMin, yMax, zMin, zMax)
		int max=new_max(check_engine->width, check_engine->height);
		// glOrtho(-check_engine->width, check_engine->width, -check_engine->height, check_engine->height, -max, max);
		glOrtho(-600,600,-600,600,-600,600);

		float eye[3]={0.0, 0.0, 1.0}; //Specifies the position of the eye point.
		float center[3]={0.0, 0.0, 0.0}; //Specifies the position of the reference point.
		float up[3]={0, 1, 0}; //Specifies the direction of the up Vector.

		// Initializes the coordinate system
		gluLookAt(eye[0],eye[1],eye[2],  center[0],center[1],center[2],   up[0],up[1],up[2]);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(10);


		glBegin(GL_QUADS);
		// top
		glColor3f(100.0f, 0.0f, 0.0f);
		glNormal3f(300.0f, 300.0f, 300.0f);


		drawTriangle(head);
		glEnd();


}
