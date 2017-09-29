a.out: main.o draw.o
	gcc -Wall -g main.o draw.o -lallegro -lallegro_ttf -lallegro_font -lallegro_primitives -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lm

main.o: main.c
	gcc -c main.c

draw.o: draw.c
	gcc -c draw.c

clean:
	rm *.o
	rm *.out
