/*author : Nicolas Reszka*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <graph.h>
#include <time.h>
#include <unistd.h>
#include "menu.h"
#include "grid.h"
#include "draw.h"
#include "play.h"

#define STATE_MENU 0
#define STATE_PLACE 1
#define STATE_PLAY 2
#define STATE_GAMEOVER 3

#define BUTTON_LESS 0
#define BUTTON_MORE 1
#define BUTTON_SOLO 2
#define BUTTON_MULTI 3

int main(void) {
  	int lastKey;
  	int i;

  	int screenW, screenH;
  	int cornerX, cornerY;
  	
  	int gridSize = 3;
  	int** grid = NULL;

  	int gameIsRunning = true;
  	int state = STATE_MENU;
  	int startGame = false;
  	int solo = true;
  	int player1Placed = false;
  	int move = false;
  	int playerTurn = 0;
  	int winner = 0;
  	
  	button menu[5] = {
  		{ 64, 128, 64, 64, "-" },
  		{ 192, 128, 64, 64, "+" },
  		{ 64, 256, 128, 64, "Jouer Solo" },
  		{ 256, 256, 192, 64, "Jouer Multijoueur" }
  	};

  	button quitGame = {940, 32, 48, 48, "X" };

  	button backToMenu = {512, 700, 256, 64, "Retour au menu"};

  	couleur colorMenu = CouleurParComposante(255,0,0);
  	couleur colorMenuHover = CouleurParComposante(0,0,255);

  	srand(time(NULL));
  	
  	player p1, p2;
  	player *P;

  	p1.c = CouleurParComposante(255,0,0);
  	p2.c = CouleurParComposante(0,0,255);

	InitialiserGraphique();

	screenW = 1024;
  	screenH = 786;

    CreerFenetre(64,64,screenW,screenH);
	
	while (gameIsRunning) {
		SourisPosition();

		if (ToucheEnAttente()) {
			lastKey = Touche();
		}

		if (testButton(quitGame)) {
			ChoisirCouleurDessin(colorMenuHover);
			if (SourisCliquee()) {
				gameIsRunning = false;
			}
		} else {
			ChoisirCouleurDessin(colorMenu);
		}
		drawButton(quitGame);
		
		if (lastKey == XK_Escape) {
			gameIsRunning = false;
		}	
		

		switch (state) {
			case STATE_MENU :
				if (!startGame) {
					drawGameInfo(96,24,"Choisir la taille de la grille");
					drawGameInfo(96,700,"Programme par Nicolas Reszka et Victor Serena");
					for (i = 0; i < 4; i++) {
						if (testButton(menu[i])) {
							ChoisirCouleurDessin(colorMenuHover);

							if (SourisCliquee()) {
								switch (i) {
									case BUTTON_LESS :
										if (gridSize > 3) {
											gridSize--;
										}
										break;
									case BUTTON_MORE :
										if (gridSize < 9) {
											gridSize++;
										}
										break;
									case BUTTON_SOLO :
										solo = true;
										startGame = true;
										break;
									case BUTTON_MULTI :
										solo = false;
										startGame = true;
										break;
								}
							}
						} else {
							ChoisirCouleurDessin(colorMenu);
						}
						drawButton(menu[i]);
					}
					drawGridSize(160,160,gridSize);
				} else {
					allocGrid(gridSize, &grid);
				  	emptyGrid(gridSize, grid);
				  	debugGrid(gridSize, grid);
				  	clearScreen(screenW,screenH);
				  	cornerX = getCorner(screenW,gridSize);
					cornerY = getCorner(screenH,gridSize);
				  	drawGrid(gridSize, cornerX, cornerY);
					state = STATE_PLACE;
					P = &p1;
					player1Placed = false;
				  	move = false;
				  	playerTurn = 0;
				  	winner = 0;
				  	startGame = false;
				}
				break;

			case STATE_PLACE :
				if (!player1Placed) {
					drawGameInfo(96,24,"Joueur 1 place son pion");
				} else {
					drawGameInfo(96,24,"Joueur 2 place son pion");	
				}

				ChoisirCouleurDessin(P->c);
				if (placePlayer(P, grid, gridSize, cornerX, cornerY)) {
					if (!player1Placed) {
						player1Placed = true;
						P = &p2;
						if (solo) {
							drawGameInfo(96,24,"L'odinateur place son pion");
							sleep(1);
							ChoisirCouleurDessin(P->c);
							placeIA(P, grid, gridSize, cornerX, cornerY);
							P = &p1;
							state = STATE_PLAY;
							break;
						}
					} else {
						P = &p1;
						state = STATE_PLAY;
					}
				}
				break;

			case STATE_PLAY :
				if (!checkAllMoves(&p1,grid,gridSize)) {
					winner = 2;
				}

				if (!checkAllMoves(&p2,grid,gridSize)) {
					if (winner == 2) {
						winner = -1;
					} else {
						winner = 1;
					}
				}

				if (winner != 0) {
					if (winner == 1) {
						drawGameInfo(96,24,"Joueur 1 vainqueur !");
					} else if (winner == 2) {
						drawGameInfo(96,24,"Joueur 2 vainqueur !");
					} else {
						drawGameInfo(96,24,"match nul !");
					}	
					state = STATE_GAMEOVER;
					break;
				} 


				if (!move) {
					if (solo && playerTurn == 1) {
						drawGameInfo(96,24,"L'ordinateur bouge son pion");
						sleep(1);
						ChoisirCouleurDessin(P->c);
						moveIA(P,grid,gridSize,cornerX,cornerY);
						move = true;
					} else {
						if (playerTurn == 0) {
							drawGameInfo(96,24,"Joueur 1 bouge son pion");
						} else {
							drawGameInfo(96,24,"Joueur 2 bouge son pion");
						}
						ChoisirCouleurDessin(P->c);
						move = drawAndSelectMoves(P,grid,gridSize,cornerX,cornerY);
					}
					
				} else {
					if (solo && playerTurn == 1) {
						drawGameInfo(96,24,"L'ordinateur condamne une case");
						sleep(1);
						ChoisirCouleurDessin(P->c);
						placeCrossIA(grid, gridSize, cornerX, cornerY);
						move = false;
					} else {
						if (playerTurn == 0) {
							drawGameInfo(96,24,"Joueur 1 condamne une case");
						} else {
							drawGameInfo(96,24,"Joueur 2 condamne une case");
						}
						ChoisirCouleurDessin(P->c);
						move = placeCross(grid, gridSize, cornerX, cornerY);
					}
					
					if (!move) {
						if (playerTurn == 0) {
							P = &p2;
							playerTurn = 1;
						} else {
							P = &p1;
							playerTurn = 0;
						}
					}
				}
				break;

			case STATE_GAMEOVER : 
				if (testButton(backToMenu)) {
					ChoisirCouleurDessin(colorMenuHover);
					if (SourisCliquee()) {
						state = STATE_MENU;
						clearScreen(screenW,screenH);
						break;
					}
				} else {
					ChoisirCouleurDessin(colorMenu);
				}
				drawButton(backToMenu);
				break;
		}
	}

    FermerGraphique();

    if (grid != NULL) {
    	freeGrid(gridSize, grid);
    }
    

  	return EXIT_SUCCESS;
}
