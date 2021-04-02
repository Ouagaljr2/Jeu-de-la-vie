/**
 * \file main.c
 * \brief Le fichier main !
 * \author Mahamat Ouagal
 */
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include<string.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


/**
 * \brief The main Function
 * \return 0 !
 */
cairo_surface_t *surface;

int main (int argc, char ** argv) {
	if (argc != 2 )
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	int tempsEvolutionDepart=0;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);



#if MODETEXT

	affiche_grille(g,tempsEvolutionDepart,1,0,-1);
	debut_jeu(&g, &gc);

#else
	surface=creationSurface(SIZEX,SIZEY);
	debut_jeu_cairo(&g,&gc);
	cairo_close(surface);

#endif
	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
