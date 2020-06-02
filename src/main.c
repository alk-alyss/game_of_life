#include "main.h"

App app;
bool running;
Uint32 rows, cols;
double cellSize = 10;
Grid initState;

int main(int argc, char *argv[]){
	srand(time(0));
	memset(&app, 0, sizeof(App));
	
	initSDL();
	atexit(cleanup);

	rows = SCREEN_HEIGHT/cellSize;
	cols = SCREEN_WIDTH/cellSize;

	initState = initGrid(rows, cols);

	for(bool run=false; ;run=true){
		Grid grid = initGrid(rows, cols);

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
				drawGrid(&grid);
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