#ifndef GRID_H
#define GRID_H

#include "common.h"
#include "draw.h"

Cell **initGrid(void);
void randomStartingState(Cell **grid);
int getNeighbourSum(Cell **grid, int i, int j);
Cell **nextState(Cell **grid);
void drawGrid(Cell **grid);

#endif