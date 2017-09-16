/*author : Nicolas Reszka*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <graph.h>
#include "draw.h"
#include "grid.h"

#define SQUARE_SIZE 64

#define NW 0
#define N 1
#define NE 2
#define W 3 
#define E 4
#define SW 5
#define S 6
#define SE 7

typedef struct playerStructure {
	int x;
	int y;
	couleur c;
} player;

int randomRange(int minNumber, int maxNumber) {
    return rand() % (maxNumber - minNumber + 1) + minNumber;
}

int checkMove(int x, int y, int d, int** grid, int gridSize) {
	switch (d) {
		case NW :
			if ((x != 0 && y != 0) 
			&& (grid[x-1][y-1] == 0)) {
				return true;
			}
			break;
		case N :
			if ((y != 0)
			&& (grid[x][y-1] == 0)) {
				return true;
			}
			break;
		case NE :
			if ((x != gridSize-1 && y != 0) 
			&& (grid[x+1][y-1] == 0)) {
				return true;
			}
			break;
		case W :
			if ((x != 0) 
			&& (grid[x-1][y] == 0)) {
				return true;
			}
			break;
		case E :
			if ((x != gridSize-1) 
			&& (grid[x+1][y] == 0)) {
				return true;
			}
			break;
		case SW :
			if ((x != 0 && y != gridSize-1) 
			&& (grid[x-1][y+1] == 0)) {
				return true;
			}
			break;
		case S :
			if ((y != gridSize-1)
			&& (grid[x][y+1] == 0)) {
				return true;
			}
			break;	
		case SE :
			if ((x != gridSize-1 && y != gridSize-1) 
			&& (grid[x+1][y+1] == 0)) {
				return true;
			}
			break;
		default :
			printf("erreur : mauvais point cardinal\n");
			break;
	}
	return false;
}

int checkAllMoves(player *p, int** grid, int gridSize) {
	int d;
	int block = 0;
	for (d = 0; d < 8; d++) {
		if (!checkMove(p->x,p->y,d,grid,gridSize)) {
			block++;
		}
	}

	if (block == 8) {
		return false;
	} 

	return true;
}


int drawAndSelectMoves(player *p, int** grid, int gridSize, int cornerX, int cornerY) {
	int d, dx, dy;
  	int s = SQUARE_SIZE;
  	int check = SourisCliquee();

	for (d = 0; d < 8; d++) {
		if (checkMove(p->x,p->y,d,grid,gridSize)) {
			switch (d) {
				case NW :
					dx = cornerX+s*(p->x-1);
			     	dy = cornerY+s*(p->y-1);
					break;
				case N :
					dx = cornerX+s*(p->x);
			     	dy = cornerY+s*(p->y-1);
					break;
				case NE :
					dx = cornerX+s*(p->x+1);
			     	dy = cornerY+s*(p->y-1);
					break;
				case W :
					dx = cornerX+s*(p->x-1);
					dy = cornerY+s*(p->y);
					break;
				case E :
					dx = cornerX+s*(p->x+1);
					dy = cornerY+s*(p->y);
					break;
				case SW :
					dx = cornerX+s*(p->x-1);
			     	dy = cornerY+s*(p->y+1);
					break;
				case S :
					dx = cornerX+s*(p->x);
					dy = cornerY+s*(p->y+1);
					break;	
				case SE :
					dx = cornerX+s*(p->x+1);
			     	dy = cornerY+s*(p->y+1);
					break;	
			}
			drawMove(dx,dy);
			if (check) {
				if (getGridPosition(_X-cornerX)+cornerX == dx
				 && getGridPosition(_Y-cornerY)+cornerY == dy) {

					undraw(cornerX+s*(p->x),cornerY+s*(p->y));

					grid[p->x][p->y] = 0;
					p->x = (dx-cornerX)/s;
					p->y = (dy-cornerY)/s;
					grid[p->x][p->y] = 1;
					
					ChoisirCouleurDessin(p->c);
					drawPlayer(dx, dy);
					drawGrid(gridSize, cornerX, cornerY);

					debugGrid(gridSize, grid);
					return true;
				}
			} 
    	}
	}

	return false;
}

int placeCross(int** grid, int gridSize, int cornerX, int cornerY) {
	int check = SourisCliquee();
	int x, y, xGrid, yGrid;

	if (check) {
		if (isInGrid(_X, _Y, cornerX, cornerY, gridSize)) {
		
			xGrid = getGridCoordinate(_X-cornerX);
			yGrid = getGridCoordinate(_Y-cornerY);

			if (grid[xGrid][yGrid] == 0) {
				x = getGridPosition(_X-cornerX)+cornerX;
				y = getGridPosition(_Y-cornerY)+cornerY;
				drawCross(x, y);
				grid[xGrid][yGrid] = 2;

				debugGrid(gridSize, grid);
				return false;
			}
		}
	}

	return true;

}

int placePlayer(player *p, int** grid, int gridSize, int cornerX, int cornerY) {
	int check = SourisCliquee();
	int x, y, xGrid, yGrid;

	if (check) {
		if (isInGrid(_X, _Y, cornerX, cornerY, gridSize)) {
			
			xGrid = getGridCoordinate(_X-cornerX);
			yGrid = getGridCoordinate(_Y-cornerY);

			if (grid[xGrid][yGrid] == 0) {
				x = getGridPosition(_X-cornerX)+cornerX;
				y = getGridPosition(_Y-cornerY)+cornerY;
				drawPlayer(x,y);
				p->x = xGrid;
				p->y = yGrid;
				grid[xGrid][yGrid] = 1;

				debugGrid(gridSize, grid);
				return true;
			}		
		}
	}

	return false;
}

void placeIA(player *p, int** grid, int gridSize, int cornerX, int cornerY) {
	int x, y, xGrid, yGrid;
	int s = SQUARE_SIZE;

	xGrid = randomRange(0,gridSize-1);
	yGrid = randomRange(0,gridSize-1);

	while (grid[xGrid][yGrid] != 0) {
		xGrid = randomRange(0,gridSize-1);
		yGrid = randomRange(0,gridSize-1);
	}	
	p->x = xGrid;
	p->y = yGrid;
	grid[xGrid][yGrid] = 1;
	x = cornerX+s*(p->x);
	y = cornerY+s*(p->y);
	ChoisirCouleurDessin(p->c);
	drawPlayer(x,y);

	debugGrid(gridSize, grid);
}

void moveIA(player *p, int** grid, int gridSize, int cornerX, int cornerY) {
	int d, dx, dy;
  	int s = SQUARE_SIZE;

  	d = randomRange(0,7);

	while (!checkMove(p->x,p->y,d,grid,gridSize)) {
		d = randomRange(0,7);
	}

	switch (d) {
		case NW :
			dx = cornerX+s*(p->x-1);
	     	dy = cornerY+s*(p->y-1);
			break;
		case N :
			dx = cornerX+s*(p->x);
	     	dy = cornerY+s*(p->y-1);
			break;
		case NE :
			dx = cornerX+s*(p->x+1);
	     	dy = cornerY+s*(p->y-1);
			break;
		case W :
			dx = cornerX+s*(p->x-1);
			dy = cornerY+s*(p->y);
			break;
		case E :
			dx = cornerX+s*(p->x+1);
			dy = cornerY+s*(p->y);
			break;
		case SW :
			dx = cornerX+s*(p->x-1);
	     	dy = cornerY+s*(p->y+1);
			break;
		case S :
			dx = cornerX+s*(p->x);
			dy = cornerY+s*(p->y+1);
			break;	
		case SE :
			dx = cornerX+s*(p->x+1);
	     	dy = cornerY+s*(p->y+1);
			break;	
	}
			
	undraw(cornerX+s*(p->x),cornerY+s*(p->y));

	grid[p->x][p->y] = 0;
	p->x = (dx-cornerX)/s;
	p->y = (dy-cornerY)/s;
	grid[p->x][p->y] = 1;
	
	ChoisirCouleurDessin(p->c);
	drawPlayer(dx,dy);

	debugGrid(gridSize, grid);
}

void placeCrossIA(int** grid, int gridSize, int cornerX, int cornerY) {
	int x, y, xGrid, yGrid;
	int s = SQUARE_SIZE;

	xGrid = randomRange(0,gridSize-1);
	yGrid = randomRange(0,gridSize-1);

	while (grid[xGrid][yGrid] != 0) {
		xGrid = randomRange(0,gridSize-1);
		yGrid = randomRange(0,gridSize-1);
	}	

	x = cornerX + s*xGrid; 
	y = cornerY + s*yGrid;
	drawCross(x,y);
	grid[xGrid][yGrid] = 2;

	debugGrid(gridSize, grid);
}