#include "main.h"

App app;
bool running, paused, advance = false;
Uint64 rows, cols;
double cellSize = DEFAULT_CELLSIZE;
Grid initState;

int main(int argc, char* argv[]){
	// Initialize stuff
	srand(time(0));
	memset(&app, 0, sizeof(App));
	
	initSDL();
	atexit(cleanup);

	rows = SCREEN_HEIGHT/cellSize + MARGIN;
	cols = SCREEN_WIDTH/cellSize + MARGIN;

	initRule();
	initOffset();

	initState = initGrid(rows, cols);

	for(bool run=false; ;run=true){
		/*
		Main program loop
		*/
		running = true;
		paused = false;
		Grid grid = initGrid(rows, cols);

		// Copy previous initial grid state if not the first run
		if(run){
			for(Uint64 i=0; i<rows; i++){
				for(Uint64 j=0; j<cols; j++){
					grid[i][j] = initState[i][j];
				}
			}
		}

		// Get user choice from main menu
		switch(menu()){
			case 0:
				randomStartingState(grid);
				break;
			case 1:
				drawGrid(&grid);
				break;
			case 2:
				getRule();
				break;
			case 3:
				exit(0);
				break;
		}

		// Save initial grid state
		for(Uint64 i=0; i<rows; i++){
			for(Uint64 j=0; j<cols; j++){
				initState[i][j] = grid[i][j];
			}
		}

		// Simulation loop
		while(running){
			prepareScene(Black);
			
			mainInput(&grid);

			if(!paused || advance){
				grid = nextState(grid);
				advance = false;
			}

			displayGrid(grid);
			
			presentScene();
			
			SDL_Delay(25);
		}
	}

	return 0;
}