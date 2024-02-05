/**
 * \file io.c
 * \brief gère les affichages et la fonction qui débute le jeu
 * \author Mahamat Ouagal
 */
#include <stdio.h>
#include <stdlib.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <string.h>

#include "io.h"


#if MODETEXTE
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

void affiche_grille (grille g,int tempsEvolution,int mode,int modeAge,int modeoscillation){
	int i, l=g.nbl, c=g.nbc;
	if(modeAge){
		if(mode==1 )printf("|%d génération |le mode d'evolution est: %s |%s\n",tempsEvolution,"Cyclique","mode vieillissement activé");
		else printf("|%d génération |le mode d'evolution est: %s| %s\n",tempsEvolution,"non-Cyclique","mode vieillissement activé");
	}
	else{
		if(mode==1 )printf("|%d génération |le mode d'evolution est: %s |%s\n",tempsEvolution,"Cyclique","mode vieillissement desactivé");
		else printf("|%d génération |le mode d'evolution est: %s| %s\n",tempsEvolution,"non-Cyclique","mode vieillissement desactivé");
	}
	if (modeoscillation == -1) {
		printf("|Oscillation Non testee|\n");
	} 
	else if (modeoscillation == 0) {
		printf("|Grille non oscillante|\n");
	} 
	else {
		printf("%d pas de temps par oscillation", modeoscillation);
	}
	printf("\n");
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
	int tempsOscillation=-1;
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
				affiche_grille(*g, tempsEvolution,modeCompteVoisinsCycle, modeAge,tempsOscillation);
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
				affiche_grille(*g,tempsEvolution,modeCompteVoisinsCycle,modeAge,tempsOscillation);
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
			case 'o':
			{
				tempsOscillation=oscillation(g,modeAge,compte_voisins_vivants_mode);
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

#else


#define MARGE_GAUCHE 10
#define MARGE_HAUT 38
#define LARGEUR 450
#define HAUTEUR 400
#define EPAISSEUR 5
extern cairo_surface_t *surface;



cairo_surface_t *creationSurface(int x,int y){
		// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			WhitePixel(dpy, scr), WhitePixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask|KeyPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	/*/ run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
		} else if(e.type==ButtonPress) break;
	}*/

	return cs;
}

void cairo_close(){
	Display *dpy = cairo_xlib_surface_get_display(surface);
	cairo_surface_destroy(surface); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
}

void affiche_trait_cairo(int c, int hauteur, float tailleDeLigne){
	cairo_t *cr;
	cr=cairo_create(surface);

	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_set_line_width (cr, EPAISSEUR);

	cairo_move_to (cr,MARGE_GAUCHE, MARGE_HAUT+(hauteur*tailleDeLigne));

	for(int i=0;i<c;i++){
		cairo_line_to(cr,MARGE_GAUCHE+LARGEUR,MARGE_HAUT+(hauteur*tailleDeLigne));
		cairo_move_to(cr,MARGE_GAUCHE,MARGE_HAUT+(hauteur*tailleDeLigne));
	}

	cairo_stroke (cr);
	cairo_destroy(cr);
	return;
}


