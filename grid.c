/*author : Nicolas Reszka*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SQUARE_SIZE 64

void allocGrid(int size, int*** grid) {
	int i;
	int x,y;
	
	*grid = NULL;
	*grid = (int**) malloc( sizeof(int*) * size);

	for (i = 0; i < size; i++) {
		(*grid)[i] = (int*) malloc( sizeof(int) * size);
	}
}

void freeGrid(int size, int** grid) {
	int i; 

	for (i = 0; i < size; i++) {
    	free(grid[i]);
	}

    free(grid);
}

void emptyGrid(int size, int** grid) {
	int x,y;

	for (x = 0; x < size; x++) {
		for (y = 0; y < size; y++) {
			grid[x][y] = 0;
		} 
	} 
}

void debugGrid(int size, int** grid) {
	int x,y;

	putchar('\n');
	for (y = 0; y < size; y++) {
		for (x = 0; x < size; x++) {
			printf(" %d", grid[x][y]);
		} 
		putchar('\n');
	} 
}

int isInGrid(int x, int y, int left, int top, int gridSize) {
	int s = SQUARE_SIZE;
	if ((x > left && x < (left + gridSize * s)) 
	&& (y > top && y < (top + gridSize * s))) {
		return true;
	} else {
		return false;
	}
}

int getGridPosition(int p) {
	int s = SQUARE_SIZE;
	p = (p/s) * s; 
	return p;
}

int getGridCoordinate(int p) {
	int s = SQUARE_SIZE;
	p = getGridPosition(p) / s;
	return p;
}