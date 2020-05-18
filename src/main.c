#include "main.h"

App app;
int running;

int main(int argc, char *argv[]){
	srand(time(0));
	memset(&app, 0, sizeof(App));
	
	initSDL();

	atexit(cleanup);

	Cell **initState = initGrid();
	for(int run=0; ;run ++){
		Cell **grid = initGrid();

		if(run){
			for(int i=0; i<ROWS; i++){
				for(int j=0; j<COLS; j++){
					grid[i][j] = initState[i][j];
				}
			}
		}

		if(!menu()){
			randomStartingState(grid);
		}
		else{
			drawGrid(grid);
		}

		for(int i=0; i<ROWS; i++){
			for(int j=0; j<COLS; j++){
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
			
			SDL_Delay(50);
		}
	}

	return 0;
}