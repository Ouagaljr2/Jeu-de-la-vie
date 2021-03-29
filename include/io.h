#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#define SIZEX 500
#define SIZEY 500

// taille en piexels
cairo_surface_t *creationSurface(int x,int y);

//
void cairo_close();

// nombre de colonnes,
void affiche_trait_cairo(int c, int hauteur, float tailleDeLigne);

//
void affiche_ligne_cairo(int c,int *ligne,int vieillissement,int hauteur, float tailleLigne);

//
void affiche_grille_cairo (grille g, int tempsEvolution, int comptageCyclique, int vieillissement);

//
void efface_grille_cairo ();

//
void debut_jeu_cairo(grille *g, grille *gc);








//-------------------------------------------------------------------------------------//

// affichage d'un trait horizontal
/** 
 * \fn affiche_trait(int c,);
 * \param c nombre de colonnes d'une grille
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
