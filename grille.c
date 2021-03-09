#include "grille.h"
/** 
 * \fn alloue_grille(int l,int c, grille*g);
 * \param l nombre de ligne d'une grille
 * \param c nommbre de colonnes d'une grille
 * \param g une grille 
 * \return  retourne rien mais alloue dynamique de l'espace pour des lignes et colones
 */
void alloue_grille(int l,int c, grille*g){
	g->nbc=c;
	g->nbl=l;
	g->cellules=(int**)malloc(l*sizeof(int*));
	for(int i=0;i<l;i++){
		g->cellules[i]=(int *)malloc(c*sizeof(int));
	}
	for(int j=0;j<l;j++){
		for(int k=0;k<c;k++){
			g->cellules[j][k]=0;
		}
	}
}
/** 
 * \fn liberer_grille(grille*g);
 * \param g une grille 
 * \return retourne rien mais desalloue l'espace reserver par la fonction alloue_grille
 */
void libere_grille(grille* g){
	for(int i=0;i<g->nbc;i++){
		free(g->cellules[i]);
	}
	free(g->cellules);
}

/** 
 * \fn inti_grille_from_file(int l,int c, grille*g);
 * \param filemane nom d'un fichier contenant des donnees d'une grille
 * \param g une grille 
 * \return  rien alloue et initialise une grille avec les donnees de filename
 */
void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL);
	
	int i,j,n,l,c,vivantes=0;
	
	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);
	
	alloue_grille(l,c,g);
	
	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}
	
	fclose (pfile);
	return;
}

/** 
 * \fn copie_grille(int l,int c, grille*g);
 * \param gs une grille
 * \param gd une grille 
 * \return  retourne rien effectue une copie de la grille gs dans gd
 */

void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;	
}
