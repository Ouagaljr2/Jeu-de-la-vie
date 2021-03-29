CC=gcc
CFLAGS1 = -g -Wall
CFLAGS2 = -Iinclude -I/usr/include/cairo
LDFLAGS= -lcairo -lm -lX11

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

OBJETS = $(patsubst src/%.c, obj/%.o,$(wildcard src/*.c))
OBJ =obj/
CPATH = src/

main: $(OBJETS)
	$(CC) $(CFLAGS1) -o $@ $? $(LDFLAGS) $(CFLAGS2)
	mkdir -p bin
	mv -f main ./bin/

$(OBJ)main.o: main.c grille.h io.h jeu.h
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p obj
	mv -f *.o ./obj/

$(OBJ)%.o:%.c %.h
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p obj
	mv -f *.o ./obj

clean:	
	rm  -fr obj/*.o obj
	rm -fr bin/main bin
	rm -fr doc

dist: makefile src include bin obj
	tar -cvz $^ -f MahamatOuagal-GoL-v.tar.xz
docs:
	mkdir -p doc
	doxygen -g
	doxygen Doxyfile
	mv  html latex Doxyfile ./doc