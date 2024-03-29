/**
 * \file jeu.c
 * \brief Tout ce qui est evolution d'une grille et nombre de voisins d'une cellule
 * \author Mahamat Ouagal
 */

#include "jeu.h"

int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v; 
}
int compte_voisins_vivants_non_cyclique(int i,int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+=(i-1 >=0 && j-1 >=0) ? est_vivante(i-1,j-1,g) : 0;
	v+=(i-1 >=0) ? est_vivante(i-1,j,g) : 0;
	v+=(i-1 >=0 && j+1 <c) ? est_vivante(i-1,j+1,g) : 0;
	v+=(j-1 >=0) ? est_vivante(i,j-1,g) : 0;
	v+=(j+1 <c ) ? est_vivante(i,j+1,g) : 0;
	v+=(i+1 <l && j-1 >=0) ? est_vivante(i+1,j-1,g) : 0;
	v+=(i+1 < l) ? est_vivante(i+1,j,g) : 0;
	v+=(i+1 < l && j+1 < c) ? est_vivante(i+1,j+1,g) : 0;
	return v;

}

void evolue (grille *g, grille *gc,int * tempsEvolution, int (*compte_voisins_vivants_mode)(int,int, grille),int vieillissement){
	(* tempsEvolution)++;
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{
			if(g->cellules[i][j]!=-1){
			v = compte_voisins_vivants_mode (i, j, *gc);
			if (est_vivante(i,j,*g)) 
			{ // evolution d'une cellule vivante
				if(vieillissement ){
					if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
					else g->cellules[i][j]++;
				}
				
				if ( v!=2 && v!= 3 ) set_morte(i,j,*g);
			}
			else 
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
		}
	}
	return;
}
