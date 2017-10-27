OBJ = al_engine.o
a.out: main.o al_engine.o
	gcc -Wall -o a.out main.o al_engine.o -lallegro -lallegro_ttf -lallegro_font  -lallegro_primitives -lglut -lGL -lGLU -lm


debug: main.o al_engine.o
	gcc -Wall -o a.out main.o al_engine.o -lallegro -lallegro_ttf -lallegro_font -lallegro_primitives -lglut -lGL -lGLU -lm -g

main.o: main.c
	gcc -c main.c

al_engine.o: al_engine.c al_engine.h
	gcc -c al_engine.c

clean:
	-rm *.o
