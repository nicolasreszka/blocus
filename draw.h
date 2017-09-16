/*author : Nicolas Reszka*/

#ifndef DRAW_H_   
#define DRAW_H_

/*calcule le bord de la grille en longueur ou en largeur*/
int getCorner(int screenSize, int gridSize); 

/*dessine un carre blanc de la taille de l ecran*/
void clearScreen(int screenW, int screenH); 

/*dessine un carre blanc de la tille d un joueur*/
void undraw(int x, int y);

/*dessine la grille*/
void drawGrid(int size, int left, int top); 

/*dessine les positions jouables*/
void drawMove(int x, int y);

/*dessine un pion*/
void drawPlayer(int x, int y); 

/*dessine une croix*/
void drawCross(int x, int y);

#endif 