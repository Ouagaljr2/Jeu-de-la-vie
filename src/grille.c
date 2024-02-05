/**
 * \file grilles.c
 * \brief Tous les opperations sur une grille allouer initialiser liberer copier
 * \author Mahamat Ouagal
 */

#include "grille.h"
#include "jeu.h"

void alloue_grille(int l,int c, grille* g){
	g->nbc=c;
	g->nbl=l;
	g->cellules=(int**)malloc(l*sizeof(int*));
	for(int i=0;i<l;i++){
		g->cellules[i]=(int *)malloc(c*sizeof(int));
	}
	for(int  i=0;i<l;i++){
		for(int j=0;j<c;j++){
			g->cellules[i][j]=0;
		}
	}
}

void libere_grille(grille*g){
	for(int i=0;i<g->nbl;i++){
		free(g->cellules[i]);
	}
	 free(g->cellules);
}

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0,nonVivante=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	fscanf(pfile,"%d",& nonVivante);
	for (n=0; n< nonVivante; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		non_vivable(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}

int grilles_egales( grille ga, grille gb){
	for(int i=0;i< ga.nbl;i++){
		for (int j = 0; j< ga.nbc; j++)
		{
			if(ga.cellules[i][j]!=gb.cellules[i][j]) return 0;
		}
	}
	return 1;
}

int vide(grille g){
	for(int i=0;i<g.nbl;i++){
		for(int j=0;j<g.nbc;j++){
			if(g.cellules[i][j]!=0) return 0;
		}
	}
	return 1;
}


int oscillation(grille *g,int vieillissement,int (*compte_voisins_vivants_mode)(int,int, grille)){
	int tempsOscillation=0;
	grille ga, gb,temp;
	alloue_grille(g->nbl,g->nbc,&ga);
	copie_grille(*g,ga);

	alloue_grille(g->nbl,g->nbc,&gb);
	copie_grille(*g,gb);

	alloue_grille(g->nbl,g->nbc,&temp);
	copie_grille(*g,temp);

	int pasMaxOscillation=100;
	int i=0;
	do
	{
		while(tempsOscillation<pasMaxOscillation){
			evolue(&gb,&temp,&tempsOscillation,compte_voisins_vivants_mode,vieillissement);
			if(vide(ga)) return 0;
			if(grilles_egales(ga,gb)) return tempsOscillation;
		}
		evolue(&ga,&temp,&tempsOscillation,compte_voisins_vivants_mode,vieillissement);
		copie_grille(ga,gb);
		tempsOscillation=0;
		i++;
	} while (i<pasMaxOscillation);
	return 0;

}