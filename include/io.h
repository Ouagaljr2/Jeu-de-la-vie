/** 
 * \file
 * Fonctions pour les affichages
 * \author Ouagal Mahamat
 */
#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

// affichage d'un trait horizontal
/** 
 * \fn affiche_trait(int c,);
 * \param c nommbre de colonnes d'une grille
 * \return  affiche les traiss delimitants les colonnes d'une grille
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/** 
 * \fn affiche_ligne(int c, int* ligne);
 * \param c nommbre de colonnes d'une grille
 * \param ligne lignes d'une grille
 * \param modeAge entier prepresentant l'activation du mode vieillissement et permet d'adapter l'affchage des grilles
 * \return  affiche les lignes delimitants les lignes d'une grille
 */
void affiche_ligne (int c, int* ligne,int modeAge);

// affichage d'une grille
/** 
 * \fn affiche_grille(int l,int c, grille*g);
 * \param g une grille 
 * \param tempsEvolution Variable comtenant le temps d'evolution ou pas d'une grille affichée
 * \param mode entier correspondant au mode du calcul des voisins 1 pour cyclique 2 pour non cyclique
 * \param modeAge entier correspondant au mode d'affichage de la grille 0 pour simple 1 pour l'affichage avec l'age
 * \return  retourne rien mais affiche une grille passée en paramettre
 */
void affiche_grille (grille g,int tempsEvolution,int mode,int modeAge);

// effacement d'une grille
/** 
 * \fn efface_grille(grille g);
 * \param g  une grille
 * \return  retourne rien mais efface le contenue de la grille passée en paramètre 
 */
void efface_grille (grille g);

// debute le jeu
/** 
 * \fn debut_jeu(grille *g, grille*gc);
 * \param g  une grille
 * \param gc une grille 
 * \return  retourne rien mais cree une grille g copie son evolution dans c et l'efface a chaque appuis sur "\n" 
 */
void debut_jeu(grille *g, grille *gc);

#endif
