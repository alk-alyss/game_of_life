#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "draw.h"
#include "input.h"

Grid initGrid(Uint32 _rows, Uint32 _cols);
Grid resizeGrid(Grid grid, Uint32 _rows, Uint32 _cols);
void moveGrid(int offsetX, int offsetY);
void flipCell(Grid grid, SDL_Point mouse);
void clearGrid(Grid grid);
void randomStartingState(Grid grid);
Uint8 getNeighbourSum(Grid grid, Uint32 i, Uint32 j);
Grid nextState(Grid grid);
void displayGrid(Grid grid);
void drawGrid(Grid* grid);
SDL_Point screenToGrid(Uint32 x, Uint32 y);
void addGosperGun(Grid grid, SDL_Point mouse);

#endif