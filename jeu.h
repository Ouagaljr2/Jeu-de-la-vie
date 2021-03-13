#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/** 
 * \fn compte_voisins_vivants(int i,int j, grille g);
 * \param i indice de ligne d'une cellule
 * \param j indice de colonne d'une cellule
 * \param g une grille 
 * \return  retourne de le nombre de voisins vivant d'une cellule[i][j]
 */
int compte_voisins_vivants (int i, int j, grille g);

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont non-cycliques.
/** 
 * \fn compte_voisins_vivants_non_cyclique(int i,int j, grille g);
 * \param i indice de ligne d'une cellule
 * \param j indice de colonne d'une cellule
 * \param g une grille 
 * \return  retourne de le nombre de voisins vivant d'une cellule[i][j] de manière non cyclique
 */
int compte_voisins_vivants_non_cyclique(int i,int j, grille g);

// fait évoluer la grille g d'un pas de temps
/** 
 * \fn evolue(grille *g, grille* gc,int *tempsEvolutiton,int (*compte_voisins_vivants)(int,int,grille));
 * \param g une grille
 * \param gc une grille
 * \param tempsEvolution pointeur vers le pas d'evolution de la grille
 * \param compte_voisins_vivants_mode pointeur de fonction qui pointeur sur le mode de comptage des voisins d'une cellule que ce soit cyclique ou non
 * \param veillissement test pour voir si le mode Age est activié si oui augmente l'age des cellues encore vivantes
 * \return  retourne rien mais fais evoluer la grille g et la copie dans gc au fure et a mesure
 */
void evolue (grille *g, grille *gc,int * tempsEvolution,int (*compte_voisins_vivants)(int,int, grille),int vieillissement);

#endif
