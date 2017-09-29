
HEADERS = data.h draw.h physics.h other.h
OBJECTS = main.o data.o draw.o physics.o other.o

engine.out: $(OBJECTS)
	gcc -Wall -o $@ -g main.o data.o draw.o physics.o other.o -lallegro -lallegro_ttf -lallegro_font -lallegro_primitives -lm
	make clean
%.o: %.c
	gcc -c $< -o $@

clean:
	rm  $(OBJECTS)
