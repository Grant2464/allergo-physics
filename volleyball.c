#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>
#include <stdlib.h>
int init(void);
void delay(int number_of_seconds);
void circle(int x,int y);

ALLEGRO_DISPLAY *display=0;
ALLEGRO_FONT *font=0;
typedef struct vector {
        float x;
        float y;
} vector;
typedef struct node {
        int val;
        struct node * next;
} node_t;
vector vector_sum(vector a,vector b);
vector velocity;
vector ball;
void gravity(void);
void print_list(node_t * head);
node_t* append(node_t* head, int data);

int main() {
  init();
        ball.x=1;
        ball.y=0;
        velocity.x=20;
        velocity.y=10;
        node_t* head;//1. Create the begging of the linked list, it is eaul to nothing.
        head=append(head,1);
        print_list(head);
        while(1) {
                gravity();
                circle(ball.x,ball.y);
                ball=vector_sum(ball,velocity);
                delay(1000/60);
        }
        al_destroy_display(display);
        return 0;
}
node_t* append(node_t* head, int data){
        /* go to the last node */
        node_t *cursor = head;
        while(cursor->next != NULL)
                cursor = cursor->next;
        /* create a new node */
        node_t* new_node =  create(data,NULL);
        cursor->next = new_node;
        return head;
}
void print_list(node_t * head) {
        node_t * current = head;
        while (current != NULL) {
                printf("%d\n", current->val);
                current = current->next;
        }
}
void gravity(void){
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
        velocity.x+=abs(velocity.x)/velocity.x* -0.03;
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
        al_clear_to_color(al_map_rgb(0,0,0));
        al_draw_circle(x,y, 20,al_map_rgb(0,100,220), 10);
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
