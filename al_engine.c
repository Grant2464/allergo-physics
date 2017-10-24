
#include "al_engine.h"
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
void init(engine * new_engine, int w, int h) {
		new_engine->exit_status=1;

		new_engine->display=NULL,new_engine->event_queue=NULL;
		new_engine->width=w,new_engine->height=h;

		assert(al_init());
		assert(al_init_primitives_addon());
		new_engine->display=al_create_display(new_engine->width,new_engine->height);
		assert(new_engine->display);
		new_engine->event_queue=al_create_event_queue();
		assert(new_engine->event_queue);
		assert(al_install_keyboard());
		assert(al_install_mouse());
		al_register_event_source( new_engine->event_queue, al_get_display_event_source(new_engine->display) );
		al_register_event_source( new_engine->event_queue, al_get_mouse_event_source() );
		al_register_event_source( new_engine->event_queue, al_get_keyboard_event_source() );
}
bool keys[ ALLEGRO_KEY_MAX ]={};
bool last_keys[ ALLEGRO_KEY_MAX ]={};
vector mouse_pos;
int pos_y;
int mouse_button;
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
				mouse_pos.x=check_engine->event.mouse.x;
				mouse_pos.y=check_engine->event.mouse.y;
				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				mouse_button=check_engine->event.mouse.button;
				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				mouse_button=0;
				break;

		case ALLEGRO_EVENT_DISPLAY_CLOSE:
				exitEngine(check_engine);
				break;
		}
}
void exitEngine(engine * check_engine){
		check_engine->exit_status=0;
}

vector mousePos(engine * check_engine){
		return mouse_pos;

}
bool mouseButtonDown(int button,engine * check_engine){
		if(mouse_button==button) {
				return 1;
		}
		return 0;
}
bool keyDown(int keycode){
		return keys[keycode];
}
bool keyUp(int keycode){
		return !keys[keycode];
}
