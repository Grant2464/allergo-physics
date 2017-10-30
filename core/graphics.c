#include "graphics.h"

VectorI vectorSumI(VectorI v1, VectorI v2){
		return createVectorI(v1.x+v2.x,v1.y+v2.y);
}
VectorF vectorSumF(VectorF v1, VectorF v2){


		return createVectorF(v1.x+v2.x, v1.y+v2.y);
}


void circle(int x, int y, int r, int color_r,int color_g, int color_b,int stroke){
		al_draw_circle(x, y, r, al_map_rgb(color_r,color_g,color_b), stroke);
}
void rectangle(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke){
		al_draw_rectangle(x1,y1,x2,y2, al_map_rgb(color_r,color_g,color_b), stroke);
}
void line(int x1, int y1, int x2,int y2, int color_r,int color_g, int color_b,int stroke){
		al_draw_line(x1,y1,x2,y2, al_map_rgb(color_r,color_g,color_b), stroke);
}

VectorI pixel2coord(int x, int y, engine * canvas){
		return createVectorI(x+canvas->height/2,-y+canvas->width/2);
}
void text(char *text,  int x, int y, int r, int g, int b, engine * canvas){
		al_draw_text(canvas->font, al_map_rgb(r, g, b), x, y, 1, text);
}
