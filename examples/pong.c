#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro_opengl.h>
#include "core/graphics.h"


#define createPaddle(the_paddle) malloc(sizeof *the_paddle)
#define createBall(the_ball) malloc(sizeof *the_ball)
#define between(x,n,m) (((n<x && x<m) || (m<x && x<n)) ? 1 : 0)
#define getSign(n) (n<0 ? -1 : 1)
typedef struct _Paddle {
		VectorF top;
		VectorF bottom;
		VectorF velocity;
		int score;
} Paddle;
typedef struct _Ball {
		VectorF pos;
		VectorF velocity;
} Ball;

void paddleInit(Paddle *new_paddle,float top_x, float top_y,float length,float vel_x,float vel_y){
		new_paddle->top.x=top_x;
		new_paddle->top.y=top_y;
		new_paddle->bottom.x=top_x;
		new_paddle->bottom.y=top_y+length;
		new_paddle->velocity.x=vel_x;
		new_paddle->velocity.y=vel_y;
		new_paddle->score=0;
		return;
}
void drawPaddle(Paddle * to_draw){
		line(to_draw->top.x, to_draw->top.y, to_draw->bottom.x,to_draw->bottom.y, 200,50,70,30);
		return;
}
void updatePaddle(Paddle * to_update){
		to_update->top=vectorSumF(to_update->top,to_update->velocity);
		to_update->bottom=vectorSumF(to_update->bottom,to_update->velocity);
		return;
}
void ballInit(Ball *new_ball,float pos_x, float pos_y,float vel_x,float vel_y){
		new_ball->pos.x=pos_x;
		new_ball->pos.y=pos_y;
		new_ball->velocity.x=vel_x;
		new_ball->velocity.y=vel_y;
		return;
}
void drawBall(Ball * to_draw){
		circle(to_draw->pos.x,to_draw->pos.y,35,0,255,100,10);
		return;
}
void updateBall(Ball * to_update,Paddle * left,Paddle * right){

		bool far_left=to_update->pos.x<0;
		bool far_right=to_update->pos.x>970;
		bool far_bottom=to_update->pos.y<0;
		bool far_top=to_update->pos.y>1000;
		if( (far_left && between(to_update->pos.y,left->bottom.y,left->top.y))) {

				to_update->velocity.x*=-1;
				if(left->velocity.y!=0) {
						to_update->velocity.y+=(left->velocity.y)/abs(left->velocity.y);
				}

		}
		else if ((far_right && between(to_update->pos.y,right->bottom.y,right->top.y) )) {

				to_update->velocity.x*=-1;
				if(right->velocity.y!=0) {
						to_update->velocity.y+=(right->velocity.y)/abs(right->velocity.y);
				}
		}
		else if (far_bottom || far_top) {


				to_update->velocity.y*=-1;
		}
		else if (far_left || far_right) {

				left->score+=far_right;
				right->score+=far_left;
				to_update->pos.x+=(150* -getSign(to_update->pos.x));
				to_update->pos=createVectorF(to_update->pos.x,to_update->pos.y);
				to_update->velocity.x*=-1;
		}

		to_update->pos=vectorSumF(to_update->pos,to_update->velocity);

		return;
}
void printScore(Paddle * left,Paddle * right, engine * score_board){
		char *left_score;
		char *right_score;
		left_score=malloc(sizeof *left_score);
		right_score=malloc(sizeof *right_score);
		sprintf(left_score,"%d",left->score);
		sprintf(right_score,"%d",right->score);

		text(left_score,50,30,0,120,210,score_board);
		text(right_score,935,30,0,120,210,score_board);
		free(left_score);
		free(right_score);
}
engine *new_engine;

Paddle *paddle_left;
Paddle *paddle_right;
Ball *the_ball;
int count=0;
int main(){


		paddle_left=createPaddle(paddle_left);
		paddle_right=createPaddle(paddle_right);
		the_ball=createPaddle(the_ball);
		new_engine = createEngine(new_engine);
		paddleInit(paddle_left,0,0,200,0,0);
		paddleInit(paddle_right,1000,0,200,0,0);
		ballInit(the_ball,100,300,10,10);

		engineInit(new_engine,"ohWindow myWindow",1000,1000,FIXED,0,0,0,72);

		while(new_engine->exit_status) {

				eventCheck(new_engine);

				updatePaddle(paddle_left);
				updatePaddle(paddle_right);
				updateBall(the_ball,paddle_left,paddle_right);

				paddle_left->velocity.y=0;
				paddle_right->velocity.y=0;
				if(keyDown(ALLEGRO_KEY_ESCAPE,new_engine) || (keyDown(217,new_engine) && ((keyDown(ALLEGRO_KEY_W,new_engine) || keyDown(ALLEGRO_KEY_W,new_engine)|| keyDown(ALLEGRO_KEY_Z,new_engine)) ))) {
						exitEngine(new_engine);
				}

				if(keyDown(ALLEGRO_KEY_W,new_engine) && paddle_left->top.y>0) {
						paddle_left->velocity.y=-10;
				}

				else if (keyDown(ALLEGRO_KEY_S,new_engine) && paddle_left->bottom.y<1000) {

						paddle_left->velocity.y=10;
				}

				if(keyDown(ALLEGRO_KEY_UP,new_engine) && paddle_right->top.y>0) {
						paddle_right->velocity.y=-10;
				}

				else if (keyDown(ALLEGRO_KEY_DOWN,new_engine) && paddle_right->bottom.y<1000) {
						paddle_right->velocity.y=10;

				}

				clearDisplay(0,0,0);
				printScore(paddle_left,paddle_right,new_engine);
				drawBall(the_ball);

				drawPaddle(paddle_left);
				drawPaddle(paddle_right);

				updatedisplay(60);
				count++;
		}

		engineQuit(new_engine);
		return 0;
}
