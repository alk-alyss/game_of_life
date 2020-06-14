#include "grid.h"

bool drawing;
double gridOffX = 0, gridOffY = 0;

Grid initGrid(Uint64 _rows, Uint64 _cols){
	Grid grid = calloc(_rows, sizeof *grid);
	for(Uint64 i=0; i<_rows; i++){
		grid[i] = calloc(_cols, sizeof **grid);
		for(Uint64 j=0; j<_cols; j++){
			grid[i][j] = false;
		}
	}
	return grid;
}

Grid resizeGrid(Grid grid, Uint64 _rows, Uint64 _cols){
	Grid newGrid = initGrid(_rows, _cols);

	for(Uint64 i=0; i<_rows; i++){
		for(Uint64 j=0; j<_cols; j++){
			if(i < rows && j < cols){
				newGrid[i][j] = grid[i][j];
			}
			else newGrid[i][j] = false;
		}
	}
	free(grid);
	return newGrid;
}

void moveGrid(double offsetX, double offsetY){
	gridOffX += offsetX;
	gridOffY += offsetY;
}

void flipCell(Grid grid, SDL_Point mouse){
	mouse = screenToGrid(mouse.x, mouse.y);
	grid[mouse.y][mouse.x] = !grid[mouse.y][mouse.x];
}

void clearGrid(Grid grid){
	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			grid[i][j] = false;
		}
	}
}

void randomStartingState(Grid grid){
	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			grid[i][j] = rand()/(double)RAND_MAX > 0.5;
		}
	}
}

Uint8 getNeighbourSum(Grid grid, Uint64 i, Uint64 j){
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
	Grid next = initGrid(rows, cols);

	for(Uint64 i=0; i<rows; i++){
		for(Uint64 j=0; j<cols; j++){
			next[i][j] = grid[i][j];
			Uint8 sum = getNeighbourSum(grid, i, j);
			if(grid[i][j]){
				if(sum < 2 || sum > 3) next[i][j] = false;
			}
			else{
				if(sum == 3) next[i][j] = true;
			}
		}
	}

	free(grid);
	return next;
}

void displayGrid(Grid grid){
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
	drawing = 1;
	gridOffX = 0;
	gridOffY = 0;
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
	SDL_Point index;
	index.x = (int)((double)(x + gridOffX)/cellSize);
	index.y = (int)((double)(y + gridOffY)/cellSize);
	return index;
}

void addGosperGun(Grid grid, SDL_Point mouse){
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