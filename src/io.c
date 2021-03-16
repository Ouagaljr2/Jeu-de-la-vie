/**
 * \file io.c
 * \brief gère les affichages et la fonction qui débute le jeu
 * \author Mahamat Ouagal
 */

#include "io.h"

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne,int modeAge){
	if(modeAge){
		for (int i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   ");
		else if(ligne[i]==-1) printf("| X ");
		else printf ("| %d ",ligne[i]);
	printf("|\n");
	return;
	}
	int i;
	for (i=0; i<c; ++i) 
		if (ligne[i] == 0 ) printf ("|   ");
		else if(ligne[i]==-1) printf("| X ");
		else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g,int tempsEvolution,int mode,int modeAge){
	int i, l=g.nbl, c=g.nbc;
	if(modeAge){
		if(mode==1 )printf("%d génération le mode d'evolution est: %s %s\n",tempsEvolution,"Cyclique","mode vieillissement activé");
		else printf("%d génération le mode d'evolution est: %s %s\n",tempsEvolution,"non-Cyclique","mode vieillissement activé");
	}
	else{
		if(mode==1 )printf("%d génération le mode d'evolution est: %s %s\n",tempsEvolution,"Cyclique","mode vieillissement desactivé");
		else printf("%d génération le mode d'evolution est: %s %s\n",tempsEvolution,"non-Cyclique","mode vieillissement desactivé");
	}
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i],modeAge);
		affiche_trait(c);
	}	
	printf("\n"); 
	return;
}

void efface_grille (grille g){
	system("clear"); 
}

void debut_jeu(grille *g, grille *gc){
	int tempsEvolution=0;
	int modeCompteVoisinsCycle=1; // 1 equivaut a true pour dire le comptage est cyclique
	int (*compte_voisins_vivants_mode)(int,int ,grille)=compte_voisins_vivants;
	int modeAge=0;// 0 Age desactivé 1 pour activé
	char c = getchar(); 
	while (c != 'q') // touche 'q' pour quitter
	{ 
		switch (c) {
			case '\n' : 
			{ // touche "entree" pour évoluer
				evolue(g,gc,& tempsEvolution,compte_voisins_vivants_mode,modeAge);
				efface_grille(*g);
				affiche_grille(*g, tempsEvolution,modeCompteVoisinsCycle, modeAge);
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
				affiche_grille(*g,tempsEvolution,modeCompteVoisinsCycle,modeAge);
				break;
			}
			case 'c':
			{
				if (modeCompteVoisinsCycle){
					modeCompteVoisinsCycle=0;
					compte_voisins_vivants_mode=&(compte_voisins_vivants_non_cyclique);
				}
				else{
					modeCompteVoisinsCycle=1;
					compte_voisins_vivants_mode=&(compte_voisins_vivants);
				}
				
				break;
			}
			case 'v':
			{
				modeAge= (modeAge) ? 0 : 1;
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
