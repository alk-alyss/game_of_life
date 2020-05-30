#include "main.h"

App app;
Uint8 running, cellSize = 5;
Uint32 rows, cols;

int main(int argc, char *argv[]){
	srand(time(0));
	memset(&app, 0, sizeof(App));
	
	initSDL();
	
	rows = SCREEN_HEIGHT/cellSize;
	cols = SCREEN_WIDTH/cellSize;

	atexit(cleanup);

	Cell **initState = initGrid();
	for(Uint32 run=0; ;run ++){
		Cell **grid = initGrid();

		if(run){
			for(Uint32 i=0; i<rows; i++){
				for(Uint32 j=0; j<cols; j++){
					grid[i][j] = initState[i][j];
				}
			}
		}

		switch(menu()){
			case 0:
				randomStartingState(grid);
				break;
			case 1:
				drawGrid(grid);
				break;
		}

		for(Uint32 i=0; i<rows; i++){
			for(Uint32 j=0; j<cols; j++){
				initState[i][j] = grid[i][j];
			}
		}

		running = 1;
		while(running){
			prepareScene(Black);
			
			mainInput();

			grid = nextState(grid);

			displayGrid(grid);
			
			presentScene();
			
			SDL_Delay(25);
		}
	}

	return 0;
}