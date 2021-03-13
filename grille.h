#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {int nbl; int nbc; int** cellules;} grille;
 
// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/** 
 * \fn alloue_grille(int l,int c, grille*g);
 * \param l nombre de ligne d'une grille
 * \param c nommbre de colonnes d'une grille
 * \param g une grille 
 * \return  retourne rien mais alloue dynamique de l'espace pour des lignes et colones
 */
void alloue_grille (int l, int c, grille* g);

// libère une grille
/** 
 * \fn liberer_grille(grille*g);
 * \param g une grille 
 * \return retourne rien mais desalloue l'espace reserver par la fonction alloue_grille
 */
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
/** 
 * \fn inti_grille_from_file(int l,int c, grille*g);
 * \param filemane nom d'un fichier contenant des donnees d'une grille
 * \param g une grille 
 * \return  rien alloue et initialise une grille avec les donnees de filename
 */
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] =1;}
// rend morte la cellule (i,j) de la grille g
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
// teste si la cellule (i,j) de la grille g est vivante
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] != 0;}

// recopie gs dans gd (sans allocation)
/** 
 * \fn copie_grille(int l,int c, grille*g);
 * \param gs une grille
 * \param gd une grille 
 * \return  retourne rien effectue une copie de la grille gs dans gd
 */
void copie_grille (grille gs, grille gd);

#endif
