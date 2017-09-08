#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
#define DEG 3.14159265/180

ALLEGRO_DISPLAY *display=0;
ALLEGRO_FONT *font=0;

typedef struct vector {
    float x;
    float y;
} vector;

vector vector_sum(vector a,vector b);
vector rotate(vector point,vector center,double deg);

int init(void);
int distance(vector point1,vector point2);
void delay(int number_of_seconds);
void circle(int x,int y);
void line(int x1,int y1,int x2, int y2);
vector midpoint(vector point1,vector point2);
int main() {
    init();
    vector ball;
    vector velocity;
    ball.x=1;
    ball.y=0;
    velocity.x=20;
    velocity.y=10;


    while(1) {
        if(ball.y>=600) {
            velocity.y*=-.97;
            ball.y=600;
        }
        if(ball.x>=600) {
            velocity.x*=-.995;
            ball.x=600;
        }
        if(ball.x<=0) {
            velocity.x*=-.995;
            ball.x=0;
        }
        velocity.y+=.8;
        velocity.x+=abs(velocity.x)/velocity.x*-0.03;
        al_clear_to_color(al_map_rgb(0,0,0));
        al_clear_to_color(al_map_rgb(0,0,0));
        vector point1;
        point1.x=100;
        point1.y=100;
        vector point2;
        point2.x=100;
        point2.y=300;
        vector middle=midpoint(point1,point2);
        point1=rotate(point1,middle,-45);
        point2=rotate(point2,middle,-45);
        line(point1.x,point1.y,point2.x,point2.y);
        float dist=abs((point2.x-point1.x)*ball.x+(point1.y-point2.y)*ball.y+(point1.x-point2.x)*point1.y+point1.x*(point2.y-point1.y))/(sqrt(pow(point2.x-point1.x,2)+pow(point1.y-point2.y,2)));
        if(dist<=10){
            circle(30,30);
            al_flip_display();
        }

        circle(ball.x,ball.y);

        al_flip_display();
        ball=vector_sum(ball,velocity);
        delay(1000/10);
    }
    al_destroy_display(display);
    return 0;
}
vector midpoint(vector point1,vector point2){
  vector out;
  out.x=(point1.x+point2.x)/2;
  out.y=(point1.y+point2.y)/2;
  return out;
}
vector rotate(vector point,vector center,double deg){
  deg*=DEG;
  vector out;
  out.y=sin(deg) * (point.x - center.x) + cos(deg) * (point.y - center.y) + center.y;
  out.x=cos(deg) * (point.x - center.x) - sin(deg) * (point.y-center.y) + center.x;
  return out;
}
int distance(vector point1,vector point2){

 double out =sqrt(pow(point1.x-point1.x,2)+pow(point2.y-point1.y,2));
  return out;
}
int init(void) {
    if(!al_init()) {
        fprintf(stderr, "Failed to initialize Allegro.\n");
        return -1;
    }
    if(!al_init_font_addon()) {
        fprintf(stderr, "Failed to initialize Font.\n");
        return -1;
    }
    if(!al_init_ttf_addon()) {
        fprintf(stderr, "Failed to initialize Ttf.\n");
        return -1;
    }
    if(!al_init_primitives_addon()) {
        fprintf(stderr,"Couldn't initialize primitives addon!\n");
        return -1;
    }
    display=al_create_display(600,600);
    if(!display) {
        fprintf(stderr,"Couldn't create allegro display!\n");
        return -1;
    }
    font=al_load_ttf_font("arial.ttf",72,0 );
    if(!font) {
        fprintf(stderr,"Couldn't create allegro font!\n");
        return -1;
    }

}

void circle(int x,int y) {

    al_draw_circle(x,y, 20,al_map_rgb(0,100,220), 10);
}
void line(int x1,int y1,int x2, int y2) {
    al_draw_line( x1,  y1,  x2,  y2, al_map_rgb(0,100,220), 10);
}


void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
}
vector vector_sum(vector a, vector b){
  vector out;
  out.x=a.x+b.x;
  out.y=a.y+b.y;
  return out;
}
