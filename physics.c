#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"

void physics_ball(){
		shapes->data.shape_ball.pos1=vector_sum(shapes->data.vel,shapes->data.shape_ball.pos1);
		shapes->data.vel=vector_sum(shapes->data.vel,shapes->data.accel);
}
void physics_rect(){
		shapes->data.shape_rect.pos1=vector_sum(shapes->data.vel,shapes->data.shape_rect.pos1);
		shapes->data.shape_rect.pos2=vector_sum(shapes->data.vel,shapes->data.shape_rect.pos2);
		shapes->data.vel=vector_sum(shapes->data.vel,shapes->data.accel);

}
void physics_line(){
		shapes->data.shape_line.pos1=vector_sum(shapes->data.vel,shapes->data.shape_line.pos1);
		shapes->data.shape_line.pos2=vector_sum(shapes->data.vel,shapes->data.shape_line.pos2);
		shapes->data.vel=vector_sum(shapes->data.vel,shapes->data.accel);
}


void move_ball(float x, float y){
		shapes->data.shape_ball.pos1=vector_sum(create_vector(x,y),shapes->data.shape_ball.pos1);
}
void move_rect(float x, float y){
		shapes->data.shape_rect.pos1=vector_sum(create_vector(x,y),shapes->data.shape_rect.pos1);
		shapes->data.shape_rect.pos2=vector_sum(create_vector(x,y),shapes->data.shape_rect.pos2);

}
void move_line(float x, float y){

		printf("%f\n", y);
		shapes->data.shape_line.pos1=vector_sum(create_vector(x,y),shapes->data.shape_line.pos1);
		shapes->data.shape_line.pos2=vector_sum(create_vector(x,y),shapes->data.shape_line.pos2);
}
void move(char *id,float x, float y){

		node* head=shapes;
		shapes=find_by_id(id);
		(*shapes->data.move)(x,y);
		shapes=head;

}




void rotate_ball(float degrees){
}
void rotate_rect(float degrees){
		vector cent=center(shapes->data.shape_rect.pos1,shapes->data.shape_rect.pos2);
		shapes->data.shape_rect.pos1=spin(degrees,shapes->data.shape_rect.pos1,cent);
		shapes->data.shape_rect.pos2=spin(degrees,shapes->data.shape_rect.pos2,cent);
}
void rotate_line(float degrees){
		printf("%f\n",degrees);
		vector cent=center(shapes->data.shape_line.pos1,shapes->data.shape_line.pos2);
		shapes->data.shape_line.pos1=spin(degrees,shapes->data.shape_line.pos1,cent);
		shapes->data.shape_line.pos2=spin(degrees,shapes->data.shape_line.pos2,cent);
}
void rotate(char *id,float degrees){

		node* head=shapes;
		shapes=find_by_id(id);
		(*shapes->data.rotate)(id,degrees);
		shapes=head;

}
vector spin(float degrees,vector point,vector mid){
		degrees*=DEG;
		vector out;
		out.y=sin(degrees) * (point.x - mid.x) + cos(degrees) * (point.y - mid.y) + mid.y;
		out.x=cos(degrees) * (point.x - mid.x) - sin(degrees) * (point.y-mid.y) + mid.x;
		return out;
}

void physics(char *id){
		node* head=shapes;
		shapes=find_by_id(id);
		(*shapes->data.physics)(id);
		shapes=head;


}

vector center(vector p1, vector p2){
		vector out;
		out.x=(p1.x+p2.x)/2;
		out.y=(p1.y+p2.y)/2;
		return out;
}