void affiche_ligne_cairo(int c,int *ligne,int vieillissement,int hauteur, float tailleLigne){
	float tailleColonne=(float) LARGEUR/(float)c;
	cairo_t *cr;
	cairo_t *cellules;
	char modeAge[10];
	cr=cairo_create(surface);
	cellules=cairo_create(surface);

	cairo_set_source_rgb(cr,0.0, 0.0, 0.0);
	cairo_set_source_rgb(cellules,0.0, 0.0, 0.0);
	cairo_set_line_width(cr, EPAISSEUR);

	cairo_move_to(cr,MARGE_GAUCHE,MARGE_HAUT+(hauteur*tailleLigne));
	
	for(int i=0;i<c;i++){

		if (ligne[i] == 0) {
			cairo_line_to(cr, MARGE_GAUCHE + i * tailleColonne, MARGE_HAUT+ (hauteur * tailleLigne) + tailleLigne);
			cairo_move_to(cr, MARGE_GAUCHE + ((i+1) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne));
			cairo_line_to(cr, MARGE_GAUCHE + ((i+1) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne) + tailleLigne);
		} 
		else if (ligne[i] == -1) {
			cairo_line_to(cr, MARGE_GAUCHE + i * tailleColonne, MARGE_HAUT + (hauteur * tailleLigne) + tailleLigne);
			cairo_line_to(cr, MARGE_GAUCHE + ((i+1) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne) + 1);
			cairo_line_to(cr, MARGE_GAUCHE + ((i+1) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne) + tailleLigne);
			cairo_line_to(cr, MARGE_GAUCHE + i * tailleColonne, MARGE_HAUT + (hauteur * tailleLigne) + tailleLigne);
			cairo_move_to(cr, MARGE_GAUCHE + ((i) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne));
			cairo_line_to(cr, MARGE_GAUCHE + ((i+1) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne) + tailleLigne);
			cairo_line_to(cr, MARGE_GAUCHE + ((i+1) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne));
		}
		else {
			cairo_line_to(cr, MARGE_GAUCHE + i * tailleColonne, MARGE_HAUT + (hauteur * tailleLigne) + tailleLigne);
			cairo_move_to(cr, MARGE_GAUCHE + ((i-1) * tailleColonne) + 2, MARGE_HAUT + (hauteur * tailleLigne) + 2);
			cairo_rectangle(cellules, MARGE_GAUCHE + i * tailleColonne + 3, MARGE_HAUT + (hauteur * tailleLigne + 3),
			tailleColonne - 3, tailleLigne - 3);
			cairo_fill(cellules);

			if (vieillissement) {
				sprintf(modeAge, "%d", ligne[i]);
				cairo_move_to(cr, MARGE_GAUCHE + ((i) * tailleColonne) + tailleColonne/2 - 5,
				MARGE_HAUT + (hauteur * tailleLigne) + (tailleLigne*2/3) - 3);
				cairo_set_source_rgb (cr, 1.0, 0.0, 0.0);
				cairo_select_font_face(cr, "Arial",
					CAIRO_FONT_SLANT_NORMAL,
					CAIRO_FONT_WEIGHT_BOLD);
				cairo_set_font_size(cr, 15);
				cairo_show_text(cr, modeAge);
				cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
			}
			
			cairo_move_to(cr, MARGE_GAUCHE + ((i+1) * tailleColonne), MARGE_HAUT + (hauteur * tailleLigne));
		}	
	}	
	cairo_fill(cellules);
	cairo_stroke(cr);
	cairo_destroy(cr);
	cairo_destroy(cellules);
	return;
}



void affiche_grille_cairo (grille g, int tempsEvolution, int comptageCyclique, int vieillissement,int tempsOscillation){
	int l=g.nbl, c=g.nbc;

	char pasDeTemps[100], modeComptageCyclique[100], modeVieillissement[100],Oscillation[100];
	sprintf(pasDeTemps, " %d Générations ", tempsEvolution);
	sprintf(modeComptageCyclique, comptageCyclique ? " Le mode de Comptage est: Cyclique" : " Le mode de Comptage est : Non-cyclique");
	sprintf(modeVieillissement, vieillissement ? " Le mode Vieillissement est : Active" : " Le mode Vieillissement est : Desactive");

	if (tempsOscillation == -1) {
		sprintf(Oscillation, " L'Oscillation est : Non testee");
	} else if (tempsOscillation == 0) {
		sprintf(Oscillation, " Grille non oscillante");
	} else {
		sprintf(Oscillation, " L'oscillation est de : %d pas de periode", tempsOscillation);
	}
	cairo_t *cr;
	cr = cairo_create(surface);

	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

	cairo_select_font_face(cr, "Arial",
		CAIRO_FONT_SLANT_NORMAL,
		CAIRO_FONT_WEIGHT_BOLD);

	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_set_font_size(cr, 20);
	cairo_move_to(cr, 500, 50);
	cairo_show_text(cr, pasDeTemps);
	cairo_move_to(cr, 500, 75);
	cairo_show_text(cr, Oscillation); 
	cairo_move_to(cr, 500, 100);
	cairo_show_text(cr, modeComptageCyclique);  
	cairo_move_to(cr, 500, 125);
	cairo_show_text(cr, modeVieillissement); 

	cairo_move_to(cr, 500, 200);
	cairo_show_text(cr, "- o : Tester si la grille est oscillante");
	cairo_move_to(cr, 500, 225);
	cairo_show_text(cr, "- q / clic droit : Quitter le programme");
	cairo_move_to(cr, 500, 250);
	cairo_show_text(cr, "- v : Activer/desactiver le vieillissement");
	cairo_move_to(cr, 500, 275);
	cairo_show_text(cr, "- c : Passer en mode cyclique/non-cyclique");
	cairo_move_to(cr, 500, 300);
	cairo_show_text(cr, "- Entrée / clic gauche pour faire évoluer la grille");
	cairo_move_to(cr, 500, 325);
	cairo_show_text(cr, "- n : Charger une nouvelle grille depuis le terminal");


	cairo_destroy(cr);

	int hauteur = 0;
	float tailleLigne = (float) HAUTEUR/ (float) g.nbl;
	affiche_trait_cairo(c, hauteur, tailleLigne);
	for (int i=0; i<l; i++) {
		affiche_ligne_cairo(c, g.cellules[i], vieillissement, hauteur, tailleLigne);
		affiche_trait_cairo(c, ++hauteur, tailleLigne);
	}

	return;
}

