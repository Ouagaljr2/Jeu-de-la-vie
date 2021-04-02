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
/** 
 * \fn set_vivante(int i, int j,grille g);
 * \param i indice d'une ligne
 * \param j indice d'une colonne
 * \param g une grille 
 * \return retourne rien mais rend vivante la cellule (i,j) de la grille g
 */
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] =1;}

// rend morte la cellule (i,j) de la grille g
/** 
 * \fn set_morte(int i, int j,grille g);
 * \param i indice d'une ligne
 * \param j indice d'une colonne
 * \param g une grille 
 * \return retourne rien mais rend morte la cellule (i,j) de la grille g
 */
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}

// teste si la cellule (i,j) de la grille g est vivante
/** 
 * \fn est_vivante(int i, int j,grille g);
 * \param i indice d'une ligne
 * \param j indice d'une colonne
 * \param g une grille 
 * \return 1 (true) si la cellule(i,j) est vivante  si non 0(false)
 */
static inline int est_vivante(int i, int j, grille g){return g.cellules[i][j] != 0;}

// test si la cellule (i,j) de la grille g peut etre viable
/** 
 * \fn non_vivante(int i, int j,grille g);
 * \param i indice d'une ligne
 * \param j indice d'une colonne
 * \param g une grille 
 * \return 1 (true) si la cellule(i,j) est non viable si non 0(false)
 */
static inline int non_vivable(int i, int j, grille g){return g.cellules[i][j] = -1;}

// recopie gs dans gd (sans allocation)
/** 
 * \fn copie_grille(int l,int c, grille*g);
 * \param gs une grille
 * \param gd une grille 
 * \return  retourne rien effectue une copie de la grille gs dans gd
 */
void copie_grille (grille gs, grille gd);

// Egalité de deux grilles
/** 
 * \fn grilles_egales( grille ga, grille gb)
;
 * \param ga une grille
 * \param gb une grille 
 * \return  retourne 1 (True )si ga est egale a gb si non 0(False)
 */
int grilles_egales( grille ga, grille gb);

// Grille vide
/** 
 * \fn vide( grille g)
 * \param g une grille
 * \return  retourne 1 (True )si g est vide si non 0(False)
 */
int vide(grille g);

// Test Oscillation d'une grille
/** 
 * \fn oscillation(grille *g,int vieillissement,int (*compte_voisins_vivants_mode)(int,int, grille))
 * \param g une grille
 * \param veillissement  entier pour activer/desactiver le mode vieillissement
 * \param compte_voisins_vivants_mode correspond au mode d'evolution de la grille cyclique ou non cyclique
 * \return  retourne le pas de temps correspondant à la periode d'oscillation d'une grille 
 */
int oscillation(grille *g,int vieillissement,int (*compte_voisins_vivants_mode)(int,int, grille));

#endif
