#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro_opengl.h>

#include "al_engine.h"
#define new_max(x,y) ((x) >= (y)) ? (x) : (y)
engine *new_engine;
vector pos;
typedef struct _Vertex {
		float x;
		float y;
		float z;
} Vertex;
typedef struct _Triangle {
		struct Triangle* next;
		Vertex data;
} Triangle;

Vertex createVertex(float x, float y, float z){
		Vertex out;
		out.x=x,out.y=y, out.z=z;
		return out;
}
void printVertex(Vertex to_print){
		printf("x: %f, y: %f, z: %f\n", to_print.x,to_print.y,to_print.z);
}

void append(Vertex data,Triangle** head){


		*head= (Triangle*)malloc(sizeof *head);

		(*head)->data=data;
		(*head)->next=NULL;
		printf("Itsnull\n");
		return;


		// while(head->next==NULL) {
		//      printVertex(head->data);
		// }
}
Triangle* head;

int main () {

		Vertex test=createVertex(10,10,10);
		Vertex test2=createVertex(0,1,2);

		append(test,&head);
		append(test2,&head->next);

		new_engine = createEngine(new_engine);
		engineInit(new_engine,"ohWindow myWindow",600,600,0,0,0,72);

		while(new_engine->exit_status) {

				eventCheck(new_engine);

				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}
				printVertex(head->next->data);

				clearDisplay(0,0,0);
				circle(300,300,50,100,255,0,10);
				updatedisplay(60);


		}

		engineQuit(new_engine);
		return 0;
}