void efface_grille_cairo () {
	cairo_t *cr;
	cr = cairo_create(surface);
	cairo_set_source_rgb (cr, 40.0,30.0,20.0);
	cairo_paint(cr);
	cairo_destroy(cr);
}



void debut_jeu_cairo(grille *g, grille *gc) {
	int tempsEvolution = 1;
	int vieillissement = 0;
	int refreshGrille = 0;
	int tempsOscillation=-1;

	int modeCompteVoisinsCycle=1; // 1 equivaut a true pour dire le comptage est cyclique
	int (*compte_voisins_vivants_mode)(int,int ,grille)=compte_voisins_vivants;

	XEvent e;
	//KeySym key;

	while(1) {
		XNextEvent(cairo_xlib_surface_get_display(surface), &e);
		
		if (e.type==Expose && e.xexpose.count<1) {
			affiche_grille_cairo(*g, tempsEvolution, modeCompteVoisinsCycle, vieillissement,tempsOscillation);
		} 
		else if (e.type == KeyPress) { // Touche pressée
			if (e.xkey.keycode == 36 || e.xkey.keycode == 104) { // Touche entrée (ou entrée numpad)
				evolue(g,gc,&tempsEvolution,compte_voisins_vivants_mode,vieillissement);
				refreshGrille = 1;
			}
			else if (e.xkey.keycode == 57)// Touche n
			{
				efface_grille_cairo();
				tempsOscillation=-1;
				tempsEvolution=0;
				libere_grille(g);
				libere_grille(gc);
				char nomDeFichier[100];
				printf("Entrer le chemain de la grille \n");
				scanf("%s",nomDeFichier);
				printf("la grille a été charger sur la fenetre \n");
				init_grille_from_file(nomDeFichier,g);
				alloue_grille(g->nbl,g->nbc,gc);
				affiche_grille_cairo(*g,tempsEvolution,modeCompteVoisinsCycle,vieillissement,tempsOscillation);
				
			}
			 
			else if (e.xkey.keycode == 54) { // Touche c
				// voisinnage cyclique / non-cyclique
				if (modeCompteVoisinsCycle){
					modeCompteVoisinsCycle=0;
					compte_voisins_vivants_mode=&(compte_voisins_vivants_non_cyclique);
				}
				else{
					modeCompteVoisinsCycle=1;
					compte_voisins_vivants_mode=&(compte_voisins_vivants);
				}
				refreshGrille = 1;
			} 
			else if (e.xkey.keycode == 55) { // Touche v
				vieillissement= (vieillissement) ? 0 : 1;
				refreshGrille = 1;
			} 
			
			else if (e.xkey.keycode == 38) break;// Touche q

			else if(e.xkey.keycode== 32){	// touche o
				tempsOscillation = oscillation(g, vieillissement,compte_voisins_vivants_mode);
				refreshGrille = 1;
			}
		} 

		// partie des clicks
		else if (e.type == ButtonPress) {
			if (e.xbutton.button == 1) { // Clic gauche pour evoluer
				evolue(g,gc,&tempsEvolution,compte_voisins_vivants,vieillissement);
				refreshGrille = 1;
			} 
			else if (e.xbutton.button == 3){
				break;
			} // Clic droit (quitte le jeu)
			
		}
		if (refreshGrille) {
			efface_grille_cairo();
			affiche_grille_cairo(*g, tempsEvolution, modeCompteVoisinsCycle, vieillissement,tempsOscillation);
			refreshGrille = 0;
		}
	}
	return;
}
#endif