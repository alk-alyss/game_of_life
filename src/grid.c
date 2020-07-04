#include "common.h"
#include "draw.h"
#include "input.h"
#include "grid.h"

bool drawing, gettingRule;
double gridOffX, gridOffY;

Grid initGrid(Uint64 _rows, Uint64 _cols){
	/*
	Allocate grid memory and initialize to empty cells
	*/
	Grid grid = calloc(_rows, sizeof *grid);
	for(Uint64 i=0; i<_rows; i++){
		grid[i] = calloc(_cols, sizeof **grid);
		for(Uint64 j=0; j<_cols; j++){
			grid[i][j] = false;
		}
	}
	return grid;
}

void initOffset(void){
	gridOffX = MARGIN/2;
	gridOffY = MARGIN/2;
}

Grid resizeGrid(Grid grid, Uint64 _rows, Uint64 _cols){
	/*
	Create new grid with new dimensions and copy old overlapping cells
	*/
	Grid newGrid = initGrid(_rows, _cols);

	for(Uint64 i=0; i<_rows; i++){
		for(Uint64 j=0; j<_cols; j++){
			if(i < rows && j < cols){
				newGrid[i][j] = grid[i][j];
			}
			else newGrid[i][j] = false;
		}
	}

	// Free old grid, return new
	free(grid);
	return newGrid;
}

void moveGrid(double offsetX, double offsetY){
	/*
	Move grid view by adding to the offset from 0,0
	*/
	gridOffX += offsetX;
	gridOffY += offsetY;
}

void flipCell(Grid grid, SDL_Point mouse){
	/*
	Change cell state pointed to by mouse
	*/
	mouse = screenToGrid(mouse.x, mouse.y);
	grid[mouse.y][mouse.x] = !grid[mouse.y][mouse.x];
}

void clearGrid(Grid grid){
	/*
	Clear grid
	*/
	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			grid[i][j] = false;
		}
	}
}

void randomStartingState(Grid grid){
	/*
	Assign random state to cells in visible grid area
	*/
	for(Uint64 i=MARGIN/2; i<rows-MARGIN/2; i++){
		for(Uint64 j=MARGIN/2; j<cols-MARGIN/2; j++){
			grid[i][j] = rand()/(double)RAND_MAX > 0.5;
		}
	}
}

Uint8 getNeighbourSum(Grid grid, Uint64 i, Uint64 j){
	/*
	Get the sum of alive neighbours for a given cell
	*/
	Uint8 sum = 0;
	for(Sint8 yoff=-1; yoff<=1; yoff++){
		for(Sint8 xoff=-1; xoff<=1; xoff++){
			if(xoff == 0 && yoff == 0) continue;
			Sint64 yIndex = i + yoff;
			Sint64 xIndex = j + xoff;
			if(yIndex>=0 && yIndex<rows && xIndex>=0 && xIndex<cols)
				sum += grid[yIndex][xIndex];
		}
	}
	return sum;
}

Grid nextState(Grid grid){
	/*
	Calculate next grid state based on the rule
	*/
	Grid next = initGrid(rows, cols);

	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			next[i][j] = grid[i][j];
			Uint8 sum = getNeighbourSum(grid, i, j);
			// S rule
			if(grid[i][j]){
				// If sum < 2 or sum > 3 kill cell
				if(sum < 2 || sum > 3) next[i][j] = false;
			}
			// B rule
			else{
				// If sum = 3 make cell alive
				if(sum == 3) next[i][j] = true;
			}
		}
	}

	// Free old grid, return new
	free(grid);
	return next;
}

