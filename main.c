/**
 * \file main.c
 * \brief Le fichier main !
 * \author Mahamat Ouagal
 */

#include <stdio.h>

#include "grille.h"
#include "io.h"
#include "jeu.h"


/**
 * \brief The main Function
 * \return 0 !
 */

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
	affiche_grille(g,tempsEvolutionDepart,1,0);
	
	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
