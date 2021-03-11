/** 
 * \file
 * Fonctions pour les affichages
 * \author Ouagal Mahamat
 */
#include "io.h"
/** 
 * \fn affiche_trait(int c,);
 * \param c nommbre de colonnes d'une grille
 * \return  affiche les traiss delimitants les colonnes d'une grille
 */
void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}
/** 
 * \fn affiche_ligne(int c, int* ligne);
 * \param c nommbre de colonnes d'une grille
 * \param ligne lignes d'une grille
 * \return  affiche les lignes delimitants les lignes d'une grille
 */
void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}
/** 
 * \fn affiche_grille(int l,int c, grille*g);
 * \param g une grille 
 * \return  retourne rien mais affiche une grille passée en paramettre
 */
void affiche_grille (grille g,int tempsEvolution,int mode){
	int i, l=g.nbl, c=g.nbc;
	if(mode==1 )printf("%d génération le mode d'evolution est: %s\n",tempsEvolution,"Cyclique");
	else printf("%d génération le mode d'evolution est: %s\n",tempsEvolution,"non-Cyclique");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}


void efface_grille (grille g){
	system("clear"); 
}

/** 
 * \fn debut_jeu(grille *g, grille*gc);
 * \param g  une grille
 * \param gc une grille 
 * \return  retourne rien mais cree une grille g copie son evolution dans c et l'efface a chaque appuis sur "\n" 
 */
void debut_jeu(grille *g, grille *gc){
	int tempsEvolution=0;
	int modeCompteVoisinsCycle=1; // 1 equivaut a true pour dire le comptage est cyclique
	int (*compte_voisins_vivants)(int,int ,grille)=compte_voisins_vivants_non_cyclique;
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc,& tempsEvolution,compte_voisins_vivants);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution,modeCompteVoisinsCycle);
				break;
			}
			case 'n':
			{	tempsEvolution=0;
				libere_grille(g);
				libere_grille(gc);
				char nomDeFichier[100];
				printf("Entrer le chemain de la grille \n");
				scanf("%s",nomDeFichier);
				init_grille_from_file(nomDeFichier,g);
				alloue_grille(g->nbl,g->nbc,gc);
				affiche_grille(*g,tempsEvolution,modeCompteVoisinsCycle);
				break;
			}
			case 'c':
			{
				if (modeCompteVoisinsCycle){
					modeCompteVoisinsCycle=0;
					compte_voisins_vivants=&(compte_voisins_vivants_non_cyclique);
				}
				else{
					modeCompteVoisinsCycle=1;
					compte_voisins_vivants=&(compte_voisins_vivants_non_cyclique);
				}
				
				break;
			}
			default : 
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar(); 
	}
	return;	
}