void displayGrid(Grid grid){
	/*
	Display the grid
	*/
	// Check if grid offset is out of bounds and correct if necessary
	double originBound = MARGIN/4*cellSize;
	double xBound = (cols-MARGIN/4)*cellSize - SCREEN_WIDTH;
	double yBound = (rows-MARGIN/4)*cellSize - SCREEN_HEIGHT;
	gridOffX = gridOffX < originBound ? originBound : gridOffX;
	gridOffY = gridOffY < originBound ? originBound : gridOffY;
	gridOffX = gridOffX > xBound ? xBound : gridOffX;
	gridOffY = gridOffY > yBound ? yBound : gridOffY;

	// Create rectangles for the live cells and render them
	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			if(grid[i][j]){
				SDL_Rect rect;
				rect.y = (Sint32) (i * cellSize + 1 - gridOffY);
				rect.x = (Sint32) (j * cellSize + 1 - gridOffX);
				rect.w = (Sint32) cellSize - 1;
				rect.h = (Sint32) rect.w;
				drawRect(rect, White);
			}
		}
	}
}

void drawGrid(Grid* grid){
	/*
	Grid drawing loop
	*/
	drawing = true;
	gridOffX = MARGIN/2*cellSize;
	gridOffY = MARGIN/2*cellSize;
	cellSize = DEFAULT_CELLSIZE;
	while(drawing){
		prepareScene(Black);
		
		gridInput(grid);

		displayGrid(*grid);

		presentScene();
		
		SDL_Delay(50);
	}
}

SDL_Point screenToGrid(Uint64 x, Uint64 y){
	/*
	Convert screen coordinates to grid indexes
	*/
	SDL_Point index;
	index.x = (int)((double)(x + gridOffX)/cellSize);
	index.y = (int)((double)(y + gridOffY)/cellSize);
	return index;
}

void addGosperGun(Grid grid, SDL_Point mouse){
	/*
	Add gosper glider gun relative to mouse
	*/
	mouse = screenToGrid(mouse.x, mouse.y);
	grid[mouse.y+0][mouse.x+25] = 1;

	grid[mouse.y+1][mouse.x+23] = 1;
	grid[mouse.y+1][mouse.x+25] = 1;

	grid[mouse.y+2][mouse.x+13] = 1;
	grid[mouse.y+2][mouse.x+14] = 1;
	grid[mouse.y+2][mouse.x+21] = 1;
	grid[mouse.y+2][mouse.x+22] = 1;
	grid[mouse.y+2][mouse.x+35] = 1;
	grid[mouse.y+2][mouse.x+36] = 1;

	grid[mouse.y+3][mouse.x+12] = 1;
	grid[mouse.y+3][mouse.x+16] = 1;
	grid[mouse.y+3][mouse.x+21] = 1;
	grid[mouse.y+3][mouse.x+22] = 1;
	grid[mouse.y+3][mouse.x+35] = 1;
	grid[mouse.y+3][mouse.x+36] = 1;

	grid[mouse.y+4][mouse.x+1] = 1;
	grid[mouse.y+4][mouse.x+2] = 1;
	grid[mouse.y+4][mouse.x+11] = 1;
	grid[mouse.y+4][mouse.x+17] = 1;
	grid[mouse.y+4][mouse.x+21] = 1;
	grid[mouse.y+4][mouse.x+22] = 1;

	grid[mouse.y+5][mouse.x+1] = 1;
	grid[mouse.y+5][mouse.x+2] = 1;
	grid[mouse.y+5][mouse.x+11] = 1;
	grid[mouse.y+5][mouse.x+15] = 1;
	grid[mouse.y+5][mouse.x+17] = 1;
	grid[mouse.y+5][mouse.x+18] = 1;
	grid[mouse.y+5][mouse.x+23] = 1;
	grid[mouse.y+5][mouse.x+25] = 1;

	grid[mouse.y+6][mouse.x+11] = 1;
	grid[mouse.y+6][mouse.x+17] = 1;
	grid[mouse.y+6][mouse.x+25] = 1;

	grid[mouse.y+7][mouse.x+12] = 1;
	grid[mouse.y+7][mouse.x+16] = 1;

	grid[mouse.y+8][mouse.x+13] = 1;
	grid[mouse.y+8][mouse.x+14] = 1;
}