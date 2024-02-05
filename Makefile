CC=gcc
CFLAGS1 = -g -Wall
CFLAGS2 = -Iinclude -I/usr/include/cairo
LDFLAGS= -lcairo -lm -lX11 -L lib/

MODE=CAIRO

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

OBJETS = $(patsubst src/%.c, obj/%.o,$(wildcard src/*.c))
OBJ =obj/
CPATH = src/
LIB=lib/libjeu.a

main: $(LIB)
	$(CC) -DMODE$(MODE) $(CFLAGS1) -o $@ $? $(LDFLAGS) $(CFLAGS2)
	@mkdir -p bin
	mv -f main ./bin/

$(LIB): $(OBJETS)
	@mkdir -p lib
	ar -rcs $(LIB) $(OBJETS)
	ranlib $(LIB)

$(OBJ)main.o: main.c grille.h io.h jeu.h
	$(CC) -DMODE$(MODE) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p obj
	mv -f *.o ./obj/

$(OBJ)%.o:%.c %.h
	$(CC) -DMODE$(MODE) $(CFLAGS1) -c $< $(CFLAGS2)
	mkdir -p obj
	mv -f *.o ./obj

clean:	
	rm  -fr obj/*.o obj
	rm -fr bin/main bin
	rm -fr doc
	rm -fr lib/*.a lib

dist: Makefile src include Doxyfile grilles
	tar -cvz $^ -f MahamatOuagal-GoL-v5.4.tar.xz
docs:
	mkdir -p doc
	doxygen  Doxyfile
	mv html latex ./doc


