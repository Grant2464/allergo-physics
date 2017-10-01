#include "data.h"
#include "physics.h"
#include "draw.h"
#include "other.h"


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
void delay(int sec){
		int ms = 1000 * sec;
		clock_t start = clock();
		while (clock() < start + ms) ;
}
engine init(int w, int h) {
		engine new_engine;
		ALLEGRO_DISPLAY *display=NULL;
		ALLEGRO_EVENT_QUEUE *event_queue=NULL;
		new_engine.display=display,new_engine.event_queue=event_queue;
		new_engine.exit_status=true;
		new_engine.width=w,new_engine.height=h;
		assert(al_init());
		assert(al_init_primitives_addon());
		new_engine.display=al_create_display(new_engine.width,new_engine.height);
		assert(new_engine.display);
		new_engine.event_queue=al_create_event_queue();
		assert(new_engine.event_queue);

		al_register_event_source( new_engine.event_queue, al_get_display_event_source(new_engine.display) );
		//al_register_event_source( new_engine.event_queue, al_get_mouse_event_source() );
		//al_register_event_source( new_engine.event_queue, al_get_keyboard_event_source() );
		return new_engine;
}
void event_check(){
		al_get_next_event( good_engine.event_queue, &good_engine.event);
		if(good_engine.event.type != 0 ) {
				switch(good_engine.event.type) {
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
						good_engine.exit_status=0;
						break;
/*      case ALLEGRO_EVENT_KEY_DOWN:
        good_engine.get_keys[ good_engine.event.keyboard.keycode ] = true;
        break;
        case ALLEGRO_EVENT_KEY_UP:
        good_engine.get_keys[ good_engine.event.keyboard.keycode ] = false;
        break;*/
				}

		}
}
