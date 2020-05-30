#include "grid.h"

Uint8 drawing;

Cell **initGrid(void){
	Cell **grid = calloc(ROWS, sizeof *grid);
	for(int i=0; i<ROWS; i++){
		grid[i] = calloc(COLS, sizeof **grid);
		for(int j=0; j<COLS; j++){
			grid[i][j].rect.y = i*CELL_SIZE+1;
			grid[i][j].rect.x = j*CELL_SIZE+1;
			grid[i][j].rect.w = CELL_SIZE-1;
			grid[i][j].rect.h = CELL_SIZE-1;
			grid[i][j].alive = 0;
		}
	}
	return grid;
}

void randomStartingState(Cell **grid){
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			grid[i][j].alive = 1 ? rand()/(double)RAND_MAX > 0.5 : 0;
		}
	}
}

int getNeighbourSum(Cell **grid, int i, int j){
	int sum = 0;
	for(int yoff=-1; yoff<=1; yoff++){
		for(int xoff=-1; xoff<=1; xoff++){
			if(xoff == 0 && yoff == 0) continue;
			int yIndex = i + yoff;
			int xIndex = j + xoff;
			if(yIndex>=0 && yIndex<ROWS && xIndex>=0 && xIndex<COLS)
				sum += 1 ? grid[yIndex][xIndex].alive : 0;
		}
	}
	return sum;
}

Cell **nextState(Cell **grid){
	Cell **next = initGrid();

	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
			next[i][j] = grid[i][j];
			int sum = getNeighbourSum(grid, i, j);
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
	for(int i=0; i<ROWS; i++){
		for(int j=0; j<COLS; j++){
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

SDL_Point screenToGrid(Sint32 x, Sint32 y){
	SDL_Point index;
	index.x = (int) x/CELL_SIZE;
	index.y = (int) y/CELL_SIZE;
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