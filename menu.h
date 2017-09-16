/*author : Nicolas Reszka*/

#ifndef MENU_H_   
#define MENU_H_

typedef struct bouttonStructure {
	int x;
	int y;
	int w;
	int h;
	char* text;
} button;

/*verifie si la souris survole le boutton b*/
int testButton(button b); 

/*dessine un boutton*/
void drawButton(button b); 

/*dessine la taille de la grille*/
void drawGridSize(int x, int y, int gridSize); 

/*dessine le statut du jeu*/
void drawGameInfo(int x, int y, char* text); 

#endif 