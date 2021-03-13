main: main.o grille.o jeu.o io.o
	gcc -g -Wall -o main main.o grille.o jeu.o io.o -lm

main.o: main.c grille.h io.h jeu.h
	gcc -g -Wall -c main.c

grille.o: grille.c grille.h
	gcc -g -Wall -c grille.c

jeu.o:	jeu.c jeu.h grille.h
	gcc -g -Wall -c  jeu.c

io.o:	io.h grille.h jeu.h
	gcc -g -Wall -c io.c

clean:	
	rm  -f *.o main

dist:
	tar -zcvf MahamatOuagal-GoL-v1.0.tar.xz main.c grille.c grille.h jeu.c jeu.h io.c io.h makefile Doxyfile
docs:
	doxygen -g
	doxygen Doxyfile