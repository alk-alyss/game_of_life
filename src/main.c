#include "main.h"

int main(int argc, char *argv[]){
	srand(time(0));
	memset(&app, 0, sizeof(App));
	
	initSDL();
	
	atexit(cleanup);

	Cell **grid = calloc(ROWS, sizeof *grid);

	for(int i=0; i<ROWS; i++){
		grid[i] = calloc(COLS, sizeof **grid);
		for(int j=0; j<COLS; j++){
			grid[i][j].rect.y = i*CELL_SIZE+1;
			grid[i][j].rect.x = j*CELL_SIZE+1;
			grid[i][j].rect.w = CELL_SIZE-1;
			grid[i][j].rect.h = CELL_SIZE-1;
			grid[i][j].alive = 1 ? rand()/(double)RAND_MAX > 0.5 : 0;
		}
	}

	while(1){
		prepareScene();
		
		doInput();

		Cell **next = calloc(ROWS, sizeof *next);

		for(int i=0; i<ROWS; i++){
			next[i] = calloc(COLS, sizeof **next);
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
		grid = next;
		// next = NULL;

		for(int i=0; i<ROWS; i++){
			for(int j=0; j<COLS; j++){
				Color color;
				if(grid[i][j].alive) color = white;
				else color = black;
				drawRect(grid[i][j].rect, color);
			}
		}
		
		presentScene();
		
		SDL_Delay(50);
	}

	return 0;
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