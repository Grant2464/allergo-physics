#include "al_engine.h"
bool empty[]={0,0,0};

////////////////////////////////NON-ENGINE RELATED////////////////////////////////
void delay(int sec){
		int ms = 1000 * sec;
		clock_t start = clock();
		while (clock() < start + ms) ;
}
vector createVector(float x, float y){
		vector out;
		out.x=x;
		out.y=y;
		return out;
}

////////////////////////////////ENGINE////////////////////////////////
void engineInit(engine * new_engine, int w, int h,int r,int g,int b ) {
		new_engine->exit_status=1;
		new_engine->display=NULL,new_engine->event_queue=NULL;
		new_engine->width=w,new_engine->height=h;

		assert(al_init());
		assert(al_init_primitives_addon());

		new_engine->display=al_create_display(new_engine->width,new_engine->height);
		assert(new_engine->display);

		al_clear_to_color(rgb(r,g,b));
		al_flip_display();

		new_engine->event_queue=al_create_event_queue();
		assert(new_engine->event_queue);

		assert(al_install_keyboard());
		assert(al_install_mouse());

		al_register_event_source( new_engine->event_queue, al_get_display_event_source(new_engine->display) );
		al_register_event_source( new_engine->event_queue, al_get_mouse_event_source() );
		al_register_event_source( new_engine->event_queue, al_get_keyboard_event_source() );
}
void engineQuit(engine * to_exit){
		al_destroy_event_queue(to_exit->event_queue);
		al_destroy_display(to_exit->display);
}

////////////////////////////////EVENTS////////////////////////////////
void eventCheck(engine * check_engine){
		al_get_next_event( check_engine->event_queue, &check_engine->event);
		switch(check_engine->event.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
				check_engine->keys[ check_engine->event.keyboard.keycode ] = 1;
				break;
		case ALLEGRO_EVENT_KEY_UP:
				check_engine->last_keys[check_engine->event.keyboard.keycode] = 0;
				check_engine->keys[ check_engine->event.keyboard.keycode ] = 0;
				break;
		case ALLEGRO_EVENT_MOUSE_AXES:
				al_get_mouse_state(&check_engine->mouse_state);
				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				memcpy(check_engine->last_mouse_buttons,check_engine->mouse_buttons,sizeof(check_engine->last_mouse_buttons));
				al_get_mouse_state(&check_engine->mouse_state);
				check_engine->mouse_buttons[0]=check_engine->mouse_state.buttons & 1;
				check_engine->mouse_buttons[1]=check_engine->mouse_state.buttons & 2;
				check_engine->mouse_buttons[2]=check_engine->mouse_state.buttons & 4;
				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				memcpy(check_engine->last_mouse_buttons,empty,sizeof(empty));
				memcpy(check_engine->mouse_buttons,empty,sizeof(empty));
				break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
				exitEngine(check_engine);
				break;
		}
}
void exitEngine(engine * check_engine){
		check_engine->exit_status=0;
}

////////////////////////////////INPUT////////////////////////////////
bool keyDown(int keycode,engine * check_engine){
		return check_engine->keys[keycode];
}
bool keyUp(int keycode,engine * check_engine){
		return !check_engine->keys[keycode];
}
bool keyPressed(int keycode,engine * check_engine){
		if(!check_engine->last_keys[keycode] && check_engine->keys[keycode]) {
				check_engine->last_keys[keycode]=1;
				return 1;
		}
		return 0;
}

vector mousePos(engine * check_engine){
		return createVector(check_engine->mouse_state.x,check_engine->mouse_state.y);
}
bool mouseButtonDown(int button,engine * check_engine){
		return check_engine->mouse_buttons[button];
}
bool mouseButtonUp(int button,engine * check_engine){
		return !check_engine->mouse_buttons[button];
}
bool mouseButtonPressed(int button,engine * check_engine){
		if(check_engine->mouse_buttons[button] && !check_engine->last_mouse_buttons[button]) {
				check_engine->last_mouse_buttons[button] = 1;
				return 1;
		}
		return 0;
}
///////////////////////////////DRAWING///////////////////////////////
void circle(int x, int y, int r, int color_r,int color_g, int color_b,int stroke){
		al_draw_circle(x, y, r, al_map_rgb(color_r,color_g,color_b), stroke);
}
void rectangle(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke){
		al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(color_r,color_g,color_b), stroke);
}
void line(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke){
		al_draw_line(x1,y1,x2,y2, al_map_rgb(color_r,color_g,color_b), stroke);
}

vector pixel2coord(engine * canvas,float x, float y){
		return createVector(x+canvas->height/2,-y+canvas->width/2);
}
