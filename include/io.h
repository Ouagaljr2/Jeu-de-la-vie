#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"


#if MODETEXTE
// affichage d'un trait horizontal
/** 
 * \fn affiche_trait(int c,);
 * \param c nombre de colonnes d'une grille
 * \return  affiche les traiss delimitants les colonnes d'une grille
 */
void affiche_trait (int c);

// affichage d'une ligne de la grille
/** 
 * \fn affiche_ligne(int c, int* ligne,int modeAge);
 * \param c nommbre de colonnes d'une grille
 * \param ligne lignes d'une grille
 * \param modeAge entier prepresentant l'activation du mode vieillissement et permet d'adapter l'affchage des grilles
 * \return  affiche les lignes delimitants les lignes d'une grille
 */
void affiche_ligne (int c, int* ligne,int modeAge);

// affichage d'une grille
/** 
 * \fn affiche_grille(grille*g,int tempsEvolution,int mode,int modeAge);
 * \param g une grille 
 * \param tempsEvolution Variable comtenant le temps d'evolution ou pas d'une grille affichée
 * \param mode entier correspondant au mode du calcul des voisins 1 pour cyclique 0 pour non cyclique
 * \param modeAge entier correspondant au mode d'affichage de la grille 0 pour simple 1 pour l'affichage avec l'age
 * \param modeoscillation entier representant l'acivation de l'oscillation -1 pour non activer et 0 pour oscillante
 * \return  retourne rien mais affiche une grille passée en paramettre
 */
void affiche_grille (grille g,int tempsEvolution,int mode,int modeAge,int modeoscillation);

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

//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------------------------------------------------//

#else
#define SIZEX 1000
#define SIZEY 500

// creation de fenetre
/** 
 * \fn creationSurface(int x,int y);
 * \param x taille largeur en pixels d'une fenetre
 * \param y taille hauteur en pixels d'une fenetre
 * \return  cree une fenetre graaphique de largeur x et de hateur y
 */
cairo_surface_t *creationSurface(int x,int y);

// ferrmeture de fenetre
/** 
 * \fn cairo_close();
 * \return  detruit et ferme la fenetre creer pour le cairo_surface_t(surface)
 */
void cairo_close();

// affichage d'un trait horizontal
/** 
 * \fn affiche_trait_cairo(int c,int hauteur,float tailleDeligne);
 * \param c nombre de colonnes d'une grille
 * \param hauteur la hateur en pixels du decalge des lignes depuis le debut de la grille
 * \param tailleDeligne la hateur en pixels des cases de la grille
 * \return  affiche les traits delimitants les colonnes d'une grille
 */
void affiche_trait_cairo(int c, int hauteur, float tailleDeLigne);


// affichage d'une ligne de la grille
/** 
 * \fn affiche_ligne_cairo(int c, int* ligne,int vieillissement,int hauteur,float tailleDeligne);
 * \param c nommbre de colonnes d'une grille
 * \param ligne lignes d'une grille
 * \param Vieillissement entier prepresentant l'activation du mode vieillissement et permet d'adapter l'affchage des grilles
 * \param hauteur la hateur en pixels du decalge des lignes depuis le debut de la grille
 * \param tailleDeligne la hateur en pixels des cases de la grille
 * \return  affiche les lignes delimitants les lignes d'une grille
 */
void affiche_ligne_cairo(int c,int *ligne,int vieillissement,int hauteur, float tailleLigne);


// affichage d'une grille
/** 
 * \fn affiche_grille_cairo(grille*g,int tempsEvolution,int comptageCyclique,int vieillissement);
 * \param g une grille 
 * \param tempsEvolution Variable comtenant le temps d'evolution ou pas d'une grille affichée
 * \param comptageCyclique entier correspondant au mode du calcul des voisins 1 pour cyclique 0 pour non cyclique
 * \param vieillissement entier correspondant au mode d'affichage de la grille 0 pour simple 1 pour l'affichage avec l'age
 * \param modeOscillation determine la nature oscillante de la grille -1 non oscillante et 0 si non testé
 * \return  retourne rien mais affiche une grille passée en paramettre
 */
void affiche_grille_cairo (grille g, int tempsEvolution, int comptageCyclique, int vieillissement,int modeOscillation);


// effacement d'une grille
/** 
 * \fn efface_grille_cairo();
 * \return  retourne rien mais efface le contenue de la grille grahique passée et detruit la fenetre de la grille 
 */
void efface_grille_cairo ();


// debut_jeu_cairo
/** 
 * \fn debut_jeu_cairo(grille *g, grille *gc);
 * \param g une grille
 * \param gc une grille 
 * \return  retourne rien mais cree une grille g graphique(dans une fenetre generer)copie son evolution dans c et l'efface a chaque appuis sur "\n" ou le clique gauche
 */
void debut_jeu_cairo(grille *g, grille *gc);
#endif

#endif
