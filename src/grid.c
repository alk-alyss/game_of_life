#include "grid.h"

bool drawing;

Grid initGrid(Uint32 _rows, Uint32 _cols){
	Grid grid = calloc(_rows, sizeof *grid);
	for(Uint32 i=0; i<_rows; i++){
		grid[i] = calloc(_cols, sizeof **grid);
		for(Uint32 j=0; j<_cols; j++){
			grid[i][j].rect.y = i*cellSize+1;
			grid[i][j].rect.x = j*cellSize+1;
			grid[i][j].rect.w = cellSize-1;
			grid[i][j].rect.h = cellSize-1;
			grid[i][j].alive = false;
		}
	}
	return grid;
}

Grid resizeGrid(Grid grid, Uint32 _rows, Uint32 _cols){
	Grid newGrid = initGrid(_rows, _cols);

	for(Uint32 i=0; i<_rows; i++){
		for(Uint32 j=0; j<_cols; j++){
			if(i < rows && j < cols){
				newGrid[i][j].alive = grid[i][j].alive;
			}
			else newGrid[i][j].alive = false;
		}
	}
	free(grid);
	return newGrid;
}

void randomStartingState(Grid grid){
	for(Uint32 i=0; i<rows; i++){
		for(Uint32 j=0; j<cols; j++){
			grid[i][j].alive = true ? rand()/(double)RAND_MAX > 0.5 : false;
		}
	}
}

Uint8 getNeighbourSum(Grid grid, Uint32 i, Uint32 j){
	Uint8 sum = 0;
	for(Sint8 yoff=-1; yoff<=1; yoff++){
		for(Sint8 xoff=-1; xoff<=1; xoff++){
			if(xoff == 0 && yoff == 0) continue;
			Sint64 yIndex = i + yoff;
			Sint64 xIndex = j + xoff;
			if(yIndex>=0 && yIndex<rows && xIndex>=0 && xIndex<cols)
				sum += 1 ? grid[yIndex][xIndex].alive : 0;
		}
	}
	return sum;
}

Grid nextState(Grid grid){
	Grid next = initGrid(rows, cols);

	for(Uint32 i=0; i<rows; i++){
		for(Uint32 j=0; j<cols; j++){
			next[i][j] = grid[i][j];
			Uint8 sum = getNeighbourSum(grid, i, j);
			if(grid[i][j].alive){
				if(sum < 2 || sum > 3) next[i][j].alive = false;
			}
			else{
				if(sum == 3) next[i][j].alive = true;
			}
		}
	}

	free(grid);
	return next;
}

void displayGrid(Grid grid){
	for(Uint32 i=0; i<rows; i++){
		for(Uint32 j=0; j<cols; j++){
			SDL_Color color;
			if(grid[i][j].alive) color = White;
			else color = Black;
			drawRect(grid[i][j].rect, color);
		}
	}
}

void drawGrid(Grid *grid){
	drawing = 1;
	while(drawing){
		prepareScene(Black);
		
		gridInput(grid);

		displayGrid(*grid);

		presentScene();
		
		SDL_Delay(50);
	}

}

SDL_Point screenToGrid(Uint32 x, Uint32 y){
	SDL_Point index;
	index.x = (int) x/cellSize;
	index.y = (int) y/cellSize;
	return index;
}

void addGosperGun(Grid grid, SDL_Point mouse){
	mouse = screenToGrid(mouse.x, mouse.y);
	grid[mouse.y+0][mouse.x+25].alive = 1;

	grid[mouse.y+1][mouse.x+23].alive = 1;
	grid[mouse.y+1][mouse.x+25].alive = 1;

	grid[mouse.y+2][mouse.x+13].alive = 1;
	grid[mouse.y+2][mouse.x+14].alive = 1;
	grid[mouse.y+2][mouse.x+21].alive = 1;
	grid[mouse.y+2][mouse.x+22].alive = 1;
	grid[mouse.y+2][mouse.x+35].alive = 1;
	grid[mouse.y+2][mouse.x+36].alive = 1;

	grid[mouse.y+3][mouse.x+12].alive = 1;
	grid[mouse.y+3][mouse.x+16].alive = 1;
	grid[mouse.y+3][mouse.x+21].alive = 1;
	grid[mouse.y+3][mouse.x+22].alive = 1;
	grid[mouse.y+3][mouse.x+35].alive = 1;
	grid[mouse.y+3][mouse.x+36].alive = 1;

	grid[mouse.y+4][mouse.x+1].alive = 1;
	grid[mouse.y+4][mouse.x+2].alive = 1;
	grid[mouse.y+4][mouse.x+11].alive = 1;
	grid[mouse.y+4][mouse.x+17].alive = 1;
	grid[mouse.y+4][mouse.x+21].alive = 1;
	grid[mouse.y+4][mouse.x+22].alive = 1;

	grid[mouse.y+5][mouse.x+1].alive = 1;
	grid[mouse.y+5][mouse.x+2].alive = 1;
	grid[mouse.y+5][mouse.x+11].alive = 1;
	grid[mouse.y+5][mouse.x+15].alive = 1;
	grid[mouse.y+5][mouse.x+17].alive = 1;
	grid[mouse.y+5][mouse.x+18].alive = 1;
	grid[mouse.y+5][mouse.x+23].alive = 1;
	grid[mouse.y+5][mouse.x+25].alive = 1;

	grid[mouse.y+6][mouse.x+11].alive = 1;
	grid[mouse.y+6][mouse.x+17].alive = 1;
	grid[mouse.y+6][mouse.x+25].alive = 1;

	grid[mouse.y+7][mouse.x+12].alive = 1;
	grid[mouse.y+7][mouse.x+16].alive = 1;

	grid[mouse.y+8][mouse.x+13].alive = 1;
	grid[mouse.y+8][mouse.x+14].alive = 1;
}