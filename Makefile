CC=gcc
CFLAGS1 = -g -Wall
CFLAGS2 = -I include
LDFLAGS= -lm

vpath %.h include
vpath %.c src
vpath %.o obj
vpath main bin

OBJETS = $(patsubst src/%.c, obj/%.o,$(wildcard src/*.c))
OBJ =obj/
CPATH = src/

main: $(OBJETS)
	$(CC) $(CFLAGS) -o $@ $? $(LDFLAGS) $(CFLAGS2)
	mv -f main ./bin/

$(OBJ)main.o: main.c grille.h io.h jeu.h
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mv -f *.o ./obj/

$(OBJ)%.o:%.c %.h
	$(CC) $(CFLAGS1) -c $< $(CFLAGS2)
	mv -f *.o ./obj

clean:	
	rm  -f obj/*.o
	rm -f bin/main
	rm -fr doc

dist: makefile src include bin obj
	tar -cvz $^ -f MahamatOuagal-GoL-v.tar.xz
docs:
	mkdir -p doc
	doxygen -g
	doxygen Doxyfile
	mv  html latex Doxyfile ./doc