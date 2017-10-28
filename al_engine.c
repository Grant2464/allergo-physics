#include "al_engine.h"
bool empty[3]={0,0,0};
int x;
int y;

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
void engineInit(engine * new_engine, const char *title,int w, int h,int r,int g,int b,int pt ) {
		new_engine->exit_status=1;
		new_engine->focused=1;

		new_engine->display=NULL,new_engine->event_queue=NULL;
		new_engine->width=w,new_engine->height=h;
		if(!al_init()) {
				printf("al_init didn't work\n");
				assert(1);
		}
		assert(!new_engine->font);
		assert(al_init_font_addon());
		assert(al_init_ttf_addon());
		new_engine->font = al_load_font("font.ttf", pt, 0);

		assert(al_init_primitives_addon());
		al_set_new_display_flags(ALLEGRO_RESIZABLE);

		new_engine->display=al_create_display(new_engine->width,new_engine->height);
		assert(new_engine->display);
		al_set_window_title(new_engine->display,title);
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
				check_engine->keys[ check_engine->event.keyboard.keycode ] = 0;
				break;
		case ALLEGRO_EVENT_MOUSE_AXES:
				check_engine->last_mouse_pos=createVector(check_engine->mouse_state.x,check_engine->mouse_state.y);

				al_get_mouse_state(&check_engine->mouse_state);
				check_engine->mouse_pos=createVector(check_engine->mouse_state.x,check_engine->mouse_state.y);
				check_engine->wheel_pos=createVector(check_engine->mouse_state.w,check_engine->mouse_state.z);

				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				for(int i=0; i< sizeof(check_engine->mouse_buttons)/sizeof(check_engine->mouse_buttons[0]); i++) {
						check_engine->last_mouse_buttons[i]=check_engine->mouse_buttons[i];
				}
				al_get_mouse_state(&check_engine->mouse_state);
				check_engine->mouse_pos=createVector(check_engine->mouse_state.x,check_engine->mouse_state.y);
				check_engine->mouse_buttons[0]=check_engine->mouse_state.buttons & 1;
				check_engine->mouse_buttons[1]=check_engine->mouse_state.buttons & 2;
				check_engine->mouse_buttons[2]=check_engine->mouse_state.buttons & 4;

				break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				al_get_mouse_state(&check_engine->mouse_state);
				for(int i=0; i< sizeof(check_engine->mouse_buttons)/sizeof(check_engine->mouse_buttons[0]); i++) {
						check_engine->mouse_buttons[i]=0;
				}
				break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
				al_acknowledge_resize(check_engine->event.display.source);
				check_engine->width=al_get_display_width(check_engine->display);
				check_engine->height=al_get_display_height(check_engine->display);
				break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
				check_engine->focused=0;
				break;
		case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
				check_engine->focused=1;
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
bool keyReleased(int keycode,engine * check_engine){
		if(check_engine->last_keys[keycode] && !check_engine->keys[keycode]) {
				check_engine->last_keys[keycode]=0;
				return 1;
		}
		return 0;
}

bool mouseCursorMoving(int axis, engine * check_engine){
		bool x=check_engine->mouse_pos.x != check_engine->last_mouse_pos.x;
		bool y=check_engine->mouse_pos.y != check_engine->last_mouse_pos.y;
		bool states[3]={x || y,x,y};
		if(states[axis]) {
				return true;
		}
		return false;
}

bool mouseButtonDown(int button,engine * check_engine){
		return check_engine->mouse_buttons[button];
}
bool mouseButtonUp(int button,engine * check_engine){
		return !check_engine->mouse_buttons[button];
}
bool mouseButtonPressed(int button,engine * check_engine){
		if(!check_engine->last_mouse_buttons[button] && check_engine->mouse_buttons[button]) {
				check_engine->last_mouse_buttons[button] = 1;
				return 1;
		}
		return 0;
}
bool mouseButtonReleased(int button,engine * check_engine){
		if(check_engine->last_mouse_buttons[button] && !check_engine->mouse_buttons[button]) {
				check_engine->last_mouse_buttons[button] = 0;
				return 1;
		}
		return 0;
}

// bool mouseWheelMoving(int axis, engine * check_engine){
//      bool w=check_engine->wheel_pos.x != check_engine->last_wheel_pos.x;
//      bool z=check_engine->wheel_pos.y != check_engine->last_wheel_pos.y;
//      bool states[3]={w || z,w,z};
//      if(states[axis]) {
//              return true;
//      }
//      return false;
// }

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
void text(int r, int g, int b, int x, int y, char *text, engine * canvas){
		al_draw_text(canvas->font, al_map_rgb(r, g, b), x, y, 0, text);
}
