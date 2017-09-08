#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct vector {
        float x;
        float y;
} vector;

int init(void);
void delay(int number_of_seconds);
void circle(int x,int y,int r,int g, int b);
void *paddle_movement1(void *args);
void *paddle_movement2(void *args);


ALLEGRO_KEYBOARD_STATE kbdstate;
ALLEGRO_DISPLAY *display=0;
ALLEGRO_FONT *font=0;

vector vector_sum(vector a, vector b);
vector velocity1;
vector ball1;
vector velocity2;
vector ball2;
int jump_hieght = 20;
int down_velocity = 2;
int x_mobility=10;
int main() {
        init();
        velocity1.x=0;
        velocity1.y=0;
        ball1.x=300;
        ball1.y=600;
        velocity2.x=0;
        velocity2.y=0;
        ball2.x=400;
        ball2.y=600;
        pthread_t threads[1];

        while(1) {
                printf("Ball2.x: %f. Velocity2.x: %f\n",ball2.x,velocity2.x);
                pthread_create(&threads[0], NULL, paddle_movement1, (void *)0);
                pthread_create(&threads[1], NULL, paddle_movement2, (void *)1);
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_rectangle(285, 450, 315,  600,al_map_rgb(0,0,255),10);
                al_draw_circle(ball1.x,ball1.y, 20,al_map_rgb(0,255,0), 10);
                al_draw_circle(ball2.x,ball2.y, 20,al_map_rgb(255,0,0), 10);
                al_flip_display();
              /*  circle(ball1.x,ball1.y,255,0,0);
                circle(ball2.x,ball2.y,0,255,0);*/

        }
        al_destroy_display(display);
        return 0;
}
void *paddle_movement1(void *args){
        al_get_keyboard_state(&kbdstate);

        if(al_key_down(&kbdstate, ALLEGRO_KEY_UP)&&ball1.y>=599) {
                velocity1.y=-1*jump_hieght;
              }
        if(al_key_down(&kbdstate, ALLEGRO_KEY_DOWN)&&ball1.y<=599) {
                velocity1.y+=down_velocity;
        }
        if(al_key_down(&kbdstate, ALLEGRO_KEY_LEFT)&& ball1.x>345) {
                velocity1.x=-x_mobility;
        }
        if(al_key_down(&kbdstate, ALLEGRO_KEY_RIGHT)&& ball1.x<600) {
                velocity1.x=x_mobility;
        }
        if(ball1.y<=600) {
                velocity1.y+=0.8;
        }
        else if(ball1.y>600) {
                ball1.y=600;
                velocity1.y=0;
        }
        if(ball1.x>600){
          ball1.x=600;
        }
        else if(ball1.x<345){
          ball1.x=345;

        }
        ball1=vector_sum(ball1,velocity1);
        velocity1.x=0;
        pthread_exit(NULL);
}
void *paddle_movement2(void *args){
        al_get_keyboard_state(&kbdstate);

        if(al_key_down(&kbdstate, ALLEGRO_KEY_W) &&ball2.y>=599) {
                velocity2.y=-1*jump_hieght;
              }
        if(al_key_down(&kbdstate, ALLEGRO_KEY_S) &&ball2.y<=599) {
                velocity2.y+=down_velocity;
        }
        if(al_key_down(&kbdstate, ALLEGRO_KEY_A )&& ball2.x>0) {
                velocity2.x=-x_mobility;
        }
        if(al_key_down(&kbdstate, ALLEGRO_KEY_D )&& ball2.x<255) {
                velocity2.x=x_mobility;
        }
        if(ball2.y<=600) {
                velocity2.y+=0.8;
        }
        else if(ball2.y>600) {
                ball2.y=600;
                velocity2.y=0;
        }
        if(ball2.x>255){
          ball2.x=255;
        }
        else if(ball2.x<0){
          ball2.x=0;

        }
        ball2=vector_sum(ball2,velocity2);
        velocity2.x=0;
        pthread_exit(NULL);
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
        if (!al_install_keyboard()) {
                fprintf(stderr,"Error installing keyboard.\n");
                return 1;
        }

}

void circle(int x,int y,int r,int g, int b) {
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_circle(x,y, 20,al_map_rgb(r,g,b), 10);
        al_flip_display();
}

void delay(int number_of_seconds)
{
        int milli_seconds = 1000 * number_of_seconds;
        clock_t start_time = clock();
        while (clock() < start_time + milli_seconds) ;
}
vector vector_sum(vector a, vector b){
        vector out;
        out.x=a.x+b.x;
        out.y=a.y+b.y;
        return out;
}
