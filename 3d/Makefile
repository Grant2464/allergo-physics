OBJECTS = main.o core/al_engine.o core/graphics.o
EXEC=engine.out
$EXEC: $(OBJECTS)
	gcc -Wall -o $(EXEC) -g $(OBJECTS) -lallegro -lallegro_ttf -lallegro_font -lallegro_primitives -lm -lglut -lGL -lGLU
debug: $(OBJECTS)
	gcc -Wall -o $(EXEC) -g $(OBJECTS) -lallegro -lallegro_ttf -lallegro_font -lallegro_primitives -lm -lglut -lGL -lGLU -g
core/al_engine.o: core/al_engine.c
	gcc -o core/al_engine.o -c core/al_engine.c
core/graphics.o: core/graphics.c
	gcc -o core/graphics.o -c core/graphics.c
clean:
	rm  $(OBJECTS)
