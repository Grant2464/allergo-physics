#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"

void physics_ball(shape b)
{
		shapes->data.shape_ball.pos1=vector_sum(shapes->data.shape_ball.vel,shapes->data.shape_ball.pos1);
		shapes->data.shape_ball.vel=vector_sum(shapes->data.shape_ball.vel,shapes->data.shape_ball.accel);
}
void physics_rect(shape r)
{
		shapes->data.shape_rect.pos1=vector_sum(shapes->data.shape_rect.vel,shapes->data.shape_rect.pos1);
		shapes->data.shape_rect.pos2=vector_sum(shapes->data.shape_rect.vel,shapes->data.shape_rect.pos2);
		shapes->data.shape_rect.vel=vector_sum(shapes->data.shape_rect.vel,shapes->data.shape_ball.accel);

}
void physics_line(shape l)
{
		shapes->data.shape_line.pos1=vector_sum(shapes->data.shape_line.vel,shapes->data.shape_line.pos1);
		shapes->data.shape_line.pos2=vector_sum(shapes->data.shape_line.vel,shapes->data.shape_line.pos2);
		shapes->data.shape_line.vel=vector_sum(shapes->data.shape_line.vel,shapes->data.shape_ball.accel);
}
void physics(){
		node* head=shapes;
		while(shapes!=NULL)
		{
				(*shapes->data.physics)(shapes->data);
				shapes= shapes->next;
		}
		shapes=head;

}
