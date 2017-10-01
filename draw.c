#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"

void draw(){
		node* temp=shapes;
		while(temp!=NULL)
		{

				(*temp->data.draw)(temp->data);
				temp= temp->next;
		}

}
void draw_ball(shape b)
{
		ball temp=b.shape_ball;
		al_draw_circle(temp.pos1.x,temp.pos1.y, temp.radius,al_map_rgb(temp.r,temp.g,temp.b), 3);
}
void draw_rect(shape r)
{
		rect temp=r.shape_rect;

		al_draw_rectangle(temp.pos1.x, temp.pos1.y,temp.pos2.x, temp.pos2.y,al_map_rgb(temp.r, temp.g,  temp.b),3);
}
void draw_line(shape l)
{
		line temp=l.shape_line;
		al_draw_line(temp.pos1.x, temp.pos1.y,temp.pos2.x, temp.pos2.y,al_map_rgb(temp.r, temp.g,  temp.b),3);
}
