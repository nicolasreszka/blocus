/*author : Nicolas Reszka*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <graph.h>

#define SQUARE_SIZE 64

int getCorner(int screenSize, int gridSize) {
	int corner, s;
	s = SQUARE_SIZE;
	corner = (screenSize-gridSize*s)/2;

	return corner;
}

void clearScreen(int screenW, int screenH) {
	couleur c = CouleurParComposante(255,255,255);
	ChoisirCouleurDessin(c);
	RemplirRectangle(0,0,screenW,screenH);
}

void undraw(int x, int y) {
	int s = SQUARE_SIZE;
	couleur c = CouleurParComposante(255,255,255);
	ChoisirCouleurDessin(c);
	RemplirRectangle(x+1,y+1,s-1,s-1);
}

void drawGrid(int size, int left, int top) {
	int x,y,s;
	couleur c = CouleurParComposante(0,0,0);
	
	ChoisirCouleurDessin(c);
	s = SQUARE_SIZE; 

	for (x = 0; x < size; x++) {
		for (y = 0; y < size; y++) {
			DessinerRectangle(left+x*s,top+y*s,s,s);
		} 
	} 
}

void drawMove(int x, int y) {
	int s = SQUARE_SIZE;
	DessinerRectangle(x,y,s,s);
}

void drawPlayer(int x, int y) {
	int s = SQUARE_SIZE;
	DessinerArc(x,y,s,s,0,360);
}

void drawCross(int x, int y) {
	int s = SQUARE_SIZE;
	DessinerSegment(x,y,x+s,y+s);
	DessinerSegment(x+s,y,x,y+s);
}