#include "main.h"

App app;
int running;

int main(int argc, char *argv[]){
	srand(time(0));
	memset(&app, 0, sizeof(App));
	
	initSDL();

	atexit(cleanup);

	while(1){
		Cell **grid = initGrid();

		if(!menu()){
			randomStartingState(grid);
		}
		else{
			drawGrid(grid);
		}

		// Cell **initState = initGrid();
		// memcpy(initState, grid, sizeof grid);

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