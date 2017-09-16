/*author : Nicolas Reszka*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <graph.h>

typedef struct bouttonStructure {
	int x;
	int y;
	int w;
	int h;
	char* text;
} button;

int testButton(button b) {
	if ((_X > b.x && _X < (b.x + b.w)) 
	&& (_Y > b.y && _Y < (b.y + b.h))) {
		return true;
	} else {
		return false;
	}
}

void drawButton(button b) {
	DessinerRectangle(b.x,b.y,b.w,b.h);
	EcrireTexte(b.x+16,b.y+b.h/2+8,b.text,1);
}

void drawGridSize(int x, int y, int gridSize) {
	char g[1];
	couleur c;
	c = CouleurParComposante(255,255,255);
	ChoisirCouleurDessin(c);
	RemplirRectangle(x-16,y-16,32,32);
	c = CouleurParComposante(0,0,0);
	ChoisirCouleurDessin(c);
	g[0] = '0'+gridSize;
	EcrireTexte(x,y,g,1);
}

void drawGameInfo(int x, int y, char* text) {
	couleur c = CouleurParComposante(255,255,255);
	ChoisirCouleurDessin(c);
	RemplirRectangle(x,y,600,72);
	c = CouleurParComposante(0,0,0);
	ChoisirCouleurDessin(c);
	EcrireTexte(x+16,y+16,text,1);

}
