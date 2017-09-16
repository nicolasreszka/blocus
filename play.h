/*author : Nicolas Reszka*/

#ifndef PLAY_H_   
#define PLAY_H_

typedef struct playerStructure {
	int x;
	int y;
	couleur c;
} player;

/*retourne un entier aleatoire entre deux nombres*/
int randomRange(int minNumber, int maxNumber);

/*verifie la case adjacente aux coordonnes x et y dans la direction d*/
int checkMove(int x, int y, int d, int** grid, int gridSize);

/*verifie si le joueur n est pas bloque*/
int checkAllMoves(player *p, int** grid, int gridSize);

/*dessine les cases jouables et verifie si le joueur a clique puis bouge le pion*/
int drawAndSelectMoves(player *p, int** grid, int gridSize, int cornerX, int cornerY);

/*permet de placer une croix dans une case vide*/
int placeCross(int** grid, int gridSize, int cornerX, int cornerY);

/*permet de placer un joueur en debut de partie*/
int placePlayer(player *p, int** grid, int gridSize, int cornerX, int cornerY); 

/*place le pnj dans une case aleatoire*/
void placeIA(player *p, int** grid, int gridSize, int cornerX, int cornerY);

/*bouge le pnj dans une direction aleatoire*/
void moveIA(player *p, int** grid, int gridSize, int cornerX, int cornerY);

/*permet au pnj de condamner une case */
void placeCrossIA(int** grid, int gridSize, int cornerX, int cornerY);

#endif 