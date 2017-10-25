
#include "al_engine.h"
bool keys[ ALLEGRO_KEY_MAX ]={};
bool last_keys[ ALLEGRO_KEY_MAX ]={};
MouseButtons mouse_buttons;
ALLEGRO_MOUSE_STATE state;
int mouse_released=0;
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

		al_clear_to_color(al_map_rgb(r,g,b));
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

void clearDisplay(int r, int g, int b){
		al_clear_to_color(al_map_rgb(r,g,b));
}
void updateDisplay(int sec){
		al_flip_display();
		delay(1000/sec);
}

////////////////////////////////EVENTS////////////////////////////////
void eventCheck(engine * check_engine){
		al_get_next_event( check_engine->event_queue, &check_engine->event);
		switch(check_engine->event.type) {
		case ALLEGRO_EVENT_KEY_DOWN:
				keys[ check_engine->event.keyboard.keycode ] = 1;
				break;
		case ALLEGRO_EVENT_KEY_UP:
				keys[ check_engine->event.keyboard.keycode ] = 0;
				break;
		case ALLEGRO_EVENT_MOUSE_AXES:
				al_get_mouse_state(&state);
				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				mouse_released=1;
				al_get_mouse_state(&state);
				mouse_buttons.left=state.buttons & 1;
				mouse_buttons.right=state.buttons & 2;
				mouse_buttons.middle=state.buttons & 4;
				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				if(mouse_released) {
						mouse_buttons.left=  0;
						mouse_buttons.right= 0;
						mouse_buttons.middle=0;
				}
				mouse_released=0;
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

bool keyDown(int keycode){
		return keys[keycode];
}
bool keyUp(int keycode){
		return !keys[keycode];
}
bool keyPressed(int keycode,engine * check_engine){
		last_keys[keycode]=keys[keycode];
		eventCheck(check_engine);
		if(keys[keycode] && !last_keys[keycode]) {
				keys[keycode] = 1;
				return 0;
		}
		else if(keys[keycode] && last_keys[keycode])
		{
				keys[keycode] = 0;
				return 1;
		}
		return 0;
}
vector mousePos(engine * check_engine){

		return createVector(state.x,state.y);

}
bool mouseButtonDown(int button,engine * check_engine){

		eventCheck(check_engine);

		bool mouse_button_list[3]={mouse_buttons.left,mouse_buttons.right,mouse_buttons.middle};

		return mouse_button_list[button-1];
}
bool mouseButtonPressed(int button,engine * check_engine){
//////////////todo///////////////
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
