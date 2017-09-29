#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"


engine create_engine(int w,int h){
		engine out;
		ALLEGRO_DISPLAY *display;
		out.display=display,out.width=w,out.height=h;
		return out;
}
vector create_vector(float x,float y){
		vector out;
		out.x=x,out.y=y;
		return out;
}
vector vector_sum(vector a, vector b){
		vector out;
		out.x=a.x+b.x;
		out.y=a.y+b.y;
		return out;
}
int append(shape data,node* head){
		if(head==NULL) {
				node* new_node = (node*)malloc(sizeof(node));

				new_node->data = data;
				new_node->next = NULL;
				shapes=new_node;
				return 0;
		}
		node *cursor = head;
		while(cursor->next != NULL)
				cursor = cursor->next;
		node* new_node =  (node*)malloc(sizeof(node));
		new_node->data = data;
		new_node->next = cursor->next;
		cursor->next = new_node;
		return 0;
}


void add_circle(char *id,int pos_x1,int pos_y1,float vel_x,float vel_y,float accel_x,float accel_y,int radius,int r,int g, int b){
		shape new_shape;
		ball new_ball;
		new_shape.id=id;
		new_ball.pos1.x=pos_x1,new_ball.pos1.y=pos_y1;
		new_ball.vel.x=vel_x,new_ball.vel.y=vel_y;
		new_ball.accel.x=accel_x,new_ball.accel.y=accel_y;
		new_ball.radius=radius;
		new_ball.r=r,new_ball.g=g,new_ball.b=b;
		new_shape.shape_ball=new_ball;
		new_shape.draw=draw_ball;
		new_shape.physics=physics_ball;
		append(new_shape,shapes);
}
void add_rect(char *id,int pos_x1,int pos_y1,int pos_x2,int pos_y2,float vel_x,float vel_y,float accel_x,float accel_y,int r,int g, int b){
		shape new_shape;
		rect new_rect;
		new_shape.id=id;
		new_rect.pos1.x=pos_x1,new_rect.pos1.y=pos_y1,new_rect.pos2.x=pos_x2,new_rect.pos2.y=pos_y2;
		new_rect.vel.x=vel_x,new_rect.vel.y=vel_y;
		new_rect.accel.x=accel_x,new_rect.accel.y=accel_y;
		new_rect.r=r,new_rect.g=g,new_rect.b=b;
		new_shape.shape_rect=new_rect;
		new_shape.draw=draw_rect;
		new_shape.physics=physics_rect;

		append(new_shape,shapes);
}
void add_line(char *id,int pos_x1,int pos_y1,int pos_x2,int pos_y2,float vel_x,float vel_y,float accel_x,float accel_y,int r,int g, int b){
		shape new_shape;
		line new_line;
		new_shape.id=id;
		new_line.pos1.x=pos_x1,new_line.pos1.y=pos_y1,new_line.pos2.x=pos_x2,new_line.pos2.y=pos_y2;
		new_line.vel.x=vel_x,new_line.vel.y=vel_y;
		new_line.accel.x=accel_x,new_line.accel.y=accel_y;
		new_line.r=r,new_line.g=g,new_line.b=b;
		new_shape.shape_line=new_line;
		new_shape.draw=draw_line;
		new_shape.physics=physics_line;

		append(new_shape,shapes);
}
