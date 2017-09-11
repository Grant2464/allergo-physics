#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegrogame
5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

ALLEGRO_DISPLAY *display=0;
ALLEGRO_FONT *font=0;
ALLEGRO_KEYBOARD_STATE kbdstate;
typedef struct vector {
    float x;
    float y;
} vector;
vector vector_sum(vector a, vector b);

int init(void);
void delay(int number_of_seconds);

int main() {
  al_get_keyboard_state(&kbdstate);
    init();
    vector ball;
    vector velocity;
    ball.x=300;
    ball.y=10;
    velocity.y=10;
    velocity.x=0;

    while(1) {
if(al_key_down(&kbdstate, ALLEGRO_KEY_LEFT)){
  ball.x=300;
  ball.y=10;
  velocity.y=10;
  velocity.x=0;
}
        if(ball.y>=600) {
            velocity.y*=-.97;
            ball.y=600;
        }
        velocity.y+=.8;
        al_clear_to_color(al_map_rgb(0,0,0));

        al_draw_circle(ball.x,ball.y, 20,al_map_rgb(0,100,220), 10);
        al_flip_display();
        ball=vector_sum(ball,velocity);

        delay(1000/60);
    }
    al_destroy_display(display);
    return 0;
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
