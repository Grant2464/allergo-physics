#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <math.h>
#define width 1000
#define height 1000
ALLEGRO_DISPLAY *display=0;
ALLEGRO_FONT *font=0;

typedef struct  _vector {
		float x;
		float y;
} vector;
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
typedef struct _ball {
		vector pos1,vel,accel;
		int radius,r,g,b;
} ball;
typedef struct _rect {
		vector pos1, pos2,vel,accel;
		int r,g,b;
} rect;
typedef struct _line {
		vector pos1, pos2,vel,accel;
		int r,g,b;
} line;
typedef struct _shape {
		rect shape_rect;
		ball shape_ball;
		line shape_line;
		void (*draw)(struct _shape);
		void (*physics)(struct _shape);
} shape;
typedef struct node {
		shape data;
		struct node* next;
} node;
node* shapes=NULL;
void add_circle(int pos_x1,int pos_y1,int vel,int accel,int radius,int r,int g, int b);
void add_rect(int pos_x1,int pos_y1,int pos_x2,int pos_y2,int vel,int accel,int r,int g, int b);
void add_line(int pos_x1,int pos_y1,int pos_x2,int pos_y2,int vel,int accel,int r,int g, int b);

int append(shape data,node* head);
void draw();
void physics();
void draw_ball(shape b);
void draw_rect(shape r);
void draw_line(shape l);
void physics_ball(shape b);
void physics_rect(shape r);
void physics_line(shape l);
int init(void);
int main() {
		time_t t;
		srand((unsigned) time(&t));
		init();

		for(int x=0; x<600; x+=20) {
				add_circle(rand()%width,rand()%height,rand()%10-5,10,rand()%10+10,rand()%255,rand()%255,rand()%255);
				add_rect(rand()%width,rand()%height,rand()%width,rand()%height,rand()%10-5,10,rand()%255,rand()%255,rand()%255);
				add_line(rand()%width,rand()%height,rand()%width,rand()%height,rand()%10-5,10,rand()%255,rand()%255,rand()%255);

		}
		while(1) {
				al_clear_to_color(al_map_rgb(0,0,0));
				physics();
				draw();
				al_flip_display();
		}
}
int init(void) {
		if(!al_init()) {
				fprintf(stderr, "Failed to initialize Allegro.\n");
				return -1;
		}
		/*
		   if(!al_init_font_addon()) {
		        fprintf(stderr, "Failed to initialize Font.\n");
		        return -1;
		   }
		   if(!al_init_ttf_addon()) {
		        fprintf(stderr, "Failed to initialize Ttf.\n");
		        return -1;

		   }
		   font=al_load_ttf_font("arial.ttf",72,0 );
		   if(!font) {
		        fprintf(stderr,"Couldn't create allegro font!\n");
		        return -1;
		   }
		 */
		if(!al_init_primitives_addon()) {
				fprintf(stderr,"Couldn't initialize primitives addon!\n");
				return -1;
		}
		display=al_create_display(width,height);
		if(!display) {
				fprintf(stderr,"Couldn't create allegro display!\n");
				return -1;
		}


}
void add_circle(int pos_x1,int pos_y1,int vel, int accel,int radius,int r,int g, int b){
		shape new_shape;
		ball new_ball;
		new_ball.pos1.x=pos_x1,new_ball.pos1.y=pos_y1;
		new_ball.vel.x=vel,new_ball.vel.y=vel;
		new_ball.accel.x=accel,new_ball.accel.y=accel;
		new_ball.radius=radius;
		new_ball.r=r,new_ball.g=g,new_ball.b=b;
		new_shape.shape_ball=new_ball;
		new_shape.draw=draw_ball;
		new_shape.physics=physics_ball;
		append(new_shape,shapes);
}
void add_rect(int pos_x1,int pos_y1,int pos_x2,int pos_y2,int vel, int accel,int r,int g, int b){
		shape new_shape;
		rect new_rect;
		new_rect.pos1.x=pos_x1,new_rect.pos1.y=pos_y1,new_rect.pos2.x=pos_x2,new_rect.pos2.y=pos_y2;
		new_rect.vel.x=vel,new_rect.vel.y=vel;
		new_rect.accel.x=accel,new_rect.accel.y=accel;
		new_rect.r=r,new_rect.g=g,new_rect.b=b;
		new_shape.shape_rect=new_rect;
		new_shape.draw=draw_rect;
		new_shape.physics=physics_rect;

		append(new_shape,shapes);
}
void add_line(int pos_x1,int pos_y1,int pos_x2,int pos_y2,int vel, int accel,int r,int g, int b){
		shape new_shape;
		line new_line;
		new_line.pos1.x=pos_x1,new_line.pos1.y=pos_y1,new_line.pos2.x=pos_x2,new_line.pos2.y=pos_y2;
		new_line.vel.x=vel,new_line.vel.y=vel;
		new_line.accel.x=accel,new_line.accel.y=accel;
		new_line.r=r,new_line.g=g,new_line.b=b;
		new_shape.shape_line=new_line;
		new_shape.draw=draw_line;
		new_shape.physics=physics_line;

		append(new_shape,shapes);
}
void draw_ball(shape b)
{
		ball temp=b.shape_ball;
		al_draw_circle(temp.pos1.x,temp.pos1.y, temp.radius,al_map_rgb(temp.r,temp.g,temp.b), 10);
}
void draw_rect(shape r)
{
		rect temp=r.shape_rect;

		al_draw_rectangle(temp.pos1.x, temp.pos1.y,temp.pos2.x, temp.pos2.y,al_map_rgb(temp.r, temp.g,  temp.b),10);
}
void draw_line(shape l)
{
		line temp=l.shape_line;
		al_draw_line(temp.pos1.x, temp.pos1.y,temp.pos2.x, temp.pos2.y,al_map_rgb(temp.r, temp.g,  temp.b),10);
}
void physics_ball(shape b)
{
		shapes->data.shape_ball.pos1=vector_sum(shapes->data.shape_ball.vel,shapes->data.shape_ball.pos1);
}
void physics_rect(shape r)
{
		shapes->data.shape_rect.pos1=vector_sum(shapes->data.shape_rect.vel,shapes->data.shape_rect.pos1);
		shapes->data.shape_rect.pos2=vector_sum(shapes->data.shape_rect.vel,shapes->data.shape_rect.pos2);

}
void physics_line(shape l)
{
		shapes->data.shape_line.pos1=vector_sum(shapes->data.shape_line.vel,shapes->data.shape_line.pos1);
		shapes->data.shape_line.pos2=vector_sum(shapes->data.shape_line.vel,shapes->data.shape_line.pos2);
}
void draw(){
		node* temp=shapes;
		while(temp!=NULL)
		{

				(*temp->data.draw)(temp->data);
				temp= temp->next;
		}

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
