/*author : Nicolas Reszka*/

#ifndef GRID_H_   
#define GRID_H_

/*allocation dynamique de la grille*/
void allocGrid(int size, int*** grid);

/*vider la memoire*/
void freeGrid(int size, int** grid);

/*remplir la grille de zeros*/
void emptyGrid(int size, int** grid);

/*ecrire la grille dans la console*/
void debugGrid(int size, int** grid);

/*verifier si la position x et y se trouve dans la grille*/
int isInGrid(int x, int y, int left, int top, int gridSize);

/*recupere la position p en pixel dans la grille*/
int getGridPosition(int p);

/*recupere la coordonnee dans le tableau en 2 dimensions*/
int getGridCoordinate(int p); 

#endif 