#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "draw.h"
#include "input.h"

Cell **initGrid(void);
void randomStartingState(Cell **grid);
Uint8 getNeighbourSum(Cell **grid, Uint32 i, Uint32 j);
Cell **nextState(Cell **grid);
void displayGrid(Cell **grid);
void drawGrid(Cell **grid);
SDL_Point screenToGrid(Uint32 x, Uint32 y);
void addGosperGun(Cell **grid);

#endif