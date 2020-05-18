#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "draw.h"
#include "input.h"

Cell **initGrid(void);
void randomStartingState(Cell **grid);
int getNeighbourSum(Cell **grid, int i, int j);
Cell **nextState(Cell **grid);
void displayGrid(Cell **grid);
void drawGrid(Cell **grid);
SDL_Point screenToGrid(Sint32 x, Sint32 y);
void addGosperGun(Cell **grid);

#endif