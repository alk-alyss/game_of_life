#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "draw.h"
#include "input.h"

Grid initGrid(Uint64 _rows, Uint64 _cols);
Grid resizeGrid(Grid grid, Uint64 _rows, Uint64 _cols);
void moveGrid(Sint64 offsetX, Sint64 offsetY);
void flipCell(Grid grid, SDL_Point mouse);
void clearGrid(Grid grid);
void randomStartingState(Grid grid);
Uint8 getNeighbourSum(Grid grid, Uint64 i, Uint64 j);
Grid nextState(Grid grid);
void displayGrid(Grid grid);
void drawGrid(Grid* grid);
SDL_Point screenToGrid(Uint64 x, Uint64 y);
void addGosperGun(Grid grid, SDL_Point mouse);

#endif