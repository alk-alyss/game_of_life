#include "grid.h"

Uint8 drawing;

Cell **initGrid(void){
	Cell **grid = calloc(rows, sizeof *grid);
	for(Uint32 i=0; i<rows; i++){
		grid[i] = calloc(cols, sizeof **grid);
		for(Uint32 j=0; j<cols; j++){
			grid[i][j].rect.y = i*cellSize+1;
			grid[i][j].rect.x = j*cellSize+1;
			grid[i][j].rect.w = cellSize-1;
			grid[i][j].rect.h = cellSize-1;
			grid[i][j].alive = 0;
		}
	}
	return grid;
}

void randomStartingState(Cell **grid){
	for(Uint32 i=0; i<rows; i++){
		for(Uint32 j=0; j<cols; j++){
			grid[i][j].alive = 1 ? rand()/(double)RAND_MAX > 0.5 : 0;
		}
	}
}

Uint8 getNeighbourSum(Cell **grid, Uint32 i, Uint32 j){
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

Cell **nextState(Cell **grid){
	Cell **next = initGrid();

	for(Uint32 i=0; i<rows; i++){
		for(Uint32 j=0; j<cols; j++){
			next[i][j] = grid[i][j];
			Uint8 sum = getNeighbourSum(grid, i, j);
			if(grid[i][j].alive){
				if(sum < 2 || sum > 3) next[i][j].alive = 0;
			}
			else{
				if(sum == 3) next[i][j].alive = 1;
			}
		}
	}

	free(grid);
	return next;
}

void displayGrid(Cell **grid){
	for(Uint32 i=0; i<rows; i++){
		for(Uint32 j=0; j<cols; j++){
			SDL_Color color;
			if(grid[i][j].alive) color = White;
			else color = Black;
			drawRect(grid[i][j].rect, color);
		}
	}
}

void drawGrid(Cell **grid){
	drawing = 1;
	while(drawing){
		prepareScene(Black);
		
		gridInput(grid);

		displayGrid(grid);

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

void addGosperGun(Cell **grid){
	grid[0][25].alive = 1;

	grid[1][23].alive = 1;
	grid[1][25].alive = 1;

	grid[2][13].alive = 1;
	grid[2][14].alive = 1;
	grid[2][21].alive = 1;
	grid[2][22].alive = 1;
	grid[2][35].alive = 1;
	grid[2][36].alive = 1;

	grid[3][12].alive = 1;
	grid[3][16].alive = 1;
	grid[3][21].alive = 1;
	grid[3][22].alive = 1;
	grid[3][35].alive = 1;
	grid[3][36].alive = 1;

	grid[4][1].alive = 1;
	grid[4][2].alive = 1;
	grid[4][11].alive = 1;
	grid[4][17].alive = 1;
	grid[4][21].alive = 1;
	grid[4][22].alive = 1;

	grid[5][1].alive = 1;
	grid[5][2].alive = 1;
	grid[5][11].alive = 1;
	grid[5][15].alive = 1;
	grid[5][17].alive = 1;
	grid[5][18].alive = 1;
	grid[5][23].alive = 1;
	grid[5][25].alive = 1;

	grid[6][11].alive = 1;
	grid[6][17].alive = 1;
	grid[6][25].alive = 1;

	grid[7][12].alive = 1;
	grid[7][16].alive = 1;

	grid[8][13].alive = 1;
	grid[8][14].alive = 1;
}